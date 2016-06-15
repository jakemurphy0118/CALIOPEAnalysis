#include "HistoMaker.hh"
#include <string>
#include <sstream>
#include <vector>
#include <cmath>


HistoMaker::HistoMaker(){

	fNumBars = 16;
	fNumQDCbins = 200;
	fQDCmin = 0;
	fQDCmax = 700;
	fNumTDCbins = 200;
	fTDCmax = 700;
	fTDCmin = 0;
	fNumZPosbins = 100;
	fZPosmax = 3;
	fZPosmin = -3;
	histObj = "";
	histTitle = "";
}


HistoMaker::~HistoMaker(){}

void HistoMaker::SetInvAttCoeff(){

	InvAttCoeff[0] = 1;
	InvAttCoeff[1] = 1;
	InvAttCoeff[2] = 1;
	InvAttCoeff[3] = 1;
	InvAttCoeff[4] = 1;
	InvAttCoeff[5] = 1;
	InvAttCoeff[6] = 1;
	InvAttCoeff[7] = 1;
	InvAttCoeff[8] = 1;
	InvAttCoeff[9] = 1;
	InvAttCoeff[10] = 1;
	InvAttCoeff[11] = 1;
	InvAttCoeff[12] = 1;
	InvAttCoeff[13] = 1;
	InvAttCoeff[14] = 1;
	InvAttCoeff[15] = 1;

}


void HistoMaker::MakeHistos(TTree* tTDC,TTree* tQDC,TFile *f){


//QDC tree access--------------------------------------------------------------------------

//branch addressing
	Int_t runNumber2;
	UInt_t crate2;
	UInt_t card2;
	UInt_t eventCount2;
	UInt_t nValues2;
	std::vector<UInt_t> *qdc = 0;
	std::vector<UInt_t> *qdcUnder = 0;
	std::vector<UInt_t> *qdcOverflow = 0;

	tQDC->SetBranchAddress("runNumber",&runNumber2);
	tQDC->SetBranchAddress("crate",&crate2);
	tQDC->SetBranchAddress("card",&card2);
	tQDC->SetBranchAddress("eventCount",&eventCount2);
	tQDC->SetBranchAddress("nValues",&nValues2);
	tQDC->SetBranchAddress("qdc",&qdc);
	tQDC->SetBranchAddress("isUnderThresh",&qdcUnder);
	tQDC->SetBranchAddress("isOverflow",&qdcOverflow);

//create histograms

	int i;
	int j;


	long numEntries = tQDC->GetEntries();
	
	TH1D *qdcALL = new TH1D("qdcALL","QDC All Bars",fNumQDCbins,fQDCmin,fQDCmax);
	TH1D *zPosALL = new TH1D("zPosALL","zPos All Bars",fNumZPosbins,fZPosmin,fZPosmax);
	TH2D *energyVSzpos = new TH2D("energyVSzpos","energy vs zpos",fNumZPosbins,fZPosmin,fZPosmax,fNumQDCbins,fQDCmin,fQDCmax);

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
		histObj = "zPosBar" + sbar.str();
		histTitle = "zPos Bar " + sbar.str();
		fHistPtr = new TH1D(histObj.c_str(),histTitle.c_str(),fNumZPosbins,fZPosmin,fZPosmax);
		histObj = "qdc" + sch1.str();
		histTitle = "QDC Channel " + sch1.str();
		fHistPtr = new TH1D(histObj.c_str(),histTitle.c_str(),fNumQDCbins,fQDCmin,fQDCmax);
		histObj = "qdc" + sch2.str();
		histTitle = "QDC Channel " + sch2.str();
		fHistPtr = new TH1D(histObj.c_str(),histTitle.c_str(),fNumQDCbins,fQDCmin,fQDCmax);

	}
	
//fill histos

	int ch[2];
	double q1;
	double q2;


	SetInvAttCoeff();


	for (i=0;i<numEntries;i++)
	{
		tQDC->GetEntry(i);

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
			ch[0] = (j+1) + (j+1) - 2;
			ch[1] = ch[0] + 1;
			fHistPtr->Fill(qdc->at(ch[0]) + qdc->at(ch[1]));
			qdcALL->Fill(qdc->at(ch[0]) + qdc->at(ch[1]));
			histObj = "zPosBar" + sbar.str();
			f->GetObject(histObj.c_str(),fHistPtr);
			if ((qdc->at(ch[0])!=0) && (qdc->at(ch[1])!=0))
			{
				q1 = (double)qdc->at(ch[0]);
				q2 = (double)qdc->at(ch[1]);
				fHistPtr->Fill(InvAttCoeff[j]*log(q1/q2));
				zPosALL->Fill(InvAttCoeff[j]*log(q1/q2));
				energyVSzpos->Fill(InvAttCoeff[j]*log(q1/q2),q1+q2);
			}			
			histObj = "qdc" + sch1.str();
			f->GetObject(histObj.c_str(),fHistPtr);
			fHistPtr->Fill(qdc->at(j));
			histObj = "qdc" + sch2.str();
			f->GetObject(histObj.c_str(),fHistPtr);
			fHistPtr->Fill(qdc->at(j+16));			
		}
				
	}


