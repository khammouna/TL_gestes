#include "opencv2/opencv.hpp"
#include <algorithm>
#include <vector>
#include <complex> 
#include <fstream>

//int comparaison_prototypes(std::vector<std::complex<double> > coeffs, std::vector<std::vector<std::complex<double> > > prototypes);

std::vector<std::complex<double> >  lire_prototypes(std::string n_reel,std::string n_imaginaire, int N_COEFF);