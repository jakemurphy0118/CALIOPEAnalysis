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
	histObj = "";
	histTitle = "";
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
	
	TH1D *qdcALL = new TH1D("qdcALL","QDC All Channels",fNumQDCbins,fQDCmin,fQDCmax);

	for (i=0;i<fNumBars;i++) 
	{
		std::stringstream sbar;
		std::stringstream sch1;
		std::stringstream sch2;
		sbar << i+1;
		sch1 << i;
		sch2 << i+16;
		histObj = "qdcBar" + sbar.str();
		histTitle = "QDC Bar " + sbar.str();
		fHistPtr = new TH1D(histObj.c_str(),histTitle.c_str(),fNumQDCbins,fQDCmin,fQDCmax);
		histObj = "qdc" + sch1.str();
		histTitle = "QDC Channel " + sch1.str();
		fHistPtr = new TH1D(histObj.c_str(),histTitle.c_str(),fNumQDCbins,fQDCmin,fQDCmax);
		histObj = "qdc" + sch2.str();
		histTitle = "QDC Channel " + sch2.str();
		fHistPtr = new TH1D(histObj.c_str(),histTitle.c_str(),fNumQDCbins,fQDCmin,fQDCmax);

	}
	
//fill bar histos
	for (i=0;i<numEntries;i++)
	{
		t->GetEntry(i);

		for (j=0;j<fNumBars;j++)
		{
			std::stringstream sbar;
			std::stringstream sch1;
			std::stringstream sch2;
			sbar << j+1;
			sch1 << j;
			sch2 << j+16;
			histObj = "qdcBar" + sbar.str();
			f->GetObject(histObj.c_str(),fHistPtr);
			int * ch = GetChannelsForBar(j+1);
			fHistPtr->Fill(qdc->at(ch[0]));
			fHistPtr->Fill(qdc->at(ch[1]));
			histObj = "qdc" + sch1.str();
			f->GetObject(histObj.c_str(),fHistPtr);
			fHistPtr->Fill(qdc->at(j));
			histObj = "qdc" + sch2.str();
			f->GetObject(histObj.c_str(),fHistPtr);
			fHistPtr->Fill(qdc->at(j+16));
			qdcALL->Fill(qdc->at(j));
			qdcALL->Fill(qdc->at(j+16));			
		}
				
	}
}






void EnergyCal::DeleteBarHistos(TFile *f){
//delete histos

	int i;
	

	for (i=0;i<fNumBars;i++)
	{
		std::stringstream sbar;
		std::stringstream sch1;
		std::stringstream sch2;
		sbar << i+1;
		sch1 << i;
		sch2 << i+16;
		histObj = "qdcBar" + sbar.str();
		f->GetObject(histObj.c_str(),fHistPtr);
		delete fHistPtr;
		histObj = "qdc" + sch1.str();
		f->GetObject(histObj.c_str(),fHistPtr);
		delete fHistPtr;
		histObj = "qdc" + sch2.str();
		f->GetObject(histObj.c_str(),fHistPtr);
		delete fHistPtr;
	}		


}
