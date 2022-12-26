#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

//-----------------------------------
int exibeImagemRGBparaCinza(String nomeImagemRGB) {
  
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
    
    Mat imCinza;
    cvtColor(imRGB, imCinza, CV_RGB2GRAY);
    
    vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9); // Nível de compressao [0,9]
    imwrite("Lena256Cinza.png", imCinza, compression_params);
    
    titulo2="Lena.png";
    titulo2+=" (256 tons de cinza)";
    namedWindow(titulo2, WINDOW_AUTOSIZE);
    imshow(titulo2, imCinza);
  }
  
  waitKey(0);
  return 0;
  
}

//------------------------------
int main( int argc, char** argv)
{
  
  int r;
  
  r=exibeImagemRGBparaCinza("Lena.tif");
  
  return 0;
  
}


