#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(int argc, char **argv)
{
	int scelta = 0;
	std::cout << "inserire la tecnica la blurring!!!!" << std::endl;
	std::cout << "inserire 1 per blur"<<std::endl;
	std::cout << "inserire 2 per gaussian blur" <<std::endl;
	std::cout << "inserire 3 per median blur" << std::endl;
	std::cout << "inserire 4 per il bilateral filter " << std::endl;
	std::cin >> scelta;
	std::cin;
	switch (scelta) {
	case 1:
	{
		int dimensione = 0;
		std::cout << "inserire la dimensione del kernel !!!" << std::endl;
		std::cin >> dimensione;
		std::cout << "applico il blur :" << std::endl;
		Mat image;
		image = imread("C:\\Users\\Luca\\Desktop\\SUPSI\\terza\\multimedia\\esercitazione6\\ViewImage\\ViewImage\\ImageToAnalyse.png", CV_LOAD_IMAGE_COLOR); // Read the file
		Mat filter;
		cv::blur(image, filter, Size(dimensione, dimensione));
		if (!image.data)
		{
			std::cout << "Could not open or find the image" << std::endl;
			return -1;
		}
		cv::imshow("image", image);
		cv::imshow("immagine with median blur !!!", filter);
		cv::waitKey(0);
		break;
	}
	case 2:
	{
		int dimensione = 0;
		std::cout << "inserire la dimensione del kernel !!!" << std::endl;
		std::cin >> dimensione;
		std::cout << "applico il gaussian blur :" << std::endl;
		Mat image;
		image = imread("C:\\Users\\Luca\\Desktop\\SUPSI\\terza\\multimedia\\esercitazione6\\ViewImage\\ViewImage\\ImageToAnalyse.png", CV_LOAD_IMAGE_COLOR); // Read the file
		Mat filter;
		cv::GaussianBlur( image,filter,Size( dimensione,dimensione),0);

		if (!image.data)
		{
			std::cout << "Could not open or find the image" << std::endl;
			return -1;
		}
		cv::imshow("image", image);
		cv::imshow("immagine with median blur !!!", filter);
		cv::waitKey(0);




		break;
	}
	case 3:
	{
		int dimensione = 0;
		std::cout << "inserire la dimensione del kernel !!!" << std::endl;
		std::cin >> dimensione;
		std::cout << "applico il median blur :" << std::endl;
		
		Mat image;
		image = imread("C:\\Users\\Luca\\Desktop\\SUPSI\\terza\\multimedia\\esercitazione6\\ViewImage\\ViewImage\\ImageToAnalyse.png", CV_LOAD_IMAGE_COLOR); // Read the file
		Mat filter;
		cv::medianBlur( image,filter, dimensione);

		if (!image.data)
		{
			std::cout << "Could not open or find the image" << std::endl;
			return -1;
		}
		cv::imshow("image", image);
		cv::imshow("immagine with median blur !!!", filter);
		cv::waitKey(0);
		break;
	}
	case 4:
	{
		int dimensione = 0;
		std::cout << "inserire la dimensione del kernel !!!" << std::endl;
		std::cin >> dimensione;
		std::cout << "applico il bilateral filter :" << std::endl;
		Mat image;
		image = imread("C:\\Users\\Luca\\Desktop\\SUPSI\\terza\\multimedia\\esercitazione6\\ViewImage\\ViewImage\\ImageToAnalyse.png", CV_LOAD_IMAGE_COLOR); // Read the file
		Mat filter;
		cv::bilateralFilter(image, filter, dimensione,dimensione*2,dimensione/2);
		if (!image.data) 
		{
			std::cout << "Could not open or find the image" << std::endl;
			return -1;
		} 
		cv::imshow("image", image);
		cv::imshow("immagine with bilateral filter !!!", filter);
		cv::waitKey(0);
		break;

	}
	}
	return 0;
}