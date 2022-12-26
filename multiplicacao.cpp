#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

//---------------------------------------------
Mat imagemMULTconstante(const Mat& im, float fat)
{
  Mat imM;
  
  imM=im*fat;
  
  return imM;
}

//============================
int main(int argc, char** argv)
{
  Mat imRGB1=imread("Lena.tif", IMREAD_COLOR);
  
  Mat imMult = imagemMULTconstante(imRGB1, 0.5);
  
  String nomeJanelaO="ORIGINAL";
  namedWindow(nomeJanelaO, WINDOW_AUTOSIZE);
  imshow(nomeJanelaO, imRGB1);
  
  String nomeJanelaM="MULTIPLICACAO x 0.5";
  namedWindow(nomeJanelaM, WINDOW_AUTOSIZE);
  imshow(nomeJanelaM, imMult);
  imwrite("LenaMult.jpg", imMult);
  
  waitKey(0);
	return 0;
}
