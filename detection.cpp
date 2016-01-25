#include "detection.hpp"

using namespace std;
using namespace cv;

vector<vector<Point>> detection(Mat frame, int w, int l){

	vector<vector<Point>> drawBiggestContour;
	int thresh =70;
	//int max_thresh = 255;
	RNG rng(12345);
	Scalar color(255,255,255);
	Scalar blueColor(255,0,0);
	Scalar redColor(0,0,255);
	void thresh_callback(int, void* );
	vector<Vec4i> hierarchy;
	Mat edges;
	vector<vector<Point> > contours;



	Mat myContour = Mat::zeros(frame.rows, frame.cols, CV_8UC3);
	Mat myFrame = Mat::zeros(frame.rows, frame.cols, CV_8UC3);
//	GaussianBlur(frame, frame, Size(7,7), 1.8, 1.8);
	int k(0), seuil(0);
	for (int i =0;i<l;i++){
		for (int j = 0; j< w; j++){

			Vec3b pixel = frame.at<Vec3b>(i, j);
			int blue = pixel[0];
			int green = pixel[1];
			int red = pixel[2];

			int  max_rg =max(red,green);
			int  max_rgb =max(max_rg,blue);
			int  min_rg = min(red,green);
			int  min_rgb =min(min_rg,blue);

			//diminuer luminosite

			if (red> 150 && blue>150 && green>150 ){
				frame.at<Vec3b>(i,j)[0] =255;
				frame.at<Vec3b>(i,j)[1] =255;
				frame.at<Vec3b>(i,j)[2] =255;

			}

			if (red == max_rgb){
				if (max_rgb-min_rgb>seuil){
					frame.at<Vec3b>(i,j)[0]=255;
					frame.at<Vec3b>(i,j)[1]=255;
					frame.at<Vec3b>(i,j)[2]=255;
					++k;
				}

				else {
					frame.at<Vec3b>(i,j)[0]=0;
					frame.at<Vec3b>(i,j)[1]=0;
					frame.at<Vec3b>(i,j)[2]=0;

				}
			}


			else{
				frame.at<Vec3b>(i,j)[0]=0;
				frame.at<Vec3b>(i,j)[1]=0;
				frame.at<Vec3b>(i,j)[2]=0;

			}

		}
	}


	cvtColor(frame, edges, CV_BGR2GRAY );
	blur( edges, edges, Size(3,3) );
	Canny(edges, edges, thresh, thresh*2, 3 );
	/// Find contours
	findContours( edges, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0) );
	drawContours(myContour, contours,-1,blueColor,2,2);
	add(frame, myContour, frame);
	imshow("edges", frame);

	int longmax = 0;
	int index = 1;
	int longueur = 0;
	vector<Point> z;

	// On itère sur l'ensemble des contours
	const int nb_contours = contours.size(); 
	for(int i  = 0; i< nb_contours; i++ )
	{
		vector<Point> contourj = contours.at(i);
		longueur = contourj.size();
		if (longueur>longmax){
			longmax = longueur;
			index = i;
		}


	}   
	//z is the biggest contour
	z = contours.at(index); 

	//draw this contour

	drawBiggestContour.push_back(z);
	drawContours(myFrame,drawBiggestContour,0,redColor,2, 8, hierarchy, 0, Point() );
	add(myContour, myFrame, myContour);
	imshow("lepluslong", myContour);

	return (drawBiggestContour);
}

