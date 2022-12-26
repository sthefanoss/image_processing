#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;
	
//-----------------------------------------
void equalizaHistogramaR(String nomeImagem)
{
	Mat imOrig;
	imOrig=imread(nomeImagem, IMREAD_COLOR);
	
	vector<Mat> bgr_canais;
	split(imOrig, bgr_canais);
	
  Mat imDestEqualR;
	equalizeHist(bgr_canais[2], imDestEqualR);
	
	Mat imEqDest;
	vector<Mat> imCanais;
	imCanais.push_back(bgr_canais[0]);
  imCanais.push_back(bgr_canais[1]);
  imCanais.push_back(imDestEqualR);
  
  merge(imCanais, imEqDest);
  
  String tituloOrigRGB="RGB Orig";
  namedWindow(tituloOrigRGB, WINDOW_AUTOSIZE);
  imshow(tituloOrigRGB, imOrig);
  
  String tituloEqRGB="Red Equal";
  namedWindow(tituloEqRGB, WINDOW_AUTOSIZE);
  imshow(tituloEqRGB, imEqDest);

	waitKey(0);
	
}

//============================
int main(int argc, char** argv)
{
	equalizaHistogramaR("Lena.tif");
	return 0;
}

