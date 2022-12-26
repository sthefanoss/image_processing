#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

//---------------------------------------------
Mat realceMedia(const Mat& imO)
{
  Mat im;
  float a=4;
  float w=9*a-1;
  float d=1./9.;
  im = imO.clone();
  float filtro[3][3] = {-1., -1., -1.,
                        -1.,  w, -1.,
                        -1., -1., -1.};
  Mat f(3, 3, CV_64F);
  for(int i=0; i<3; i++)
    for(int j=0; j<3; j++)
      f.at<double>(i,j)=d*filtro[i][j];
  filter2D(imO, im, -1, f, Point(-1, -1),0,BORDER_REPLICATE);
  return im;
}

//============================
int main(int argc, char** argv)
{
  Mat im=imread("imagemBaixoContraste.jpg", IMREAD_COLOR);
  
  Mat imRealce = realceMedia(im);
  
  String nomeJanela1="ORIGINAL";
  namedWindow(nomeJanela1, WINDOW_AUTOSIZE);
  imshow(nomeJanela1, im);
  
  String nomeJanela2="REALCE";
  namedWindow(nomeJanela2, WINDOW_AUTOSIZE);
  imshow(nomeJanela2, imRealce);
  
  waitKey(0);
	return 0;
}
