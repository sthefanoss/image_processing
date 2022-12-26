#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;
	
//-----------------------------------------
void equalizaHistogramaG(String nomeImagem)
{
	Mat imOrig;
	imOrig=imread(nomeImagem, IMREAD_COLOR);
	
	vector<Mat> bgr_canais;
	split(imOrig, bgr_canais);
	
  Mat imDestEqualG;
	equalizeHist(bgr_canais[1], imDestEqualG);
	
	Mat imEqDest;
	vector<Mat> imCanais;
	imCanais.push_back(bgr_canais[0]);
  imCanais.push_back(imDestEqualG);
  imCanais.push_back(bgr_canais[2]);
  
  
  merge(imCanais, imEqDest);
  
  String tituloOrigRGB="RGB Orig";
  namedWindow(tituloOrigRGB, WINDOW_AUTOSIZE);
  imshow(tituloOrigRGB, imOrig);
  
  String tituloEqRGB="Green Equal";
  namedWindow(tituloEqRGB, WINDOW_AUTOSIZE);
  imshow(tituloEqRGB, imEqDest);

	waitKey(0);
	
}

//============================
int main(int argc, char** argv)
{
	equalizaHistogramaG("Lena.tif");
	return 0;
}

