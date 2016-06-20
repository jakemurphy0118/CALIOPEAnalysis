#include "HistoMaker.hh"
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include "EventBuilder.hh"


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
	InvAttCoeff[16] = 1;
	InvAttCoeff[17] = 1;
	InvAttCoeff[18] = 1;
	InvAttCoeff[19] = 1;
	InvAttCoeff[20] = 1;
	InvAttCoeff[21] = 1;
	InvAttCoeff[22] = 1;
	InvAttCoeff[23] = 1;

}

void HistoMaker::SetOppositeBars(){
//input: bar#-1, output: opp bar#
//example: oppositebar[0] = 5 tells you the opposite bar of bar 1 is bar 5
	OppositeBar[0] = 5;
	OppositeBar[1] = 6;
	OppositeBar[2] = 7;
	OppositeBar[3] = 24;
	OppositeBar[4] = 1;
	OppositeBar[5] = 2;
	OppositeBar[6] = 3;
	OppositeBar[7] = 9;
	OppositeBar[8] = 8;
	OppositeBar[9] = 17;
	OppositeBar[10] = 18;
	OppositeBar[11] = 19;
	OppositeBar[12] = 20;
	OppositeBar[13] = 21;
	OppositeBar[14] = 22;
	OppositeBar[15] = 23;
	OppositeBar[16] = 10;
	OppositeBar[17] = 11;
	OppositeBar[18] = 12;
	OppositeBar[19] = 13;
	OppositeBar[20] = 14;
	OppositeBar[21] = 15;
	OppositeBar[22] = 16;
	OppositeBar[23] = 4;

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
	TH1D *numBarsHit = new TH1D("numBarsHit","Total Number of Bars Hit Per Event",24,0,24);
	TH1D *whichBarsHit = new TH1D("whichBarsHit","Number of times each bar was hit per Run",24,0,24);
	TH1D *qdcOppBarEvents = new TH1D("qdcOppBarEvents","Fill if event had opposite bars hit",fNumQDCbins,fQDCmin,fQDCmax);

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
//fill histos(integrating EventBuilder)

	SetInvAttCoeff();
	SetOppositeBars();
	int channel;
	int currentbar;
	int numHitBars;
	int wasHit[24] = {0};
	UInt_t barHitThreshold = 0;
	double qL;
	double qR;
	double q;
	double zPos;
	bool oppBarEvent;

	for (i=0;i<numEntries;i++)
	{
		EventBuilder *eb = new EventBuilder();
		tQDC->GetEntry(i);
		numHitBars = eb->NumOfHitBars(qdc,barHitThreshold);
		eb->WhichBars(qdc,wasHit,barHitThreshold);
		oppBarEvent = eb->WasOppBarEvent(qdc,OppositeBar,wasHit);
		qL = 0;
		qR = 0;
		q = 0;
		zPos = 0;
		currentbar = 0;

		for (j=0;j<16;j++)
		{
			currentbar = j+1;
			qL = eb->GetLeftCharge(qdc,currentbar);
			qR = eb->GetRightCharge(qdc,currentbar);
			q = qL + qR;
			zPos = eb->ZRecon(qdc,InvAttCoeff[j],currentbar);	

			std::stringstream sbar;
			sbar << j+1;
			std::stringstream schL;
			schL << 2*(j+1) - 2;
			std::stringstream schR;
			schR << 2*(j+1) - 1;

			histObj = "qdcBar" + sbar.str();
			f->GetObject(histObj.c_str(),fHistPtr);
			fHistPtr->Fill(q);
			qdcALL->Fill(q);
			if (oppBarEvent) {qdcOppBarEvents->Fill(q);}			

			histObj = "qdc" + schL.str();
			f->GetObject(histObj.c_str(),fHistPtr);
			fHistPtr->Fill(qL);
			
			histObj = "qdc" + schR.str();
			f->GetObject(histObj.c_str(),fHistPtr);
			fHistPtr->Fill(qR);

			histObj = "zPosBar" + sbar.str();
			f->GetObject(histObj.c_str(),fHistPtr);
			fHistPtr->Fill(zPos);
			zPosALL->Fill(zPos);
			energyVSzpos->Fill(zPos,q);	
				
		}
		
		numBarsHit->Fill(numHitBars);
		for (j=0;j<fNumBars;j++) { if (wasHit[j] == 1) { whichBarsHit->Fill(j+1); } }		

		delete eb;
	}
//fill histos
/*
	int ch[2];
	double q1;
	double q2;
	int barsHit;
	UInt_t barHitThresh = 0;
	//int wasHit[24] = {0};


	SetInvAttCoeff();
	SetOppositeBars();


	for (i=0;i<numEntries;i++)
	{
		tQDC->GetEntry(i);
		barsHit = 0;

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
			q1 = (double)qdc->at(ch[0]);
			q2 = (double)qdc->at(ch[1]);
			fHistPtr->Fill(q1 + q2);
			qdcALL->Fill(q1 + q2);
			histObj = "zPosBar" + sbar.str();
			f->GetObject(histObj.c_str(),fHistPtr);
			if ((q1!=0) && (q2!=0))
			{

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
		//numbars hit/which ones
			wasHit[j] = 0;
			if ( (q1 > barHitThresh) && (q2 > barHitThresh) )
			{
				barsHit++;
				whichBarsHit->Fill(j);
				wasHit[j] = 1;
			}
				
		}
	
		numBarsHit->Fill(barsHit);
	//2 bar events (must be opposite)
		if (barsHit == 2) 
		{
			for (j=0;j<16;j++) 
			{
				int oppbar = OppositeBar[j];
				if ( (wasHit[j]==1) && (wasHit[oppbar-1]==1) )
				{
					ch[0] = (j+1) + (j+1) - 2;
					ch[1] = ch[0] + 1;
					qdcOppBarEvents->Fill( qdc->at(ch[0]) + qdc->at(ch[1]) );
					break;
				}
			}
		}	
		
				
	}

*/
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
	int ch[2];
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
	f->GetObject("numBarsHit",fHistPtr);
	delete fHistPtr;
	f->GetObject("whichBarsHit",fHistPtr);
	delete fHistPtr;
	f->GetObject("qdcOppBarEvents",fHistPtr);
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
