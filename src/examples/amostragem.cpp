#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

//-----------------------------------
int alteraGradeAmostragem(String nomeImagemRGB) {

    String titulo1, titulo2, titulo3;

    Mat imRGB;
    imRGB = imread(nomeImagemRGB, CV_LOAD_IMAGE_COLOR);  
  
    titulo1="RGB";
    namedWindow(titulo1, WINDOW_AUTOSIZE);
    imshow(titulo1, imRGB);
        
    Mat imRGB200x200;

    Size size(200,200);
    resize(imRGB,imRGB200x200,size);

    imwrite("Lena200x200.tif", imRGB200x200);
  
    titulo2="RGB 200x200";
    namedWindow(titulo2, WINDOW_AUTOSIZE);
    imshow(titulo2, imRGB200x200);
  
    //----------
  
    Mat imRGB900x900;
  
    Size size2(900,900);
    resize(imRGB,imRGB900x900,size2, INTER_CUBIC);
  
    imwrite("Lena900x900.tif", imRGB900x900);
  
    titulo3="RGB 900x900";
    namedWindow(titulo3, WINDOW_AUTOSIZE);
    imshow(titulo3, imRGB900x900);
  
    return 0;

}

//------------------------------
int main(int argc, char** argv)
{

    int r;

    r=alteraGradeAmostragem("Lena.tif");

		waitKey(0); 
 		return 0;
 		
}


