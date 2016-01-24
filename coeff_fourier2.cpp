#include "coeff_fourier2.hpp"
#define N_COEFF 15
using namespace cv;
using namespace std;



vector<complex<double>> coeff_fourier2(vector<complex<double>> z_comp, int cmax){


   vector<complex<double>> coeff(2*cmax + 1);
   vector<complex<double>> tc(2*cmax + 1);
   vector<complex<double>> z_temp;
   vector<complex<double>> z_diff;
   vector<complex<double>> z_coeff;
   complex<double> z_moy;
   double longc = z_comp.size();
   vector<int> num(2*cmax + 1);

   //num contient les ints de -cmax à cmax
   for( int j = 1 ; j< 2*cmax+2; j++ ){
      num[j] = -cmax -1 + j;
   }
   //moyenne (pas besoin la fonction dft la calcule directement)
   for(auto& point: z_comp) {
      z_moy += complex<double>(point.real() , point.imag());
   }

      z_moy = complex<double>(z_moy.real()/(double)longc, z_moy.imag()/(double)longc);
   //on calcule les coefficients de fourier
      //ajout d'un coefficient 10 à la moyenne sinon le décalage est trop grand
   for( int j = 1; j < longc ; j++){
      complex<double> z_point2(z_comp[j].real() - z_moy.real()*100, z_comp[j].imag() - z_moy.imag()*100);
      //complex<double> z_point2(z_comp[j].real() , z_comp[j].imag());
      z_diff.push_back(z_point2);
   }
   //DFT_SCALE divise par le nombre de coeffs
   dft(z_diff, coeff, DFT_SCALE + DFT_COMPLEX_OUTPUT); 
   
   /*
   dft(z_diff, tc, DFT_SCALE + DFT_COMPLEX_OUTPUT); 
   //on selectionne les coeffs entre -cmax et cmax
   for(int j = 1; j<cmax+1; j++ ){
      coeff[j+cmax] = tc[j];
   }
   for(int j = 1; j<cmax+1; j++ ){
      coeff[j] = tc[j+cmax];
   }
   */
   
   //invariance vis a vis du sens de parcours
   if(abs(coeff[cmax-1])<abs(coeff[cmax+1])){
   reverse(coeff.begin(), coeff.end());
   }

   //invariance vis a vis de la rotation
   double Phi = arg(coeff[cmax+1]*coeff[cmax-1])/2.0;
   complex<double> exp_comp = exp(complex<double>(0,-Phi));

   for (auto& complex : coeff){
   complex *= exp_comp;
   }
   double theta = arg(coeff[cmax+1]);

   for (size_t i = 0; i < coeff.size(); ++i){
   exp_comp = exp(complex<double>(0,-theta*(i-cmax)));
   coeff[i] = coeff[i] * exp_comp;
   }
   double d1 = abs(coeff[cmax+1]);
   for(auto& complex : coeff){
   complex /=d1;
   }
   
   
   return (coeff);
}
