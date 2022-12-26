#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
  Mat src, dst;

  char source_window[40] = "Imagem Original (Tons de Cinza)";
  char equalized_window[20] = "Imagem Equalizada";

  // Leitura da imagem original
  src = imread( argv[1], 1 );

  if( !src.data )
    { 
     printf("Como usar o programa: ./EqualizacaoHistograma <path_to_image>\n");
     return -1;
    }

  /// Converte imagem para tons de cinza
  cvtColor( src, src, CV_BGR2GRAY );

  /// Equaliza o histograma da imagem
  equalizeHist( src, dst );

  /// Exibe os resultados
  namedWindow( source_window, CV_WINDOW_AUTOSIZE );
  namedWindow( equalized_window, CV_WINDOW_AUTOSIZE );

  imshow( source_window, src );
  imshow( equalized_window, dst );

  waitKey(0);

  return 0;
}
