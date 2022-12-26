#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

//---------------------------------------------
Mat combinacaoLinear(const Mat& im1, const Mat& im2, float alpha)
{
  float beta;
  Mat im3;
  
  beta=1-alpha;
  
  addWeighted(im1, alpha, im2, beta, 0.0, im3);

  return im3;
}

//============================
int main(int argc, char** argv)
{
  Mat imRGB1=imread("Lena.tif", IMREAD_COLOR);
  Mat imRGB2=imread("logoInter.jpg", IMREAD_COLOR);
  
  Mat imCL = combinacaoLinear(imRGB1, imRGB2, 0.75);
  
  String nomeJanela1="IMAGEM 1";
  namedWindow(nomeJanela1, WINDOW_AUTOSIZE);
  imshow(nomeJanela1, imRGB1);
  
  String nomeJanela2="IMAGEM 2";
  namedWindow(nomeJanela2, WINDOW_AUTOSIZE);
  imshow(nomeJanela2, imRGB2);
  
  String nomeJanelaCL="COMBINACAO LINEAR";
  namedWindow(nomeJanelaCL, WINDOW_AUTOSIZE);
  imshow(nomeJanelaCL, imCL);
  imwrite("LenaCL.jpg", imCL);
  
  waitKey(0);
	return 0;
}
