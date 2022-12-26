#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

// Variáveis globais

int threshold_value = 0;
int threshold_type = 3;;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

Mat src, src_gray, dst;
char window_name[50] = "Limiarização do Histograma";

char trackbar_type[150] = "Tipos: \n 0: Binário \n 1: Binário Invertido \n 2: Truncado \n 3: Para zero \n 4: Para zero invertido \n\n Esc: Encerrar programa";
char trackbar_value[6] = "Value";

// Protótipos de funções
void Limiarizacao( int, void* );

// Função main
int main( int argc, char** argv )
{
  // Leitura da imagem original
  src = imread( argv[1], 1 );

  // Converte a imagem para tons de cinza
  cvtColor( src, src_gray, CV_RGB2GRAY );

  // Cria uma janela para exibição dos resultados
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );

  // Cria uma barra de comando para escolher o tipo de limiarização
  createTrackbar( trackbar_type,
                  window_name, &threshold_type,
                  max_type, Limiarizacao );

  createTrackbar( trackbar_value,
                  window_name, &threshold_value,
                  max_value, Limiarizacao );


  // Executa a função de Limiarização
  Limiarizacao( 0, 0 );
  

  // Aguarda pela finalização do programa
  while(true)
   {
    int c;
    
    c = waitKey( 20 );
    if( (char) c == 27 )
       break; 
   }

}


// Função Limiarizacao
void Limiarizacao( int, void* )
{

  threshold( src_gray, dst, threshold_value, max_BINARY_value, threshold_type );

  imshow( window_name, dst );
  
 
}
