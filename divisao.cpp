#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

//---------------------------------------------
Mat imagemDIVconstante(const Mat& im1, int fat)
{
  Mat im;
  
  im=im1/fat;
  
  return im;
  
}

//============================
int main(int argc, char** argv)
{
  Mat imRGB=imread("LenaSoma.jpg", IMREAD_COLOR);
  
  Mat imDiv = imagemDIVconstante(imRGB, 2);
  
  String nomeJanelaO="IMAGEM ORIGIONAL";
  namedWindow(nomeJanelaO, WINDOW_AUTOSIZE);
  imshow(nomeJanelaO, imRGB);
  
  String nomeJanela="DIVISAO por 2";
  namedWindow(nomeJanela, WINDOW_AUTOSIZE);
  imshow(nomeJanela, imDiv);
  
  waitKey(0);
	return 0;
}
