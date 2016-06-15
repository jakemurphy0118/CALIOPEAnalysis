//made to test peakfinding method with other runfiles
#include <string>
#include <iostream>
#include <TFile.h>
#include <TH1F.h>
#include <TSpectrum.h>



int main(int argc, char** argv){

std::string file = argv[1];
TFile fin(file.c_str());
TH1F* fHistPtr;
fin.GetObject("energySpec",fHistPtr);
int i;


	Int_t npeaks = 2;
	float sigma = 10;
	float threshold = 0.4;
	TSpectrum *spectrum = new TSpectrum(10);
	Int_t nfound = spectrum->Search(fHistPtr,sigma,"nodraw",threshold);
	Float_t *xpeaks = spectrum->GetPositionX();

	for (i=0;i<nfound;i++)
	{
		std::cout << "num peaks (nfound): " << nfound << std::endl;
		std::cout << "peak found at xposition: " << xpeaks[i] << " in bin: " << fHistPtr->GetXaxis()->FindBin(xpeaks[i]) << std::endl; 
	}


TFile fout("peaktest.root","recreate");
TH1F* h = (TH1F*)fHistPtr->Clone("h");
TH1 *background = spectrum->Background(h,20,"");
TH1F *h2 = (TH1F*)h->Clone("h2");
h2->Add(background,-1);
fout.Write();






return 0;
}


