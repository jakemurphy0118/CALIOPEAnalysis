#include "EnergyCal.hh"
#include <string>
#include <sstream>
#include <vector>
#include <TSpectrum.h>


EnergyCal::EnergyCal(){
	fNumBars = 16;
	fNumQDCbins = 100;
	fQDCmin = 0;
	fQDCmax = 200;
	fNumChannels = 16;
}

EnergyCal::~EnergyCal(){};

std::vector<double> * EnergyCal::Calibrate(TTree* t, TFile* f){

	MakeBarHistos(t,f);

	std::vector<double> *scalingFactors = 0;
//for peak finding (TSpectrum)
	Int_t npeaks = 3;
	float sigma = 5;
	float threshold = 0.05;
/*	double PeakEnergies[npeaks];
//assigned in increasing order of energy
	PeakEnergies[0] = 511;	//annihilation
	PeakEnergies[1] = 1022; //double
	PeakEnergies[2] = 1274; //gamma?
*/	



	int i;
	int j;

	for (i=0;i<fNumBars;i++)
	{	
		std::stringstream ss;
		ss << i+1;
		std::string bar = ss.str();
		std::string histObj = "qdcBar";
		histObj = histObj + bar;
		const char *Obj = histObj.c_str();
		f->GetObject(Obj,fHistPtr);

		TSpectrum *spectrum = new TSpectrum(npeaks);
		Int_t nfound = spectrum->Search(fHistPtr,sigma,"",threshold);
		Float_t *xpeaks = spectrum->GetPositionX();

		for (j=0;j<nfound;j++)
		{
			std::cout << "xposition: " << xpeaks[j] << " found for bar " << bar << std::endl;			
		}
	}
	


	return scalingFactors;
}

void EnergyCal::MakeBarHistos(TTree* t,TFile *f){


//branch addressing
	Int_t runNumber2;
	UInt_t crate2;
	UInt_t card2;
	UInt_t eventCount2;
	UInt_t nValues2;
	std::vector<UInt_t> *qdc = 0;
	std::vector<UInt_t> *qdcUnder = 0;
	std::vector<UInt_t> *qdcOverflow = 0;

	t->SetBranchAddress("runNumber",&runNumber2);
	t->SetBranchAddress("crate",&crate2);
	t->SetBranchAddress("card",&card2);
	t->SetBranchAddress("eventCount",&eventCount2);
	t->SetBranchAddress("nValues",&nValues2);
	t->SetBranchAddress("qdc",&qdc);
	t->SetBranchAddress("isUnderThresh",&qdcUnder);
	t->SetBranchAddress("isOverflow",&qdcOverflow);

//create histograms

	int i;
	int j;

	long numEntries = t->GetEntries();

	for (i=0;i<fNumBars;i++) 
	{
		std::stringstream ss;
		ss << i+1;
		std::string bar = ss.str();
		std::string histObj = "qdcBar";
		std::string histTitle = "QDC Bar ";
		histObj = histObj + bar;
		histTitle = histTitle + bar;
		const char *Obj = histObj.c_str();
		const char *Title = histTitle.c_str();
		fHistPtr = new TH1D(Obj,Title,fNumQDCbins,fQDCmin,fQDCmax);
	}
	
//fill bar histos
	for (i=0;i<numEntries;i++)
	{
		t->GetEntry(i);

		for (j=0;j<fNumBars;j++)
		{
			std::stringstream ss;
			ss << j+1;
			std::string bar = ss.str();
			std::string histObj = "qdcBar";
			histObj = histObj + bar;
			const char *Obj = histObj.c_str();
			f->GetObject(Obj,fHistPtr);
			int * ch = GetChannelsForBar(j+1);
			fHistPtr->Fill(qdc->at(ch[0]));
			fHistPtr->Fill(qdc->at(ch[1]));			
		}
				
	}
}


void EnergyCal::DeleteBarHistos(TFile *f){
//delete histos

	int i;

	for (i=0;i<fNumBars;i++)
	{
		std::stringstream ss;
		ss << i+1;
		std::string bar = ss.str();
		std::string histObj = "qdcBar";
		histObj = histObj + bar;
		const char *Obj = histObj.c_str();
		f->GetObject(Obj,fHistPtr);
		delete fHistPtr;
	}		


}
