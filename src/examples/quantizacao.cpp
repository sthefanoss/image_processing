#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

//-----------------------------------
int requantizacao(String nomeImagemRGB, int div) {

    String titulo1, titulo2;

    Mat imRGB;
    imRGB = imread(nomeImagemRGB, IMREAD_COLOR);  
    
    if(! imRGB.data)                            
      {
        cout << "Imagem não foi localizada!" << endl;
        return -1;
      } 
    else
      {
        titulo1=nomeImagemRGB;
        titulo1+=" (RGB)";
        namedWindow(titulo1, WINDOW_AUTOSIZE);
        imshow(titulo1, imRGB);       
        
        Mat imRequantizada;

				uchar buffer[256];
    		for(int i = 0; i < 256; i++)
        	buffer[i] = i / div * div + div / 2;

    		Mat table(1, 256, CV_8U, buffer, sizeof(buffer));
    		LUT(imRGB, table, imRequantizada);

        imwrite("LenaRequantizacao.tif", imRequantizada);

        titulo2=nomeImagemRGB;
        titulo2+=" RGB Requantizada";
        namedWindow(titulo2, WINDOW_AUTOSIZE);
        imshow(titulo2, imRequantizada);
      }
  
  return 0;

}

//------------------------------
int main( int argc, char** argv)
{

    int r;

    r=requantizacao("Lena.tif", 32); // [1,256]
  


		waitKey(0); 
 		return 0;
 		
}


