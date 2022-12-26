#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

String nomeImagem1, nomeImagem2;

//------------------
void concatenaDuasImagens(String nomeImagem1, String nomeImagem2) {
  
  Mat im1, im2, im;
  String titulo;
  
  im1=imread(nomeImagem1, CV_LOAD_IMAGE_COLOR);
  im2=imread(nomeImagem2, CV_LOAD_IMAGE_COLOR);
  hconcat(im1, im2, im);
  //vconcat(im1, im2, im);
  
  titulo=nomeImagem1;
  titulo+=" + ";
  titulo+=nomeImagem2;
  
  namedWindow(titulo, WINDOW_AUTOSIZE);
  imshow(titulo, im);
  waitKey(0);
  
}

//------------------
int main( int argc, char** argv ) {
  
  nomeImagem1="Lena.tif";
  nomeImagem2="Lena256Cinza.png";
  concatenaDuasImagens(nomeImagem1, nomeImagem2);
  
  return 0;
  
}
