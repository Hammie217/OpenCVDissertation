#include "pch.h"
#include <iostream>
#include "opencv2/opencv.hpp"
#include <stdint.h>

using namespace cv;
using namespace std;

//Define file name here
string filename = "Manufacturing.mp4";

//Variable declarations
Mat frameIn, frameEdit;
Mat GaussianBlurMat = (Mat_<double>(5, 5) << 1,4,7,4,1,4,16,26,16,4,7,26,41,26,7,4,16,26,16,4,1,4,7,4,1);

//Load file
VideoCapture capture(filename);

void GaussianSmooth() {

	GaussianBlur(frameEdit, frameEdit, Size(5, 5),0,0);
		for (int i = 0; i < frameEdit.rows; i++) {
			for (int j = 0; j < frameEdit.cols; j++) {
				
			}
		}
}

void RemoveRed() {
	for (int i = 0; i < frameEdit.rows; i++) {
		for (int j = 0; j < frameEdit.cols; j++) {
			frameEdit.at<Vec3b>(i, j)[2] =  0;
		}
	}
}
void RemoveBlue() {
	for (int i = 0; i < frameEdit.rows; i++) {
		for (int j = 0; j < frameEdit.cols; j++) {
			frameEdit.at<Vec3b>(i, j)[0] =  0;
		}
	}
}

void RemoveGreen() {
	for (int i = 0; i < frameEdit.rows; i++) {
		for (int j = 0; j < frameEdit.cols; j++) {
			frameEdit.at<Vec3b>(i, j)[1] =  0;
		}
	}
}

void IntensityMap(){
	int max = 0,val;
	cvtColor(frameEdit,frameEdit,COLOR_BGR2GRAY);
	for (int i = 0; i < frameEdit.rows; i++) {
		for (int j = 0; j < frameEdit.cols; j++) {
			val = frameEdit.at<uint8_t>(i, j);
				if (val > max) {
					max = val;
			}
		}
	}


	for (int i = 0; i < frameEdit.rows; i++) {
		for (int j = 0; j < frameEdit.cols; j++) {
			val = frameEdit.at<uint8_t>(i, j);
			if (val < max / 1.5) {
				frameEdit.at<uint8_t>(i, j) = 0;
			}
		}
	}

}

int main(){

	VideoWriter video("outcpp.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(1920, 1080),false);

	//Create frame
	namedWindow("InputWindow", WINDOW_NORMAL);
	namedWindow("EditedWindow", WINDOW_NORMAL);

	//if file opened error	
	if (capture.isOpened() == 0)
		printf("Error opening video stream or file");

		
	for (; ; )
	{
		//put each frame into frameIn and check for empty
		capture >> frameIn;
		if (frameIn.empty())
			break;
		frameIn.copyTo(frameEdit);


		GaussianSmooth();
		IntensityMap();


		//show windows
		imshow("InputWindow",frameIn);
		imshow("EditedWindow", frameEdit);

		video.write(frameEdit);

		//break if esc held
		char c = (char)waitKey(1);
		if (c == 27)
			break;
	}

	// Closes all the frames
	video.release();
	capture.release();
	destroyAllWindows();
			
	return 0;
}
