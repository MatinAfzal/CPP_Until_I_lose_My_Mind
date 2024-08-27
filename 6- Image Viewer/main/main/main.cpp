// main.cpp : Defines the entry point for the application.
//

#include "main.h"

using namespace std;

int main()
{
	cv::Mat image;
	const string path = "C:/Users/pc/Desktop/Desktop/Projects/CPP_Until_I_lose_My_Mind/6- Image Viewer/dead.png";
	image = cv::imread(path, cv::IMREAD_COLOR);

	if (image.empty()) {
		cout << "Image is empty!";
		cin.get();
		return -1;
	}

	cv::imshow("Photo", image);
	cv::waitKey(0);
	return 0;
}
