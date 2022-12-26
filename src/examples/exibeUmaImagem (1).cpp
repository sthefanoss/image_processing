#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

//-----------------------------------
int exibeImagem(String nomeImagem) {
  
  Mat image;
  
  image = imread(nomeImagem, IMREAD_COLOR);
  
  if(! image.data) {
    cout << "Imagem não foi localizada!" << endl;
    return -1;
  }
  
  namedWindow(nomeImagem, WINDOW_AUTOSIZE);
  imshow(nomeImagem, image);
  
  waitKey(0);
  return 0;
  
}

//-------------------------------
int main( int argc, char** argv )
{
  int r;
  
  r=exibeImagem("Lena.tif");
  
  return 0;
}
