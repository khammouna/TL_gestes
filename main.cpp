#include <iostream>
#include <sstream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <cmath>
#include <algorithm>
#include <string>
#include <array>
#include <fstream>
#include <complex>
#include "detection.hpp"
//#include "compare_prototype.hpp"
//#include "calcul_coeff.hpp"

using namespace std;
using namespace cv;


int  main(int argc, char** argv){

        Mat frame;
        vector<vector<Point> > contour;
        vector<complex<double>> prototypes;
        vector<complex<double> > coeffs;
        Scalar color(255 ,255 ,255);  
        int w,l;
        //clock_t t1 = clock();

        //extraction des prototypes des fichiers sources
        //prototypes = lire_prototypes(FICHIER_R , FICHIER_I , N_COEFF_FOUR*2+1);

        VideoCapture cap(0); // open the default camera
        if(!cap.isOpened()){  // check if we succeeded
                return -1;
        }
        //recuperation des informations de la camera
        w = cap.get(CV_CAP_PROP_FRAME_WIDTH);
        l = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

        for(;;)
        {
                Mat frame;
                cap >> frame;// get a new frame from camera
                //récupérer le plus long contour
                contour = detection(frame, w, l);
                if(waitKey(30) >= 0) break;
        }
        return 0;
}
