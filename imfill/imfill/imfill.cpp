//As far as I could comprehend, imfill fills countours of a binary image
//I implemented the function by floodfilling the iverted binary image which produced the same effect
//Shravan Mallemputi, sm22@iitbbs.ac.in

#include<opencv2/core/core.hpp>			//Incluuding libraries
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;

using namespace cv;

int main()
{
	IplImage *im = cvLoadImage("C:\\Users\\$hravan\\Documents\\Visual Studio 2015\\Projects\\imfill\\IMAG0459.jpg", CV_LOAD_IMAGE_ANYDEPTH);	//Loading Input Image
	IplImage *hole = cvCreateImage(cvSize(im->width, im->height), 8, 1);	//Creating the output image
	cvShowImage("Original", im);		

	hole=im;			//Cloning
	cvFloodFill(hole, cvPoint(0, 0), cvScalar(255)); //Floodfilling(Connected arrays become filled)
	cvShowImage("Hole", hole);
	cvSaveImage("hole.png", hole);

	cvNot(hole, hole);
	cvAdd(im, hole, im);
	cvShowImage("FillHole", im);
	cvSaveImage("fillHole.png", im);

	cvWaitKey(0);
	system("pause");
	return 0;
}