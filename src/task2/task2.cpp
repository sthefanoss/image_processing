#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

struct showImagesArgs
{
  String *windowName;
  Mat *input;
  int size;
  int centralValue;
};

Mat makeLowpassFilter(const unsigned &size, const double & = 1.0);

void showImages(showImagesArgs *args);

void onSizeChanged(int pos, void *userdata);

void onCentralValueChanged(int pos, void *userdata);

int main(int argc, char **argv)
{

  if (argc != 2)
  {
    cout << "Como utilizar: exibeimagem arquivo_da_imagem.extensão" << endl;
    return -1;
  }

  Mat input = imread(argv[1], IMREAD_COLOR);

  if (!input.data)
  {
    cout << "Imagem não foi localizada!" << endl;
    return -1;
  }
  int size = 3;
  int centralValue = 8;
  String windowName = "Imagens Filtradas";

  showImagesArgs *args = new showImagesArgs{&windowName, &input, size, centralValue};

  namedWindow(windowName, WINDOW_AUTOSIZE);
  createTrackbar("Tamanho NxN (apenas ímpar)", windowName, &size, 64, onSizeChanged, args);
  setTrackbarMin("Tamanho NxN (apenas ímpar)", windowName, 3);
  createTrackbar("Valor central (média ponderada)", windowName, &centralValue, 255, onCentralValueChanged, args);
  setTrackbarMin("Valor central (média ponderada)", windowName, 1);
  showImages(args);

  waitKey(0);
  delete[] args;
  return 0;
}

void onSizeChanged(int pos, void *userdata)
{
  if (pos % 2 == 0)
    return;

  showImagesArgs *args = (showImagesArgs *)userdata;
  args->size = pos;
  showImages(args);
}

void onCentralValueChanged(int pos, void *userdata)
{
  showImagesArgs *args = (showImagesArgs *)userdata;
  args->centralValue = pos;
  showImages(args);
}

Mat makeLowpassFilter(const unsigned &size, const double &centralValue)
{
  double sum = (size * size - 1) + centralValue;
  unsigned halfSize = size / 2;

  Mat kernel(size, size, CV_64F);
  for (unsigned i = 0; i < size; i++)
  {
    bool isIInCenter = (i == halfSize);
    for (unsigned j = 0; j < size; j++)
    {
      bool isJInCenter = (j == halfSize);
      kernel.at<double>(Point(i, j)) = (isIInCenter && isJInCenter) ? centralValue / sum : 1.0 / sum;
    }
  }

  return kernel;
}

void showImages(showImagesArgs *args)
{
  Mat lowPassFilteredImage, lowPassPonderedFilteredImage, bluredImage;

  Mat lowPassFilter = makeLowpassFilter(args->size);
  Mat lowPassPonderedFilter = makeLowpassFilter(args->size, (double)args->centralValue);

  filter2D(*args->input, lowPassFilteredImage, -1, lowPassFilter, Point(-1, -1), 0, BORDER_REPLICATE);
  filter2D(*args->input, lowPassPonderedFilteredImage, -1, lowPassPonderedFilter, Point(-1, -1), 0, BORDER_REPLICATE);

  medianBlur(*args->input, bluredImage, args->size);

  Mat h1, h2, v1;
  hconcat(*args->input, bluredImage, h1);
  hconcat(lowPassFilteredImage, lowPassPonderedFilteredImage, h2);
  vconcat(h1, h2, v1);

  imshow(*args->windowName, v1);
}
