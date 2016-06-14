#include "EnergyCal.hh"
#include <string>
#include <sstream>
#include <vector>
#include <TSpectrum.h>


EnergyCal::EnergyCal(){}

EnergyCal::~EnergyCal(){};





void EnergyCal::Calibrate(TTree* t, TFile* f){



//for peak finding (TSpectrum)
	Int_t npeaks = 2;
	float sigma = 5;
	float threshold = 0.05;
	double PeakEnergies[2];
//assigned in increasing order of energy
	PeakEnergies[0] = 511;	//annihilation
	PeakEnergies[1] = 1022; //double

	



	int i;
	int j;
/*
//finds peak for each bar

	for (i=0;i<fNumBars;i++)
	{	
		std::stringstream sbar;
		sbar << i+1;
		histObj = "qdcBar" + sbar.str();
		f->GetObject(histObj.c_str(),fHistPtr);

		TSpectrum *spectrum = new TSpectrum(npeaks);
		Int_t nfound = spectrum->Search(fHistPtr,sigma,"",threshold);
		Float_t *xpeaks = spectrum->GetPositionX();

		for (j=0;j<nfound;j++)
		{
			std::cout << "xposition: " << xpeaks[j] << " found for bar " << sbar.str() << std::endl;			
		}
	}
*/	
//finds peaks for all qdc data combined
//use findpeak.cc in CALIOPEAnalysis/RunFiles/ to test for correct arguments for Search, etc 

	f->GetObject("qdcALL",fHistPtr);
	TSpectrum *spectrum = new TSpectrum(10);
	Int_t nfound = spectrum->Search(fHistPtr,sigma,"nodraw",threshold);
	Float_t *xpeaks = spectrum->GetPositionX();
	
	for (i=0;i<nfound;i++)
	{
		std::cout << "num peaks (nfound): " << nfound << std::endl;
		std::cout << "peak found at xposition: " << xpeaks[i] << " in bin: " << fHistPtr->GetXaxis()->FindBin(xpeaks[i]) << std::endl; 
	}


}



