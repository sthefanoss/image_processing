#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
  
  if(argc != 2) {
    cout << "Como utilizar: exibeimagem arquivo_da_imagem.extensão" << endl;
    return -1;
  }
  
  Mat imo;
  
  imo = imread(argv[1], IMREAD_COLOR);
  
  if(! imo.data) {
    cout << "Imagem não foi localizada!" << endl;
    return -1;
  }
  
  namedWindow("Imagem Original", WINDOW_AUTOSIZE);
  imshow("Imagem Original", imo);
  
  Mat imr;
  
  imr = imo.clone();
  
  medianBlur(imo,imr,5);
  
  namedWindow("Reducao de Ruido - Mediana", WINDOW_AUTOSIZE);
  imshow("Reducao de Ruido - Mediana", imr);
  
  waitKey(0);
  return 0;
}
