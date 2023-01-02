#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>

#define MAX_SIZE 480
#define WINDOW_NAME "Chroma key"

using namespace std;

using namespace cv;

typedef struct
{
    Mat *foreground;
    Mat *foregroundAsYCbCr;
    Mat *background;
    Mat *colorWheel;
    int colorIndex;
    int tolerance;
} State;

void resizeToMaxSize(Mat &m);

Vec3b rgb2YCbCr(const Vec3b &rgb);

Vec3b yCbCr2rgb(const Vec3b &yCbCr);

void onColorChanged(int pos, void *userdata);

void onToleranceChanged(int pos, void *userdata);

void showImages(State *state);

int main(int argc, char **argv)
{
    // Verifica se os dois parâmetros foram passados
    if (argc != 3)
    {
        cout << "Por favor, passe o caminho para as imagens de foreground e background assim que execute o programa!" << endl;
        return -1;
    }

    // Verifica se as imagens foram carregadas
    Mat foreground = imread(argv[1], IMREAD_COLOR);
    Mat background = imread(argv[2], IMREAD_COLOR);
    if (!foreground.data)
    {
        cout << "Caminho para imagem de foreground inválido" << endl;
        return -1;
    }
    if (!background.data)
    {
        cout << "Caminho para imagem de background inválido" << endl;
        return -1;
    }

    // redimensiona imagens para tamanho máximo
    resizeToMaxSize(foreground);
    resize(background, background, foreground.size());

    // faz roda de cores
    Mat colorWheel = Mat::zeros(Size(foreground.size().width * 2, 42), foreground.type());
    for (int x = 0; x < colorWheel.cols; x++)
    {
        double angle = (double)2 * M_PI * x / colorWheel.cols;
        Vec3b color = yCbCr2rgb(Vec3b(140, 126 + 126 * cos(angle), 126 + 126 * sin(angle)));
        for (int y = 0; y < colorWheel.rows; y++)
        {
            colorWheel.at<Vec3b>(Point(x, y)) = color;
        }
    }
    // registra trackbar na janela
    namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
    int colorIndex = 1;
    int tolerance = 80;

    Mat foregroundAsYCbCr;
    cvtColor(foreground,foregroundAsYCbCr,COLOR_RGB2YCrCb);
    State *state = new State{&foreground, &foregroundAsYCbCr, &background, &colorWheel, colorIndex, tolerance};


    createTrackbar("Tolerance", WINDOW_NAME, &tolerance, 255, onToleranceChanged, state);
    createTrackbar("Color", WINDOW_NAME, &colorIndex, colorWheel.size().width, onColorChanged, state);

    showImages(state);

    waitKey(0);
    delete[] state;
    return 0;
}

void resizeToMaxSize(Mat &m)
{
    if (m.size().width <= MAX_SIZE && m.size().height <= MAX_SIZE)
        return;

    Size size = Size(0, 0);
    double ratio = (double)m.size().width / m.size().height;

    if (ratio > 1)
    {
        size.width = MAX_SIZE;
        size.height = MAX_SIZE / ratio;
    }
    else
    {
        size.width = MAX_SIZE * ratio;
        size.height = MAX_SIZE;
    }
    resize(m, m, size);
}

Vec3b rgb2YCbCr(const Vec3b &rgb)
{
    Mat temp = Mat3b(rgb);
    cvtColor(temp, temp, COLOR_RGB2YCrCb);
    return temp.at<Vec3b>(Point(0, 0));
}

Vec3b yCbCr2rgb(const Vec3b &yCbCr)
{
    Mat temp = Mat3b(yCbCr);
    cvtColor(temp, temp, COLOR_YCrCb2RGB);
    return temp.at<Vec3b>(Point(0, 0));
}

void onToleranceChanged(int pos, void *userdata) {
    State *state = (State *)userdata;
    state->tolerance = pos;
    showImages(state);
}

void onColorChanged(int pos, void *userdata)
{
    State *state = (State *)userdata;
    state->colorIndex = pos;
    showImages(state);
}

void showImages(State *state)
{
    Vec3b chromaKey = state->colorWheel->at<Vec3b>(Point(state->colorIndex, 0));
    Vec3b chromaKeyAsYCbCr = rgb2YCbCr(chromaKey);
    Mat selectedColor = Mat::zeros(state->colorWheel->size(), state->colorWheel->type());
    for (int x = 0; x < selectedColor.cols; x++)
        for (int y = 0; y < selectedColor.rows; y++)
            selectedColor.at<Vec3b>(Point(x, y)) = chromaKey;

    Mat mask = Mat::zeros(state->foreground->size(), state->foreground->type());
    Mat result = Mat::zeros(state->foreground->size(), state->foreground->type());

    for (int x = 0; x < result.cols; x++)
    {
        for (int y = 0; y < result.rows; y++)
        {
            Vec3b foregroundPixelAsYCbCr = state->foregroundAsYCbCr->at<Vec3b>(Point(x, y));
            Vec3i difference = (Vec3i)chromaKeyAsYCbCr - (Vec3i)foregroundPixelAsYCbCr;
            double distance = sqrt(difference[1] * difference[1] + difference[2] * difference[2]);

            if (distance < state->tolerance)
            {
                result.at<Vec3b>(Point(x, y)) = state->background->at<Vec3b>(Point(x, y));
                mask.at<Vec3b>(Point(x, y)) = state->foreground->at<Vec3b>(Point(x, y));
            }
            else
            {
                result.at<Vec3b>(Point(x, y)) = state->foreground->at<Vec3b>(Point(x, y));
                mask.at<Vec3b>(Point(x, y)) = Vec3b(255, 255, 255);
            }
        }
    }

    Mat hcat1, hcat2, vcat;
    hconcat(*state->foreground, *state->background, hcat1);
    hconcat(mask, result, hcat2);
    vconcat(*state->colorWheel, selectedColor, vcat);
    vconcat(vcat, hcat1, vcat);
    vconcat(vcat, hcat2, vcat);

    imshow(WINDOW_NAME, vcat);
}