#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

//============================
int main(int argc, char** argv)
{
  Mat im2 = imread("Lena.tif", IMREAD_COLOR);
  Mat im1 = imread("Paris.jpg", IMREAD_COLOR);
  Mat imAlpha = imread("LenaAlpha.tif", IMREAD_COLOR);
  
  Mat imRGB1 = im1;
  Mat imRGB2 = im2;
  
  imRGB1.convertTo(imRGB1, CV_32FC3);
  imRGB2.convertTo(imRGB2, CV_32FC3);
  imAlpha.convertTo(imAlpha, CV_32FC3, 1.0/255);
  Mat imMist = Mat::zeros(imRGB1.size(), imRGB1.type());
  multiply(imAlpha, imRGB1, imRGB1);
  multiply(Scalar::all(1.0)-imAlpha, imRGB2, imRGB2);
  add(imRGB1, imRGB2, imMist);
  
  String nomeJanela1="PRINCIPAL";
  namedWindow(nomeJanela1, WINDOW_AUTOSIZE);
  imshow(nomeJanela1, im1);
  
  String nomeJanela2="FUNDO";
  namedWindow(nomeJanela2, WINDOW_AUTOSIZE);
  imshow(nomeJanela2, im2);
  
  String nomeJanelaA="ALPHA";
  namedWindow(nomeJanelaA, WINDOW_AUTOSIZE);
  imshow(nomeJanelaA, imAlpha);
  
  String nomeJanelaM="MISTURA";
  namedWindow(nomeJanelaM, WINDOW_AUTOSIZE);
  imshow(nomeJanelaM, imMist/255);
  imwrite("LenaMist.jpg", imMist/255);
  
  waitKey(0);
  return 0;
}
