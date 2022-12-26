#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

// DETECÇÃO DE BORDAS VERSÃO 3

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{

  // LEITURA E EXIBIÇÃO DA IMAGEM ORIGINAL

	if(argc != 2)
    {
     printf("Como utilizar: bordas3 arquivo_da_imagem.extensão\n");
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
	
	// FILTRO PRËWITT
  float filtrox[3][3] = { -1, 0, 1, -1, 0, 1, -1, 0, 1 };
	float filtroy[3][3] = { -1, -1, -1, 0, 0, 0, 1, 1, 1 };
													

  // COPIA A MATRIZ DA IMAGEM ORIGINAL
	Mat imrx, imry, imr;
  imr = imo.clone();

	Mat ffx(3, 3, CV_64F);
	for(int i=0; i<3; i++)
		for(int j=0; j<3; j++)
			ffx.at<double>(i,j) = filtrox[i][j];

	Mat ffy(3, 3, CV_64F);
	for(int i=0; i<3; i++)
		for(int j=0; j<3; j++)
			ffy.at<double>(i,j) = filtroy[i][j];

	// FAZ A CONVOLUÇÃO DA MATRIZ ORIGINAL COM A MATRIZ DO FILTRO
	// OBTÉM A IMAGEM RESULTANTE FILTRADA EM imr
	filter2D(imo, imrx, -1, ffx, Point(-1, -1), 0, BORDER_REPLICATE);
	filter2D(imo, imry, -1, ffx, Point(-1, -1), 0, BORDER_REPLICATE);

	imr = imrx+imry;

	vector<Mat> bgr_imr;
  split( imr, bgr_imr );

	bgr_imr[0] = 255-bgr_imr[0];
	bgr_imr[1] = 255-bgr_imr[1];
	bgr_imr[2] = 255-bgr_imr[2];

	merge( bgr_imr, imr );

	// EXIBE A IMAGEM RESULTANTE FILTRADA
	namedWindow("Imagem Resultante", WINDOW_NORMAL);
  imshow("Imagem Resultante", imr);

  waitKey(0);
  return 0;

}





