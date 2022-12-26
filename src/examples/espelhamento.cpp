#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

//------------------------------------------------
Mat espelhamentoImagem(const Mat& imOrig, int cod)
{
  Mat imDest;
  flip(imOrig,imDest,cod);
  return imDest;
}

//============================
int main(int argc, char** argv)
{
  Mat imRGB=imread("Lena.tif", CV_LOAD_IMAGE_COLOR);
  
  Mat imEspO = espelhamentoImagem(imRGB, 0);
  String nomeJanelaO="Espelhamento ORIGEM";
  namedWindow(nomeJanelaO, CV_WINDOW_AUTOSIZE);
  imshow(nomeJanelaO, imEspO);
  
  Mat imEspY = espelhamentoImagem(imRGB, 1);
  String nomeJanelaY="Espelhamento EIXO-Y";
  namedWindow(nomeJanelaY, CV_WINDOW_AUTOSIZE);
  imshow(nomeJanelaY, imEspY);
  
  Mat imEspX = espelhamentoImagem(imRGB, -1);
  String nomeJanelaX="Espelhamento EIXO-X";
  namedWindow(nomeJanelaX, CV_WINDOW_AUTOSIZE);
  imshow(nomeJanelaX, imEspX);
  
  waitKey(0);
	return 0;
}
