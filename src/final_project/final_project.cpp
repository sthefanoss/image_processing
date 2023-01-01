#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>

#define MAX_HUE 255
#define MAX_SIZE 500
#define COLOR_WEEL_SIZE 512
using namespace cv;
using namespace std;

typedef struct
{
  String *windowName;
  Mat *input;
  Mat *inputYCbCr;
  Mat *background;
  Mat *colorWeel;
  int colorIndex;
  int colorTolerance;
} showImagesArgs;

Vec3b rgb2yCbCr(const Vec3b &pixel);

void showImages(showImagesArgs *args);

void showControllers(showImagesArgs *args);

void onCbCrToleranceChanged(int pos, void *userdata);

void onColorChanged(int pos, void *userdata);

void resizeToMaxSize(Mat &m);

//============================
int main(int argc, char **argv)
{
  Mat input = imread("input.jpg", IMREAD_COLOR);
  resizeToMaxSize(input);

  Mat inputYCbCr = Mat::zeros(input.size(), input.type());
  for (int y = 0; y < input.rows; y++)
    for (int x = 0; x < input.cols; x++)
      inputYCbCr.at<Vec3b>(Point(x, y)) = rgb2yCbCr(input.at<Vec3b>(Point(x, y)));

  Mat background = imread("background.jpg", IMREAD_COLOR);
  resize(background, background, input.size());

  int colorTolerance = 104;
  String nomeJanela1 = "Resultado";
  String nomeJanela2 = "Controles";

  namedWindow(nomeJanela1, WINDOW_AUTOSIZE);
  namedWindow(nomeJanela2, WINDOW_AUTOSIZE);
  Mat colorWeel = Mat::zeros(Size(COLOR_WEEL_SIZE, 42), input.type());
  for (int x = 0; x < colorWeel.cols; x++)
  {
    Vec3b color = Vec3b(140, 126 + 126 * cos(2 * M_PI * x / colorWeel.cols), 126 + 126 * sin(2 * M_PI * x / colorWeel.cols));
    for (int y = 0; y < colorWeel.rows; y++)
    {
      colorWeel.at<Vec3b>(Point(x, y)) = color;
    }
  }
  cvtColor(colorWeel, colorWeel, COLOR_YCrCb2BGR);

  int selectedColor = 302;

  showImagesArgs *args = new showImagesArgs{&nomeJanela1, &input, &inputYCbCr,
                                            &background, &colorWeel, selectedColor, colorTolerance};

  createTrackbar("Tolerance",
                 nomeJanela2, &colorTolerance,
                 MAX_HUE, onCbCrToleranceChanged, args);
  createTrackbar("Color",
                 nomeJanela2, &selectedColor,
                 COLOR_WEEL_SIZE, onColorChanged, args);

  showControllers(args);
  showImages(args);
  waitKey(0);

  delete[] args;
  return 0;
}

Vec3b rgb2yCbCr(const Vec3b &pixel)
{
  return Vec3b{
      (uchar)round(0.299 * pixel[0] + 0.587 * pixel[1] + 0.114 * pixel[2]),
      (uchar)round(128 + -0.168736 * pixel[0] - 0.331264 * pixel[1] + 0.5 * pixel[2]),
      (uchar)round(128 + 0.5 * pixel[0] - 0.418688 * pixel[1] - 0.081312 * pixel[2])};
};

void onCbCrToleranceChanged(int pos, void *userdata)
{
  showImagesArgs *args = (showImagesArgs *)userdata;
  args->colorTolerance = pos;
  showImages(args);
}

void onColorChanged(int pos, void *userdata)
{
  showImagesArgs *args = (showImagesArgs *)userdata;
  args->colorIndex = pos;
  showControllers(args);
  showImages(args);
}

void showImages(showImagesArgs *args)
{
  Mat chromaKey = Mat::zeros(args->input->size(), args->input->type());
  Mat result = Mat::zeros(args->input->size(), args->input->type());
  Vec3b foo = rgb2yCbCr(args->colorWeel->at<Vec3b>(Point(args->colorIndex, 0)));

  for (int y = 0; y < args->input->rows; y++)
  {
    for (int x = 0; x < args->input->cols; x++)
    {
      Point p = Point(x, y);
      Vec3b inputPixel = args->input->at<Vec3b>(p);
      Vec3b backgroundPixel = args->background->at<Vec3b>(p);

      Vec3i chroma2YCbCr = (Vec3i)foo - (Vec3i)args->inputYCbCr->at<Vec3b>(p);
      chroma2YCbCr[0] = 0;
      double Tolerance = sqrt(chroma2YCbCr.ddot(chroma2YCbCr));

      if (Tolerance < args->colorTolerance)
      {
        result.at<Vec3b>(p) = backgroundPixel;
        chromaKey.at<Vec3b>(p) = inputPixel;
      }
      else
      {
        result.at<Vec3b>(p) = inputPixel;
        chromaKey.at<Vec3b>(p) = Vec3b(255, 255, 255);
      }
    }
  }

  Mat h1, h2, v;
  cv::hconcat(*args->input, *args->background, h1);
  cv::hconcat(chromaKey, result, h2);
  cv::vconcat(h1, h2, v);
  cv::imshow(*args->windowName, v);
}

void resizeToMaxSize(Mat &m)
{
  if (m.size[0] < MAX_SIZE && m.size[1] < MAX_SIZE)
    return;

  Size size = Size(0, 0);
  Size currentSize = m.size();
  double ratio = (double)currentSize.height / currentSize.width;

  if (ratio > 1)
  {
    size.height = MAX_SIZE;
    size.width = MAX_SIZE / ratio;
  }
  else
  {
    size.height = MAX_SIZE * ratio;
    size.width = MAX_SIZE;
  }

  resize(m, m, size);
}

void showControllers(showImagesArgs *args)
{

  Mat color = Mat::zeros(args->colorWeel->size(), args->colorWeel->type());
  for (int y = 0; y < color.rows; y++)
    for (int x = 0; x < color.cols; x++)
      color.at<Vec3b>(Point(x, y)) = args->colorWeel->at<Vec3b>(Point(args->colorIndex, 0));
  cv::vconcat(*args->colorWeel, color, color);
  cv::imshow("Controles", color);
}