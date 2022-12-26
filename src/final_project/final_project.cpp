#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

//============================
int main(int argc, char **argv)
{
  Mat input = imread("input.jpg", IMREAD_COLOR);
  Mat background = imread("background.jpg", IMREAD_COLOR);
  resize(background, background, input.size());
  Mat chromaKey = Mat::zeros(input.size(), input.type());
  Mat result = Mat::zeros(input.size(), input.type());
  Vec3b chromaColor = Vec3b(0, 255, 0); // Verde

  for (int y = 0; y < input.rows; y++)
  {
    for (int x = 0; x < input.cols; x++)
    {
      Point p = Point(x, y);
      Vec3b inputPixel = input.at<Vec3b>(p);
      Vec3b backgroundPixel = background.at<Vec3b>(p);

      float t = chromaColor.ddot(inputPixel) / sqrt(chromaColor.ddot(chromaColor) * inputPixel.ddot(inputPixel));
      if (t > 0.7)
      {
        result.at<Vec3b>(p) = backgroundPixel;
        chromaKey.at<Vec3b>(p) = chromaColor;
      }
      else
      {
        result.at<Vec3b>(p) = inputPixel;
        chromaKey.at<Vec3b>(p) =  Vec3b(0, 0, 0);
      }
    }
  }

  hconcat(input, background, input);
  hconcat(chromaKey, result, chromaKey);
  vconcat(input, chromaKey, input);



  String nomeJanela1 = "Resultado";
  namedWindow(nomeJanela1, WINDOW_AUTOSIZE);
  imshow(nomeJanela1, input);

  waitKey(0);
  return 0;
}
