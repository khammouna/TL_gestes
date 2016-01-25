#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

int main2( int argc, char** argv )
{
	int i(0),j(0);
	//	for (int d = 1; d<70; d++)
	//	{

	IplImage *image;
	//	string filename = "learner_image_gauche/learner-image-gauche" + to_string(d) + ".png";
	//	string resultat = "resultat_droite/resultat_droite" + to_string(d) + ".png";
	//	image = cvLoadImage(filename.c_str());   // Read the file
	image = cvLoadImage("output.jpg");

	for( i= 0; i < image->height; i++ )
	{
		for( j = 0; j < image->width; j++ )
		{
			CvScalar pixel = cvGet2D(image, i, j); //lecture du pixel ligne 10 colonne 25
			double& red = pixel.val[0];
			double& green = pixel.val[1];
			double& blue = pixel.val[2];



			if(red!=0 || blue!= 0 || green != 0){
				red = 255;
				blue = 255;
				green = 255;
				cvSet2D(image,i,j,pixel);

			}


			/*
			   if(max({red,blue,green}) == red){
			   red = 0;
			   blue = 0;
			   green = 0;
			   cvSet2D(image,i,j,pixel);

			   }


			   if(max({red,blue,green})-min({red,blue,green})>100){
			   red = 0;
			   blue = 0;
			   green = 0;
			   cvSet2D(image,i,j,pixel);

			   }
			 */

		}
	}

	for( i= 0; i < image->height; i++ )
		{
		for( j = 0; j < image->width; j++ )
		{
		CvScalar pixel = cvGet2D(image, i, j); //lecture du pixel ligne 10 colonne 25
		double& red = pixel.val[0];
		double& green = pixel.val[1];
		double& blue = pixel.val[2];
		if(red == 255){
		red = 0;
		green =0;

		blue =0;

		cvSet2D(image,i,j,pixel);

		}
		else{
		red = 255;
		green = 255;
		blue = 255;

		cvSet2D(image,i,j,pixel);

		}

		}
		}


	//			cvSaveImage(resultat.c_str(),image);
	cvSaveImage("output2.jpg", image);
	cvReleaseImage(&image);

	const char* window_title="Inverse";
	cvNamedWindow (window_title, CV_WINDOW_AUTOSIZE);
	cvShowImage(window_title,image);
	//cvWaitKey(0);

	//}
	/*
	   const char* window_title="Inverse";
	   cvNamedWindow (window_title, CV_WINDOW_AUTOSIZE);
	   cvShowImage(window_title,image);
	   cvWaitKey(0);


	   cvDestroyAllWindows();
	 */
	return 0;
}
