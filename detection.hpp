#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <cmath>
#include <algorithm>
#include <string>
using namespace std;
using namespace cv;

vector<vector<Point>> detection(Mat frame, int w, int l);
	