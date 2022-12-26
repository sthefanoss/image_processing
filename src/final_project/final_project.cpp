#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#define MAX_HUE 1000
#define MAX_LUMINANCE 1000

using namespace cv;
using namespace std;

struct showImagesArgs
{
  String *windowName;
  Mat *input;
  Mat *background;
  Mat *chromaKey;
  Mat *result;
  Vec3b *chromaColor;
  int *colorThreshold;
  int *luminanceThreshold;
};

void showImages(showImagesArgs *args);

void onHueChanged(int pos, void *userdata);

void onLuminanceChanged(int pos, void *userdata);

//============================
int main(int argc, char **argv)
{
  Mat input = imread("input.jpg", IMREAD_COLOR);
  Mat background = imread("background.jpg", IMREAD_COLOR);
  Mat chromaKey;
  Mat result;
  Vec3b chromaColor = Vec3b(0, 255, 0); // Verde
  int colorThreshold = 700;
  int luminanceThreshold = 200;
  String nomeJanela1 = "Resultado";

  showImagesArgs *args = new showImagesArgs{
      &nomeJanela1, &input, &background, &chromaKey,
      &result, &chromaColor, &colorThreshold, &luminanceThreshold};

  resize(background, background, input.size());
  namedWindow(nomeJanela1, WINDOW_AUTOSIZE);

  createTrackbar("Hue",
                 nomeJanela1, &colorThreshold,
                 MAX_HUE, onHueChanged, args);

  createTrackbar("Light",
                 nomeJanela1, &luminanceThreshold,
                 MAX_LUMINANCE, onLuminanceChanged, args);

  showImages(args);
  waitKey(0);

  delete[] args;
  return 0;
}

void onHueChanged(int pos, void *userdata)
{
  showImagesArgs *args = (showImagesArgs *)userdata;
  *args->colorThreshold = pos;
  showImages(args);
}

void onLuminanceChanged(int pos, void *userdata)
{
  showImagesArgs *args = (showImagesArgs *)userdata;
  *args->luminanceThreshold = pos;
  showImages(args);
}

void showImages(showImagesArgs *args)
{
  *args->chromaKey = Mat::zeros(args->input->size(), args->input->type());
  *args->result = Mat::zeros(args->input->size(), args->input->type());

  float tNormalized = (float)*args->colorThreshold / MAX_HUE;
  float hNormalized = (float)*args->luminanceThreshold / MAX_LUMINANCE;

  for (int y = 0; y < args->input->rows; y++)
  {
    for (int x = 0; x < args->input->cols; x++)
    {
      Point p = Point(x, y);
      Vec3b inputPixel = args->input->at<Vec3b>(p);
      Vec3b backgroundPixel = args->background->at<Vec3b>(p);
      // ajusta se o pixel for 100% preto, para não dar divisão por zero no cálculo de t
      if (!backgroundPixel[0] && !backgroundPixel[1] && !backgroundPixel[2])
      {
        backgroundPixel[0] = 1;
        backgroundPixel[1] = 1;
        backgroundPixel[2] = 1;
      }
      // calcula o "ângulo" entre a cor do pixel e a cor do chroma
      float t = args->chromaColor->ddot(inputPixel) / sqrt(args->chromaColor->ddot(*args->chromaColor) * inputPixel.ddot(inputPixel));
      float h = sqrt(inputPixel.ddot(inputPixel) / (3 * 255.0 * 255.0));
      if (t > tNormalized && h > hNormalized)
      {
        args->result->at<Vec3b>(p) = backgroundPixel;
        args->chromaKey->at<Vec3b>(p) = inputPixel;
      }
      else
      {
        args->result->at<Vec3b>(p) = inputPixel;
        args->chromaKey->at<Vec3b>(p) = Vec3b(255, 255, 255);
      }
    }
  }

  Mat h1, h2, v;
  cv::hconcat(*args->input, *args->background, h1);
  cv::hconcat(*args->chromaKey, *args->result, h2);
  cv::vconcat(h1, h2, v);
  cv::imshow(*args->windowName, v);
}