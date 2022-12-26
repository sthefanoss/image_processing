#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

// DETECÇÃO DE BORDAS VERSÃO 1

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{

  // LEITURA E EXIBIÇÃO DA IMAGEM ORIGINAL

	if(argc != 2)
    {
     printf("Como utilizar: bordas arquivo_da_imagem.extensão\n");
     return -1;
    }

    Mat imo;
    imo = imread(argv[1], IMREAD_COLOR);   

    if(! imo.data)                            
    {
        printf("Imagem não foi localizada!\n");
        return -1;
    }
    
    namedWindow("Imagem Original", WINDOW_NORMAL);
    imshow("Imagem Original", imo);

	// DEFINE UM FILTRO PARA A DETECÇÃO DE BORDAS
	
	// FILTRO PARA DETECÇÃO DE PONTOS ISOLADOS
  float filtro[3][3] = { 	0, -1, 0, -1, 4, -1, 0, -1, 0  }; 
	
											

  // COPIA A MATRIZ DA IMAGEM ORIGINAL
	Mat imr;
  imr = imo.clone();

	Mat ff(3, 3, CV_64F);
	for(int i=0; i<3; i++)
		for(int j=0; j<3; j++)
			ff.at<double>(i,j) = filtro[i][j];

	// DETECTA BORDAS COM O FILTRO: LAPLACIANO
	filter2D(imo, imr, -1, ff, Point(-1, -1), 0, BORDER_REPLICATE);

	vector<Mat> bgr_imr;
  split(imr, bgr_imr);

	bgr_imr[0] = 255-bgr_imr[0];
	bgr_imr[1] = 255-bgr_imr[1];
	bgr_imr[2] = 255-bgr_imr[2];

	merge(bgr_imr, imr);

	// EXIBE A IMAGEM RESULTANTE FILTRADA
	namedWindow("Imagem Resultante", WINDOW_NORMAL);
  imshow("Imagem Resultante", imr);
  
  Mat imCinza;
  cvtColor(imr, imCinza, COLOR_RGB2GRAY);
  
  // EXIBE A IMAGEM RESULTANTE FILTRADA EM TONS DE CINZA
	namedWindow("Imagem Cinza", WINDOW_NORMAL);
  imshow("Imagem Cinza", imCinza);

  waitKey(0);
  return 0;

}





