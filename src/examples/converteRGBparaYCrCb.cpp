#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

//-----------------------------------
int exibeImagemRGBparaYCrCb(String nomeImagemRGB) {
  
  String titulo1, titulo2;
  Mat imRGB;
  
  imRGB = imread(nomeImagemRGB, CV_LOAD_IMAGE_COLOR);
  
  if(! imRGB.data) {
    cout << "Imagem não foi localizada!" << endl;
    return -1;
  }
  else {
    titulo1=nomeImagemRGB;
    titulo1+=" (RGB)";
    namedWindow(titulo1, WINDOW_AUTOSIZE);
    imshow(titulo1, imRGB);
    
    Mat imYCrCb;
    cvtColor(imRGB, imYCrCb, CV_RGB2YCrCb);
    
    imwrite("LenaYCrCb.tif", imYCrCb);
    
    titulo2=nomeImagemRGB;
    titulo2+=" (YCrCb)";
    namedWindow(titulo2, WINDOW_AUTOSIZE);
    imshow(titulo2, imYCrCb);
  }
  
  waitKey(0);
  return 0;
  
}

//------------------------------
int main( int argc, char** argv)
{
  
  int r;
  
  r=exibeImagemRGBparaYCrCb("Lena.tif");
  
  return 0;
  
}


