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
#include "coeff_fourier.hpp"
//#include "compare_prototype.hpp"


using namespace std;
using namespace cv;

Mat src_gray;
int thresh =63 ;
//int max_thresh = 255;
RNG rng(12345);
Scalar color(255,255,255);
/// Function header
void thresh_callback(int, void* );


int main( int argc, char** argv )
{
        //Declaration des variables
        int cmax(15);
        //int  N(200), cmax(15);
        int Nomb = 20;
        vector<Mat> liste_image;
        /*
        //Chargement des prototypes
        vector<vector<complex<double>>> dico_prototypes;
        vector<complex<double>> prototype_avance_1;
        vector<complex<double>> prototype_avance_2;
        prototype_avance_1 = lire_prototypes("prototype_avance_1_real.tex","prototype_avance_1_imag.tex", 2*cmax+1);
        prototype_avance_2 = lire_prototypes("prototype_avance_2_real.tex","prototype_avance_2_imag.tex", 2*cmax+1);
        dico_prototypes.push_back(prototype_avance_2);
        dico_prototypes.push_back(prototype_avance_1);
        */
        //Création de la liste d'images
        for ( int d=1; d<Nomb-1;d++){
                Mat image;
                string filename = "resultat2_avance" + to_string(d) +".pgm";
                //string filename = "../test/test_gestes" + to_string(d) +".pgm";
                image = imread(filename.c_str(),1);   // Read the file
                liste_image.push_back(image);
                //liste=dir('*.pgm');
        }

        
    
        //Initialisation pour findContours
        Mat canny_output, frame;
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        vector<vector<Point>> tabcontfil;

        for  (int n=1 ; n<Nomb-2 ; n++){
                //Find Contours instead of bwboundaries
                //zliste=bwboundaries(BW,8,'noholes');
                // Convert image to gray and blur it
                cvtColor( liste_image.at(n), src_gray, CV_BGR2GRAY );
                blur( src_gray, src_gray, Size(3,3) );
                /// Detect edges using canny
                Canny( src_gray, canny_output, thresh, thresh*2, 3 );
                /// Find contours
                findContours( canny_output, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0) );
                /// Draw contours
                Mat zliste = Mat::zeros( canny_output.size(), CV_8UC3 );	

                for( size_t j = 0; j< contours.size(); j++ )
                {
                        //	Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
                        drawContours( zliste, contours, j, color, 2, 8, hierarchy, 0, Point() );
                }

                //namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
                //imshow( "Contours", zliste );

                //imwrite( "contour_"+filename.c_str(), zliste );
                //imwrite( "contour.png", zliste );
                //Fin findContours

                int longmax = 0;
                int index = 1;
                int longueur = 0;
                vector<Point> z;
                vector<Point> z_reconstructed;
                Point coord;
                vector<complex<double>> coeffs2(2*cmax+1); 
                vector<complex<double>> coeffs2r(2*cmax+1); 
                vector<complex<double>> coeffs3; 



                //vector<vector<Point>> tabcontfil;
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
                vector<vector<Point>> drawBiggestContour;
                drawBiggestContour.push_back(z);
                Mat myFrame = Mat::zeros(canny_output.rows, canny_output.cols, CV_8UC3);
                drawContours(myFrame,drawBiggestContour,0,color,2, 8, hierarchy, 0, Point() );
                imwrite( "../test/contourLePlusLong"+ to_string(n) +".png", myFrame );


                // z_comp is the complex representation of z
                typedef complex<double> intComp;
                typedef vector<intComp> complexVector;
                complexVector z_comp;
                for( int j = 1; j < longmax -1 ; j++){  
                        intComp z_point(z[j].x, z[j].y); 
                        z_comp.push_back(z_point);
                } 



                coeffs2 = coeff_fourier(z_comp, cmax);
                //dft(z_comp, coeffs2, DFT_COMPLEX_OUTPUT + DFT_SCALE);
                /*
                for(int j = 1; j<cmax+1; j++ ){
                  coeffs2r[j+cmax] = coeffs2[j];
                }
                 for(int j = 1; j<cmax+1; j++ ){
                     coeffs2r[j] = coeffs2[j+cmax];
                  }
                */
                  dft(coeffs2, z_reconstructed, DFT_INVERSE + DFT_SCALE);
                  /*
                dft(coeffs2, coeffs3, DFT_INVERSE + DFT_SCALE);
                for( size_t j = 1; j < coeffs3.size() -1 ; j++){  
                        Point point(coeffs3[j].real()*coeffs3.size(),coeffs3[j].imag()*coeffs3.size());
                        z_reconstructed.push_back(point);
                } 
                //normalize(coeffs3, coeffs3, 0, 1, CV_MINMAX);
                */

                //calcul des coeffs de fourier complex des contours               
                /* coeffs2 = coeff_fourier2(z_comp, longmax);
                   for(auto& point: coeffs2){
                   cout<< complex<double>(point.real(), point.imag()) <<endl;
                   }
                   */
                /*
                //calcul de la transformée de fourier inverse pour vérification
                vector<vector<Point> > contour_reconstruit;
                contour_reconstruit = fourier_inverse(coeffs2, 2*cmax);

                for (auto& matrix: contour_reconstruit){
                for(auto& point: matrix) {
                cout<< complex<double>(point.x , point.y)<<endl;;
                }}

                //on plotte 
                Mat reconstruit = Mat::zeros(canny_output.rows, canny_output.cols, CV_8UC3); 
                drawContours(reconstruit, contour_reconstruit, -1, color,2,2);
                imshow("contour_reconstruit",reconstruit);
                imwrite( "contours_associes_aux_coeff_normalises.pgm", reconstruit);


                //FUNCTION dfdir
                //On calcule les coeffs de fourier

                complexVector coeff, coeffpi, z_comp_neg, contfil, contfilpi;
                coeff=coeff_fourier(z_comp, cmax, longmax, z);
                for(auto& point: coeff){
                cout<< complex<double>(point.real(), point.imag()) <<endl;
                }

                for( int j = 1; j < longmax -1 ; j++){
                intComp z_point(-z[j].x, -z[j].y);
                z_comp_neg.push_back(z_point);
                }

                coeffpi=coeff_fourier(z_comp_neg, cmax,longmax, z);


                //On calcule le contour de fourier inverse pour vérifier
                contfil=dfinv(coeff,cmax,N);
                contfilpi = dfinv(coeffpi, cmax, N);

                Point p;
                vector<Point> cont;

                for(size_t j = 1; j < contfil.size(); j++){
                p.x = contfil[j].real();
                p.y = contfil[j].imag();
                cont.push_back(p);
                }
                tabcontfil.push_back(cont);
*/


                //On draw le contour reconstruit
                vector<vector<Point>> drawReconstructedContour;
                drawReconstructedContour.push_back(z_reconstructed);
                Mat myFrame2 = Mat::zeros(canny_output.rows, canny_output.cols, CV_8UC3);
                drawContours(myFrame2,drawReconstructedContour,0,color,2, 8, hierarchy, 0, Point());
                imwrite( "contourReconstruit"+ to_string(n) +".png", myFrame2 );

                }
                

                
            
                /*
                //Mat reconstruit;
                Mat reconstruit = Mat::zeros(canny_output.rows, canny_output.cols, CV_8UC3); 
                //drawContours(reconstruit, canny_output, -1, color, 2, 2);
                drawContours(reconstruit, tabcontfil, -1, color, 2, 2);
                namedWindow( "Test", CV_WINDOW_AUTOSIZE );
                imshow("Test", reconstruit);
                imwrite( "contours_associes_aux_coeff_normalises.pgm", reconstruit );
                //imwrite( "contours_associes_aux_coeff_normalises.pgm", tabcontfil);
                */
                


return 0;
}	

