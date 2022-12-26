#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

//--------------------------------------------------
Mat subtracaoImagens(const Mat& im1, const Mat& im2)
{
  Mat imSub;
  imSub=im1-im2;
  return imSub;
}

//============================
int main(int argc, char** argv)
{
  Mat imRGB1=imread("LenaSoma.jpg", IMREAD_COLOR);
  Mat imRGB2=imread("ruido.jpg", IMREAD_COLOR);
  
  Mat imSubtr = subtracaoImagens(imRGB1, imRGB2);
  
  String nomeJanelaO="SOMA COM RUIDO";
  namedWindow(nomeJanelaO, WINDOW_AUTOSIZE);
  imshow(nomeJanelaO, imRGB1);
  
  String nomeJanelaR="RUIDO";
  namedWindow(nomeJanelaR, WINDOW_AUTOSIZE);
  imshow(nomeJanelaR, imRGB2);
  
  String nomeJanelaS="SUBTRACAO";
  namedWindow(nomeJanelaS, WINDOW_AUTOSIZE);
  imshow(nomeJanelaS, imSubtr);
  imwrite("LenaSubtr.jpg", imSubtr);
  
  waitKey(0);
	return 0;
}
