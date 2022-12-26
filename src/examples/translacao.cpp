#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

//-----------------------------------------------------
Mat translacaoImagem(const Mat& imOrig, int tx, int ty)
{
  Mat matTrans(imOrig.rows+2*abs(ty), imOrig.cols+2*abs(tx), CV_8UC3, Scalar(0,0,0));
  imOrig.copyTo(matTrans(Rect(abs(tx), abs(ty), imOrig.cols, imOrig.rows)));
  return Mat(matTrans, Rect(abs(tx)+tx, abs(ty)+ty, imOrig.cols, imOrig.rows));
}

//============================
int main(int argc, char** argv)
{
  Mat imRGB=imread("Lena.tif", IMREAD_COLOR);
  Mat imTrans = translacaoImagem(imRGB, 50, 100);
  String nomeJanela="Translacao";
  namedWindow(nomeJanela, WINDOW_AUTOSIZE);
  imshow(nomeJanela, imTrans);
  
  waitKey(0);
	return 0;
}
