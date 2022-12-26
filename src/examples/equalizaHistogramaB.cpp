#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;
	
//-----------------------------------------
void equalizaHistogramaB(String nomeImagem)
{
	Mat imOrig;
	imOrig=imread(nomeImagem, IMREAD_COLOR);
	
	vector<Mat> bgr_canais;
	split(imOrig, bgr_canais);
	
  Mat imDestEqualB;
	equalizeHist(bgr_canais[0], imDestEqualB);
	
	Mat imEqDest;
	vector<Mat> imCanais;
  imCanais.push_back(imDestEqualB);
	imCanais.push_back(bgr_canais[1]);
  imCanais.push_back(bgr_canais[2]);
  
  
  merge(imCanais, imEqDest);
  
  String tituloOrigRGB="RGB Orig";
  namedWindow(tituloOrigRGB, WINDOW_AUTOSIZE);
  imshow(tituloOrigRGB, imOrig);
  
  String tituloEqRGB="Blue Equal";
  namedWindow(tituloEqRGB, WINDOW_AUTOSIZE);
  imshow(tituloEqRGB, imEqDest);

	waitKey(0);
	
}

//============================
int main(int argc, char** argv)
{
	equalizaHistogramaB("Lena.tif");
	return 0;
}

