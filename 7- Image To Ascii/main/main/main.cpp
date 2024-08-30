// main.cpp : Defines the entry point for the application.
//

#include "main.h"

using namespace std;

int mapRange(int, int, int, int, int);

int main()
{
	cv::Mat image;
	const string path = "C:/Users/pc/Desktop/Desktop/Projects/CPP_Until_I_lose_My_Mind/7- Image To Ascii/UwU.jpg";
	string ascii_chars = "`^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
	image = cv::imread(path, cv::IMREAD_GRAYSCALE);
	cv::resize(image, image, cv::Size(image.size().width/3, image.size().height/3));

	if (image.empty()) {
		cerr << "Image is empty!";
		return -1;
	}

	for (int i = 0; i < image.rows; ++i) {
		for (int j = 0; j < image.cols; ++j) {
			int grayScaleVal = static_cast<int>(image.at<uchar>(i, j));
			cout << ascii_chars[mapRange(grayScaleVal, 0, 255, 0, 64)];
		}
		cout << endl;
	}

	cin.get();
	return 0;
}

//************************************************************************
int mapRange(int value, int oldMin, int oldMax, int newMin, int newMax) {
	return (int)ceil(newMin + (value - oldMin) * (newMax - newMin) / (oldMax - oldMin));
}