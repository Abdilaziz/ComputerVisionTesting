#include <opencv2/core.hpp>
#include "opencv2/opencv.hpp"
//#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

using namespace cv;
using namespace std;

int startVideo();
void plotEdges(char*windowName, Mat image);

int main(int argc, char** argv)
{
	startVideo();
	//if (argc != 2)
	//{
	//	cout << " Usage: display_image ImageToLoadAndDisplay" << endl;
	//	return -1;
	//}
	//if (argv[1]=="video") {
	//	startVideo();
	//}
	//else {
	//	Mat image, image_gray;


	//	image = imread(argv[1], IMREAD_COLOR); // Read the file

	//	if (image.empty()) // Check for invalid input
	//	{
	//		cout << "Could not open or find the image" << endl;
	//		return -1;
	//	}

	//	plotEdges("Edges Window", image);

	//	waitKey(0); // Wait for a keystroke in the window
	//}

	return 0;
}



void plotEdges(char* windowName, Mat image) {
	Mat edgeImage, image_gray;

	//In case of linear transformations, the range does not matter.
	//	But in case of a non - linear transformation, an input RGB image should be 
	//	normalized to the proper value range to get the correct results, for example, 
	//	for RGB \rightarrow L*u*v* transformation.For example, if you have a 
	//		32 - bit floating - point image directly converted from an 8 - bit image 
	//		without any scaling, then it will have the 0..255 value range instead of 
	//		0..1 assumed by the function.So, before calling cvtColor, you need first 
	//		to scale the image down :

	//image *= 1. / 255; //(if values are not in the 0-255 range)

	cvtColor(image, image_gray, CV_BGR2GRAY);

	//filter image
	//blur(image_gray, edgeImage, Size(3, 3));
	GaussianBlur(image_gray, edgeImage, Size(7, 7), 1.5, 1.5);

	//get the edges of the image
	cv::Canny(edgeImage, edgeImage, 8, 80);

	Mat dst;
	dst.create(image.size(), image.type());
	dst = Scalar::all(0);
	image.copyTo(dst, edgeImage);

	namedWindow(windowName, WINDOW_AUTOSIZE);
	imshow(windowName, dst);
}


int startVideo() {

	VideoCapture cap(0); // open the default camera
	if (!cap.isOpened()) {  // check if we succeeded
		cout << "cant open camera" << endl;
		return -1;
	}
	Mat edges;
	namedWindow("edges", 1);
	for (;;)
	{
		Mat frame;
		cap >> frame; // get a new frame from camera
		cvtColor(frame, edges, COLOR_BGR2GRAY);
		GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
		Canny(edges, edges, 0, 30, 3);
		imshow("edges", edges);
		if (waitKey(30) >= 0) break;
	}
}