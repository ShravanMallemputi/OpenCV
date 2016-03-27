//The following code has been written according to Otsu's Thresholding method, which I couldn't generalize so I implemented it with three thresholds
//Hope you accept this
// Shravan Mallemputi, sm22@iitbbs.ac.in


#include<opencv2/core/core.hpp>			//Including llibraries
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;				
using namespace std;

int main()
{
	Mat src;			// Declaring input datatype
	src = imread("C:\\Users\\$hravan\\Documents\\Visual Studio 2015\\Projects\\multithresh\\lenna.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	
	int histogram[256]; //For making a histogram array

	for (int i = 0; i < 255; i++)	// Iteratively finding the values for histogram
	{
		for (int k = 0; k < src.size().width; k++)
		{
			for (int j = 0; j < src.size().height; j++)
			{
				if (src.at<uchar>(k, j) == i) {
					histogram[i] += 1;
				}
			}
		}


	}
	double W0K, W1K, W2K, W3K, M0, M1, M2, M3, currVarB, maxBetweenVar, M0K, M1K, M2K, M3K, MT; //Declaring the variables
	int N = src.rows*src.cols; //Nuber of pixels
	W0K = 0; //class 1
	W1K = 0;	//class2
	M0K = 0;	//class 1 mean
	M1K = 0;	//class 2 mean
	MT = 0;		// overall mean
	maxBetweenVar = 0;		//maximized variance between classes
	double optimalThresh1, optimalThresh2, optimalThresh3;	//initializing output thresholds
	for (int k = 0; k <= 255; k++) {			//Overall mean
		MT += k * (histogram[k] / (double)N);
	}
	for (int t1 = 0; t1 <= 255; t1++)			//first class
	{
		W0K += histogram[t1] / (double)N; //Pi
		M0K += t1 * (histogram[t1] / (double)N); //i * Pi
		M0 = M0K / W0K; //(i * Pi)/Pi

		W1K = 0;
		M1K = 0;

		for (int t2 = t1 + 1; t2 <= 255; t2++)		//Second class
		{
			W1K += histogram[t2] / (double)N; //Pi
			M1K += t2 * (histogram[t2] / (double)N); //i * Pi
			M1 = M1K / W1K; //(i * Pi)/Pi
			W2K = 1 - (W0K + W1K);
			M2K = MT - (M0K + M1K);

			if (W2K <= 0) break;

			M2 = M2K / W2K;

			W3K = 0;
			M3K = 0;

			for (int t3 = t2 + 1; t3 <= 255; t3++)		//Third class
			{
				W2K += histogram[t3] / (double)N; //Pi
				M2K += t3 * (histogram[t3] / (double)N); // i*Pi
				M2 = M2K / W2K; //(i*Pi)/Pi
				W3K = 1 - (W1K + W2K);
				M3K = MT - (M1K + M2K);

				M3 = M3K / W3K;
				currVarB = W0K * (M0 - MT) * (M0 - MT) + W1K * (M1 - MT) * (M1 - MT) + W2K * (M2 - MT) * (M2 - MT) + W3K * (M3 - MT) * (M3 - MT);

				if (maxBetweenVar < currVarB)			//Maximized variance
				{
					maxBetweenVar = currVarB;
					optimalThresh1 = t1;
					optimalThresh2 = t2;
					optimalThresh3 = t3;
				}
			}
		}

		for (int k = 0; k < src.size().width; k++)							//Applying threshold for each class
		{
			for (int j = 0; j < src.size().height; j++)
			{
				if (1 < src.at<uchar>(k, j) < 64) {
					if (src.at<uchar>(k, j) < optimalThresh1) {
						src.at<uchar>(k, j) = 0;
					}
					else
					{
						src.at<uchar>(k, j) = 1;
					}
				}
				if (64 < src.at<uchar>(k, j) < 128) {
					if (src.at<uchar>(k, j) < optimalThresh2) {
						src.at<uchar>(k, j) = 0;
					}
					else
					{
						src.at<uchar>(k, j) = 1;
					}
				}
				if (128 < src.at<uchar>(k, j) < 256) {
					if (src.at<uchar>(k, j) < optimalThresh3) {
						src.at<uchar>(k, j) = 0;
					}
					else
					{
						src.at<uchar>(k, j) = 1;
					}
				}
			}
		}
		

	}
	namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
	imshow("Display window", src);
	cvWaitKey(0);
}