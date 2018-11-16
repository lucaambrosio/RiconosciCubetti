#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(int argc, char **argv) {
	namedWindow("image", WINDOW_AUTOSIZE);
	Mat image;
	image = imread("C:\\Users\\Luca\\Desktop\\SUPSI\\terza\\multimedia\\esercitazione6\\ViewImage\\ViewImage\\ImageToAnalyse.png", CV_LOAD_IMAGE_COLOR); // Read the file
	Mat im_gray;
	cvtColor(image, im_gray, CV_RGB2GRAY);

	if (!image.data) // Check for invalid input
	{
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	} cv::imshow("image", image);
	cv::imshow("immagine black and white !!!", im_gray);
	cv::waitKey(0);
	return 0;
}



