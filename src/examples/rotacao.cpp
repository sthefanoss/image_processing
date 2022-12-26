#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

//-----------------------------------------------
Mat rotacaoImagem(const Mat& imOrig, double ang)
{
  Point2f imCentr(imOrig.cols/2.0F, imOrig.rows/2.0F);
  Mat matRot = getRotationMatrix2D(imCentr, ang, 1.0);
  Mat imRot(Size(imOrig.size().height, imOrig.size().width), imOrig.type());
  warpAffine(imOrig, imRot, matRot, imOrig.size());
  return imRot;
}

//============================
int main(int argc, char** argv)
{
  Mat imRGB=imread("Lena.tif", IMREAD_COLOR);
	Mat imRot=rotacaoImagem(imRGB, 45);
  String nomeJanela="Rotacao";
  namedWindow(nomeJanela, WINDOW_AUTOSIZE);
  imshow(nomeJanela, imRot);
  
  waitKey(0);
	return 0;
}
