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
  
  //Media 3x3
  //float d=1./9.;
  //float filtro[3][3] = {d,d,d,d,d,d,d,d,d};
  
  //Media 5x5
  //float d=1./25.;
  //float filtro[5][5] = {d,d,d,d,d,d,d,d,d,d,d,d,d,d,d,d,d,d,d,d,d,d,d,d,d};
  
  //Media Ponderada 3x3
  float filtro[3][3] = {0,1./8.,0,1./8.,1./2.,1./8.,0,1./8.,0};
  
  Mat f(3, 3, CV_64F);
  
  //Mat f(5, 5, CV_64F);
  
  for(int i=0; i<3; i++)
    for(int j=0; j<3; j++)
    
  //for(int i=0; i<5; i++)
    //for(int j=0; j<5; j++)
      f.at<double>(i,j)=filtro[i][j];
  
  filter2D(imo, imr, -1, f, Point(-1,-1), 0, BORDER_REPLICATE);
  
  //namedWindow("RR: Media Aritmetica 3x3", WINDOW_AUTOSIZE);
  //imshow("RR: Media Aritmetica 3x3", imr);
  
  //namedWindow("RR: Media Aritmetica 5x5", WINDOW_AUTOSIZE);
  //imshow("RR: Media Aritmetica 5x5", imr);
  
  namedWindow("RR: Media Ponderada 3x3", WINDOW_AUTOSIZE);
  imshow("RR: Media Ponderada 3x3", imr);
  
  waitKey(0);
  return 0;
}
