#include "HistoMaker.hh"
#include <string>
#include <sstream>
#include <vector>


HistoMaker::HistoMaker(){

	fNumBars = 16;
	fNumQDCbins = 100;
	fQDCmin = 0;
	fQDCmax = 400;
	fNumTDCbins = 100;
	fTDCmax = 500;
	fTDCmin = 0;
	fNumZPosbins = 100;
	fZPosmax = 200;
	fZPosmin = 0;
	histObj = "";
	histTitle = "";
}


HistoMaker::~HistoMaker(){}


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

	int ch[2];


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
	
//fill bar histos
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
	
//qdc
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

	f->GetObject("qdcALL",fHistPtr);
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
