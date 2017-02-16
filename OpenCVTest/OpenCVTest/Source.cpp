#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
//using namespace std;

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << " Usage: display_image ImageToLoadAndDisplay" << std::endl;
		return -1;
	}

	Mat image;


	image = imread(argv[1], IMREAD_COLOR); // Read the file

	if (image.empty()) // Check for invalid input
	{
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	//Point i = Point(0, 400);
	//Point y = Point(400, 400);

	image = image.rowRange(Range(101, 103));
	image = image.colRange(Range(201, 203));
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			std::cout  << image.at<double>(i, j) << std::endl;
		}
	}


	printf("%d",image.rows);
	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Display window", image); // Show our image inside it.

	waitKey(0); // Wait for a keystroke in the window
	return 0;
}