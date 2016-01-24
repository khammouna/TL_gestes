#include "compare_prototype.hpp"
using namespace cv;
using namespace std;


vector<complex<double>> lire_prototypes(string n_reel,string n_imaginaire, int N_COEFF){
        vector<complex<double>> prototype;
        ifstream reel,imaginaire;
        
        reel.open(n_reel);
        if (reel.fail()) {
        cerr << "Impossible d'ouvrir le fichier "<<n_reel << endl;
        exit(1);
        } 

        imaginaire.open(n_imaginaire);
        if (imaginaire.fail()) {
        cerr << "Impossible d'ouvrir le fichier "<< n_imaginaire << endl;
        exit(1);
        } 
        
        
        for(int k = 1; k<N_COEFF;k++){
        string st_reel, st_imag, a, b;
        getline(reel, st_reel);
        getline(imaginaire, st_imag);
        complex<double> coeff(atof(st_reel.c_str()), atof(st_imag.c_str()));
        prototype.push_back(coeff); 
        }        
        reel.close();
        imaginaire.close();

	return (prototype);
}