//END QDC tree access--------------------------------------------------------------------------------


//TDC tree access------------------------------------------------------------------------------------

//branch addressing
	Int_t runNumber;
	UInt_t crate;
	UInt_t card;
	UInt_t eventCount;
	UInt_t nValues;
	std::vector<UInt_t> *tdc = 0;
	std::vector<UInt_t> *tdcUnder = 0;
	std::vector<UInt_t> *tdcOverflow = 0;

	tTDC->SetBranchAddress("runNumber",&runNumber);
	tTDC->SetBranchAddress("crate",&crate);
	tTDC->SetBranchAddress("card",&card);
	tTDC->SetBranchAddress("eventCount",&eventCount);
	tTDC->SetBranchAddress("nValues",&nValues);
	tTDC->SetBranchAddress("tdc",&tdc);
	tTDC->SetBranchAddress("isUnderThresh",&tdcUnder);
	tTDC->SetBranchAddress("isOverflow",&tdcOverflow);

//create histograms

	numEntries = tTDC->GetEntries();
	
	TH1D *tdcALL = new TH1D("tdcALL","TDC All Channels",fNumTDCbins,fTDCmin,fTDCmax);

	for (i=0;i<fNumBars;i++) 
	{
		std::stringstream sbar;
		std::stringstream sch1;
		std::stringstream sch2;
		sbar << i+1;
		sch1 << i;
		sch2 << i+16;
		histObj = "tdcBar" + sbar.str();
		histTitle = "TDC Bar " + sbar.str();
		fHistPtr = new TH1D(histObj.c_str(),histTitle.c_str(),fNumTDCbins,fTDCmin,fTDCmax);
		histObj = "tdc" + sch1.str();
		histTitle = "TDC Channel " + sch1.str();
		fHistPtr = new TH1D(histObj.c_str(),histTitle.c_str(),fNumTDCbins,fTDCmin,fTDCmax);
		histObj = "tdc" + sch2.str();
		histTitle = "TDC Channel " + sch2.str();
		fHistPtr = new TH1D(histObj.c_str(),histTitle.c_str(),fNumTDCbins,fTDCmin,fTDCmax);

	}
	
//fill histos
	for (i=0;i<numEntries;i++)
	{
		tTDC->GetEntry(i);

		for (j=0;j<fNumBars;j++)
		{
			std::stringstream sbar;
			std::stringstream sch1;
			std::stringstream sch2;
			sbar << j+1;
			sch1 << j;
			sch2 << j+16;
			histObj = "tdcBar" + sbar.str();
			f->GetObject(histObj.c_str(),fHistPtr);
			ch[0] = (j+1) + (j+1) - 2;
			ch[1] = ch[0] + 1;
			fHistPtr->Fill(tdc->at(ch[0]));
			fHistPtr->Fill(tdc->at(ch[1]));
			histObj = "tdc" + sch1.str();
			f->GetObject(histObj.c_str(),fHistPtr);
			fHistPtr->Fill(tdc->at(j));
			histObj = "tdc" + sch2.str();
			f->GetObject(histObj.c_str(),fHistPtr);
			fHistPtr->Fill(tdc->at(j+16));
			tdcALL->Fill(tdc->at(j));
			tdcALL->Fill(tdc->at(j+16));			
		}
				
	}

}








void HistoMaker::DeleteHistos(TFile* f){

	int i;
	
//qdc,zpos
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
		histObj = "qdc" + sbar.str();
		f->GetObject(histObj.c_str(),fHistPtr);
		delete fHistPtr;
	}		

	f->GetObject("qdcALL",fHistPtr);
	delete fHistPtr;
	f->GetObject("zPosALL",fHistPtr);
	delete fHistPtr;
	f->GetObject("energyVSzpos",fHistPtr);
	delete fHistPtr;

//tdc

	for (i=0;i<fNumBars;i++)
	{
		std::stringstream sbar;
		std::stringstream sch1;
		std::stringstream sch2;
		sbar << i+1;
		sch1 << i;
		sch2 << i+16;
		histObj = "tdcBar" + sbar.str();
		f->GetObject(histObj.c_str(),fHistPtr);
		delete fHistPtr;
		histObj = "tdc" + sch1.str();
		f->GetObject(histObj.c_str(),fHistPtr);
		delete fHistPtr;
		histObj = "tdc" + sch2.str();
		f->GetObject(histObj.c_str(),fHistPtr);
		delete fHistPtr;
	}		

	f->GetObject("tdcALL",fHistPtr);
	delete fHistPtr;
}
