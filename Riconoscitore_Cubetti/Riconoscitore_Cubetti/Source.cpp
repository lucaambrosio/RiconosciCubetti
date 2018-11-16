#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(int argc, char **argv)
{
	
	Mat image;
	image = imread("C:\\Users\\Luca\\Desktop\\SUPSI\\terza\\multimedia\\esercitazione6\\Riconoscitore_Cubetti\\Riconoscitore_Cubetti\\ImageToAnalyse.png", CV_LOAD_IMAGE_COLOR); // Read the file
	if (!image.data) // Check for invalid input
	{
		std::cout << "Could not open or find the" << std::endl;
		return -1;
	}
	// 1. convert in grayscale and compute a threshold



	// 5. put a text label near each block with its properties (size & color)

	Mat im_gray;
	cvtColor(image, im_gray, CV_RGB2GRAY);
	//visualizzo immagine in bianco e nero
	//cv::imshow("immagine black and white !!!", im_gray);


		/* 0: Binary
		   1: Binary Inverted
		   2: Threshold Truncated
		   3: Threshold to Zero
		   4: Threshold to Zero Inverted
		 */
	//matrice contente l'immagine una volta che si applica la foglia
	Mat destinazione;

	threshold(im_gray, destinazione, 200, 255, 0);
	//visualizzo immagine con threshold
	//cv::imshow("immagine con treshold !!!", destinazione);

	// 2. filter the noise by using one or more morphological filters
	Mat filtrata;
	Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
	cv::erode(destinazione, filtrata, kernel);
	//la matrice a cui si è applicata la trsformazione è la matrice "filtrata"!!
	//visualizzo la matrice filtrata.
	cv::imshow("immagine con filtro!!!", filtrata);
	// 3. find out how to use the findContours algorithm and use it to segment the lego blocks
	int thresh = 100;
	Mat canny_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	RNG rng(12345);

	/// Detect edges using canny
	Canny(filtrata, canny_output, thresh, thresh * 2, 3);
	/// Find contours
	findContours(canny_output, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// Draw contours
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	vector<Point>angoliAltoDestra;
	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
		angoliAltoDestra.push_back(contours.at(i).at(0));
	}

	/// Show in a window
	namedWindow("Contours", CV_WINDOW_AUTOSIZE);
	imshow("Contours", drawing);

	// 4. find a way to understand size and color of each lego block
	std::cout << " ho un totale di  :" << contours.size() << " contori" << std::endl;
	vector<double> aree;
	for (unsigned int i = 0; i < contours.size(); i++)
	{
		//area dei quadratini preso uno ad uno 
		aree.push_back(contourArea(contours[i]));
		std::cout << " Area: " << aree.at(i) << " del elemento : " << i << std::endl;
	}
	//cerco il centro delle figure
	cv::Moments M;
	int valx;
	int valy;
	vector<String> colori;
	//per trovare il colore di ogni rettangolo viene utilizzato il pixel centrale e analizzato il colore
	for (int i = 0; i < aree.size(); i++) {
		M = cv::moments(contours.at(i));
		valx = int(M.m10 / M.m00);
		valy = int(M.m01 / M.m00);
		Point punto{ valx, valy };
		//cv::circle(image,punto , 10, (255, 255, 255), -1);
		Scalar scalar{ image.at<cv::Vec3b>(punto) };
		int blu = int(scalar[0]);//componente blu
		int green = int(scalar[1]);//componente verde
		int red = int(scalar[2]);//componente rossa
		std::cout << "il rettangolo :" << i << " " << red << " " << green << " " << blu << std::endl;
		//adesso classifico i rettangoli per clolore
		if (red == 0 && green == 0 && blu == 0) {
			//Nero
			colori.push_back("Nero");
		}
		else if (red == 0 && green == 114 && blu == 45) {
			//Verde
			colori.push_back("Verde");
		}
		else if ((red > 220 && green > 150 && blu >= -1) && (red < 250 && green < 203 && blu < 10)) {
			//questo rappresenta il giallo
			colori.push_back("Giallo");
		}
		else if ((red >= 0 && green >= 0 && blu >= 100) && (red < 10 && green < 100 && blu < 150)) {
			//questo rappresenta il blu
			colori.push_back("Blu");
		}
		else if ((red >= 150 && green >= 10 && blu >= 20) && (red < 200 && green < 30 && blu < 50)) {
			//questo rappresenta il rosso
			colori.push_back("Rosso");
		}
		else {
			// se il valore del colore non è riconosciuto dal codice viene identificato da "No Color Defined"
			colori.push_back("No Color Defined");
		}
	}

		//a questo punto so tutte le varie aree dei quadratini !!!
		std::cout << std::endl;
		for (int i = 0; i < aree.size(); i++) {
			if (aree.at(i) > 8000 && aree.at(i) < 9000) {
				std::stringstream testo;//questo ci permette di scrivere sull'immagine
				testo << "1X2, " << colori.at(i);
				std::cout << "il rettangolo : " << i << " e\' un 1X2 " << "e di colore "<<testo.str()<<std::endl;
				cv::putText(image,testo.str(),
					angoliAltoDestra.at(i), 
					cv::FONT_HERSHEY_DUPLEX,
					1.0,
					CV_RGB(0, 0, 0), 
					2);

			}
		else if (aree.at(i) > 13000 && aree.at(i) < 16000) {
				//std::cout << "il rettangolo : " << i << " e\' un 2X2" << std::endl;
				std::stringstream testo;
				testo << "2X2, " << colori.at(i);
				std::cout << "il rettangolo : " << i << " e\' un 2X2 " << "e di colore " << testo.str() << std::endl;
				cv::putText(image, testo.str(),
					angoliAltoDestra.at(i),
					cv::FONT_HERSHEY_DUPLEX,
					1.0,
					CV_RGB(0, 0, 0), 
					2);

			}
			else if (aree.at(i) > 20000 && aree.at(i) < 21500) {
				//std::cout << "il rettangolo : " << i << " e\' un 3X2 " << std::endl;
				std::stringstream testo;
				testo << "3X2, " << colori.at(i);
				std::cout << "il rettangolo : " << i << " e\' un 3X2 " << "e di colore " << testo.str() << std::endl;
				cv::putText(image, testo.str() ,
					angoliAltoDestra.at(i), 
					cv::FONT_HERSHEY_DUPLEX,
					1.0,
					CV_RGB(0, 0, 0), 
					2);
			}
			else if (aree.at(i) > 26000 && aree.at(i) < 28000) {
				//std::cout << "il rettangolo : " << i << " e\' un 4X2 " << std::endl;
				std::stringstream testo;
				testo << "4X2, " << colori.at(i);
				std::cout << "il rettangolo : " << i << " e\' un 4X2 " << "e di colore " << testo.str() << std::endl;
				cv::putText(image, testo.str(),
					angoliAltoDestra.at(i), 
					cv::FONT_HERSHEY_DUPLEX,
					1.0,
					CV_RGB(0, 0, 0), 
					2);
			}
			else if (aree.at(i) > 38000 && aree.at(i) < 40000) {
				//std::cout << "il rettangolo : " << i << " e\' un 6X2 " << std::endl;
				std::stringstream testo;
				testo << "6X2, " << colori.at(i);
				std::cout << "il rettangolo : " << i << " e\' un 6X2 " << "e di colore " << testo.str() << std::endl;
				cv::putText(image, testo.str(),
					angoliAltoDestra.at(i),
					cv::FONT_HERSHEY_DUPLEX,
					1.0,
					CV_RGB(0, 0, 0), 
					2);
			}

		}
		//visualizzo l'immagine a colori
		//salvo l'immagine annotata
		imwrite("C:\\Users\\Luca\\Desktop\\SUPSI\\terza\\multimedia\\esercitazione6\\immagine_annotata.jpg", image);
		std::cout << std::endl;
		//std::cout << "dimensione aree :" << aree.size();
		//std::cout << "dimensione contorni :" << contours.size();
		cv::imshow("image", image);
		cv::waitKey(0);
		return 0;
	}
