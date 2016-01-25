#include "coeff_fourier.hpp"
#define N_COEFF 15
using namespace cv;
using namespace std;



vector<complex<double>> coeff_fourier(vector<complex<double>> z_comp, int cmax){


	vector<complex<double>> coeff(2*cmax + 1);
	vector<complex<double>> z_temp;
	vector<complex<double>> z_diff;
	vector<complex<double>> z_coeff;
	Point centre(500, -300);
	complex<double> z_moy;
	double longc = z_comp.size();

	//moyenne (pas besoin la fonction dft la calcule directement)
   for(auto& point: z_comp) {
      z_moy += complex<double>(point.real() , point.imag());
   }
   	z_moy = complex<double>(z_moy.real()/longc, z_moy.imag()/longc);

	//on calcule les coefficients de fourier
	for( int j = 1; j < longc ; j++){
      complex<double> z_point2(z_comp[j].real() - z_moy.real(), z_comp[j].imag() - z_moy.imag());
      //complex<double> z_point2(z_comp[j].real() , z_comp[j].imag());
      z_diff.push_back(z_point2);
   }

   for(int i = 0; i<2*cmax+1; ++i){
   	complex<double> exp_four;
   	complex<double> a(0,0);

   for (int j = 0 ; j < longc; ++j){   
         exp_four = exp(complex<double>(0,-2.0*j*(i-cmax)*M_PI/longc));
         a+= (z_diff[j])*exp_four;
      }

      coeff[i] = a /complex<double>(longc,0);
   } 


	dft(z_diff, coeff, DFT_SCALE + DFT_COMPLEX_OUTPUT);
	//dft(z_diff, z_temp, DFT_SCALE + DFT_COMPLEX_OUTPUT);
	/*
	for(int j = 1; j<cmax+1; j++ ){
    coeff[j+cmax] = z_temp[j];
    }
    for(int j = 1; j<cmax+1; j++ ){
    coeff[j] = z_temp[j+cmax];
    }
    */
	//invariance vis a vis du sens de parcours
	if(abs(coeff[cmax - 1])<abs(coeff[cmax-1])){
	reverse(coeff.begin(), coeff.end());
	}
	
	//invariance vis a vis de la rotation
	double Phi = arg(coeff[cmax+1]*coeff[cmax-1])/2.0;
	complex<double> exp_comp = exp(complex<double>(0,-Phi));

	for (auto& complex: coeff){
	complex *= exp_comp;
	}
	/*
	double theta = arg(coeff[cmax+1]);
	
	for (int i = 0; i < 2*cmax+1 ; ++i){
	complex<double> exp_comp2 = exp(complex<double>(0,-theta*(-cmax+i)));
	coeff[i] *= exp_comp2;
	}
	*/	
	double d1 = abs(coeff[cmax+1]);	
	for(auto& comp : coeff){
	comp /= d1;
	}
	
	return (coeff);
}
