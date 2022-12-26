#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

//---------------------------------------------
Mat somaImagens(const Mat& im1, const Mat& im2)
{
  Mat imS;
  imS=im1+im2;
  return imS;
}

//============================
int main(int argc, char** argv)
{
  Mat imRGB1=imread("Lena.tif", IMREAD_COLOR);
  Mat imRGB2=imread("ruido.jpg", IMREAD_COLOR);
  
  Mat imSoma = somaImagens(imRGB1, imRGB2);
  
  String nomeJanelaO="IMAGEM ORIGINAL";
  namedWindow(nomeJanelaO, WINDOW_AUTOSIZE);
  imshow(nomeJanelaO, imRGB1);
  
  String nomeJanelaR="RUIDO";
  namedWindow(nomeJanelaR, WINDOW_AUTOSIZE);
  imshow(nomeJanelaR, imRGB2);
  
  String nomeJanelaS="SOMA 2 IMAGENS";
  namedWindow(nomeJanelaS, WINDOW_AUTOSIZE);
  imshow(nomeJanelaS, imSoma);
  imwrite("LenaSoma.jpg", imSoma);
  
  waitKey(0);
	return 0;
}
