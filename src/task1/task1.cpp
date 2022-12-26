#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

void exibeJanelaDeImagem(const String &titulo, const Mat &imagem)
{
  namedWindow(titulo, WINDOW_AUTOSIZE);
  imshow(titulo, imagem);
}

int main(int argc, char **argv)
{
  Mat imRGB, imHSV, imYCrCb, imCinza;

  imRGB = imread("manhattan.png", IMREAD_COLOR);

  if (!imRGB.data)
  {
    cout << "Imagem não foi localizada!" << endl;
    return -1;
  }

  cvtColor(imRGB, imHSV, COLOR_RGB2HSV_FULL);
  cvtColor(imRGB, imYCrCb, COLOR_RGB2YCrCb);
  cvtColor(imRGB, imCinza, COLOR_RGB2GRAY);
  // As imagens devem ter o mesmo tamanho e a mesma quantidade de canais.
  // esse merge cria 3 canais iguais na imagem em cinza.
  merge((vector<Mat>){imCinza, imCinza, imCinza}, imCinza);

  hconcat(imRGB, imCinza, imRGB);
  hconcat(imHSV, imYCrCb, imHSV);
  vconcat(imRGB, imHSV, imRGB);

  exibeJanelaDeImagem("Grade de imagens", imRGB);

  waitKey(0);
  return 0;
}