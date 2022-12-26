#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/**
 * @function main
 */
int main( int argc, char** argv )
{
  Mat src, dst;

  // Leitura da imagem original
  src = imread( argv[1], 1 );

  if( !src.data )
    { return -1; }

  // Separa a imagem em 3 canais de cores (RGB)
  vector<Mat> bgr_planes;
  split( src, bgr_planes );

  // Estabelece o número de barras dos histogramas
  int histSize = 256;

  // Configura os intervalos para RGB
  float range[] = { 0, 256 } ;
  const float* histRange = { range };

  bool uniform = true; bool accumulate = false;

  Mat b_hist, g_hist, r_hist;

  /// Calcula os histogramas para cada canal de cor
  calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
  calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
  calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

  // Determina os histogramas
  int hist_w = 512; int hist_h = 400;
  int bin_w = cvRound( (double) hist_w/histSize );

  Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

  // Normaliza o resultado para [ 0, histImage.rows ]
  normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
  normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
  normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

  // Desenha os histogramas para cada canal de cor
  for( int i = 1; i < histSize; i++ )
  {
      line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                       Scalar( 255, 0, 0), 2, 8, 0  );
      line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
                       Scalar( 0, 255, 0), 2, 8, 0  );
      line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
                       Scalar( 0, 0, 255), 2, 8, 0  );
  }

  // Ativa a janela de exibição
  namedWindow("Imagem - Canal R", CV_WINDOW_AUTOSIZE );
  imshow("Imagem - Canal R", bgr_planes[0] );
  
  namedWindow("Imagem - Canal G", CV_WINDOW_AUTOSIZE );
  imshow("Imagem - Canal G", bgr_planes[1] );
  
  namedWindow("Imagem - Canal B", CV_WINDOW_AUTOSIZE );
  imshow("Imagem - Canal B", bgr_planes[2] );
  
  namedWindow("Histogramas (RGB)", CV_WINDOW_AUTOSIZE );
  imshow("Histogramas (RGB)", histImage );

  waitKey(0);

  return 0;
}
