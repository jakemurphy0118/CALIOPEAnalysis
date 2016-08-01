#include "HistoMaker.hh"
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include "EventBuilder.hh"
#include <algorithm>


HistoMaker::HistoMaker(){


	std::cout << "HistoMaker constructor" << std::endl;
	fNumBars = 24;
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

	qdcTree1 = true;//bars 1-8
	qdcTree2 = false;//bars 9-16
	qdcTree3 = false;//bars 17-24

	tdcTree1 = true;//1-8
	tdcTree2 = false;//9-16
	tdcTree3 = false;//17-24

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

void HistoMaker::FillTH1D(TFile *f,std::string histo,double val){

	f->GetObject(histo.c_str(),fHistPtr);
	fHistPtr->Fill(val);

}

void HistoMaker::FillTH2D(TFile *f,std::string histo,double valx,double valy){
	
	f->GetObject(histo.c_str(),fHistPtr);
	fHistPtr->Fill(valx,valy);
}


void HistoMaker::MakeHistos(TTree* tTDC1,TTree* tTDC2,TTree* tTDC3,TTree* tQDC1,TTree* tQDC2,TTree* tQDC3,TFile *f){


//QDC tree access--------------------------------------------------------------------------
	int i;
	int j;

//branch addressing
	Int_t runNumberQ1;
	UInt_t crateQ1;
	UInt_t cardQ1;
	UInt_t eventCountQ1;
	UInt_t nValuesQ1;
	std::vector<UInt_t> *qdc1 = 0;
	std::vector<UInt_t> *qdcUnder1 = 0;
	std::vector<UInt_t> *qdcOverflow1 = 0;
	if (qdcTree1){
		tQDC1->SetBranchAddress("runNumber",&runNumberQ1);
		tQDC1->SetBranchAddress("crate",&crateQ1);
		tQDC1->SetBranchAddress("card",&cardQ1);
		tQDC1->SetBranchAddress("eventCount",&eventCountQ1);
		tQDC1->SetBranchAddress("nValues",&nValuesQ1);
		tQDC1->SetBranchAddress("qdc",&qdc1);
		tQDC1->SetBranchAddress("isUnderThresh",&qdcUnder1);
		tQDC1->SetBranchAddress("isOverflow",&qdcOverflow1);
	}
	Int_t runNumberQ2;
	UInt_t crateQ2;
	UInt_t cardQ2;
	UInt_t eventCountQ2;
	UInt_t nValuesQ2;
	std::vector<UInt_t> *qdc2 = 0;
	std::vector<UInt_t> *qdcUnder2 = 0;
	std::vector<UInt_t> *qdcOverflow2 = 0;
	if (qdcTree2){
		tQDC2->SetBranchAddress("runNumber",&runNumberQ2);
		tQDC2->SetBranchAddress("crate",&crateQ2);
		tQDC2->SetBranchAddress("card",&cardQ2);
		tQDC2->SetBranchAddress("eventCount",&eventCountQ2);
		tQDC2->SetBranchAddress("nValues",&nValuesQ2);
		tQDC2->SetBranchAddress("qdc",&qdc2);
		tQDC2->SetBranchAddress("isUnderThresh",&qdcUnder2);
		tQDC2->SetBranchAddress("isOverflow",&qdcOverflow2);
	}
	Int_t runNumberQ3;
	UInt_t crateQ3;
	UInt_t cardQ3;
	UInt_t eventCountQ3;
	UInt_t nValuesQ3;
	std::vector<UInt_t> *qdc3 = 0;
	std::vector<UInt_t> *qdcUnder3 = 0;
	std::vector<UInt_t> *qdcOverflow3 = 0;
	if (qdcTree3){
		tQDC3->SetBranchAddress("runNumber",&runNumberQ3);
		tQDC3->SetBranchAddress("crate",&crateQ3);
		tQDC3->SetBranchAddress("card",&cardQ3);
		tQDC3->SetBranchAddress("eventCount",&eventCountQ3);
		tQDC3->SetBranchAddress("nValues",&nValuesQ3);
		tQDC3->SetBranchAddress("qdc",&qdc3);
		tQDC3->SetBranchAddress("isUnderThresh",&qdcUnder3);
		tQDC3->SetBranchAddress("isOverflow",&qdcOverflow3);
	}

//create histograms

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
		histObj = "qdcBar" + sbar.str();
		histTitle = "QDC Bar " + sbar.str();
		fHistPtr = new TH1D(histObj.c_str(),histTitle.c_str(),fNumQDCbins,fQDCmin,fQDCmax);
		histObj = "zPosBar" + sbar.str();
		histTitle = "zPos Bar " + sbar.str();
		fHistPtr = new TH1D(histObj.c_str(),histTitle.c_str(),fNumZPosbins,fZPosmin,fZPosmax);
		if (i < 8 && qdcTree1) {
			sch1 << 2*(i%8);
			sch2 << 2*(i%8)+1;
			histObj = "qdc1CH" + sch1.str();
			histTitle = "QDC1 Channel " + sch1.str();
			fHistPtr = new TH1D(histObj.c_str(),histTitle.c_str(),fNumQDCbins,fQDCmin,fQDCmax);
			histObj = "qdc1CH" + sch2.str();
			histTitle = "QDC1 Channel " + sch2.str();
			fHistPtr = new TH1D(histObj.c_str(),histTitle.c_str(),fNumQDCbins,fQDCmin,fQDCmax);
		}
		if (i >= 8 && i < 16 && qdcTree2){
			sch1 << 2*(i%8);
			sch2 << 2*(i%8)+1;
			histObj = "qdc2CH" + sch1.str();
			histTitle = "QDC2 Channel " + sch1.str();
			fHistPtr = new TH1D(histObj.c_str(),histTitle.c_str(),fNumQDCbins,fQDCmin,fQDCmax);
			histObj = "qdc2CH" + sch2.str();
			histTitle = "QDC2 Channel " + sch2.str();
			fHistPtr = new TH1D(histObj.c_str(),histTitle.c_str(),fNumQDCbins,fQDCmin,fQDCmax);
			
		}
		if (i >= 16 && qdcTree3){
			sch1 << 2*(i%8);
			sch2 << 2*(i%8)+1;
			histObj = "qdc3CH" + sch1.str();
			histTitle = "QDC3 Channel " + sch1.str();
			fHistPtr = new TH1D(histObj.c_str(),histTitle.c_str(),fNumQDCbins,fQDCmin,fQDCmax);
			histObj = "qdc3CH" + sch2.str();
			histTitle = "QDC3 Channel " + sch2.str();
			fHistPtr = new TH1D(histObj.c_str(),histTitle.c_str(),fNumQDCbins,fQDCmin,fQDCmax);		
		}

	}
//fill histos(integrating EventBuilder)

	SetInvAttCoeff();
	SetOppositeBars();
	int channel;
	int currentbar;
	int numHitBars;
	double barHitThreshold = 0;
	double qL;
	double qR;
	double q;
	double Econst = 1;
	double zPos;
	bool oppBarEvent;
	long numEntriesQDC1, numEntriesQDC2, numEntriesQDC3, maxEntriesQDC;
	if (qdcTree1) { numEntriesQDC1 = tQDC1->GetEntries(); maxEntriesQDC = numEntriesQDC1;} else { numEntriesQDC1 = 0;}
	if (qdcTree2) { numEntriesQDC2 = tQDC2->GetEntries(); if (numEntriesQDC2 > maxEntriesQDC){maxEntriesQDC = numEntriesQDC2;}} else { numEntriesQDC2 = 0;}
	if (qdcTree3) { numEntriesQDC3 = tQDC3->GetEntries(); if (numEntriesQDC3 > maxEntriesQDC){maxEntriesQDC = numEntriesQDC3;}} else { numEntriesQDC3 = 0;}
	std::cout << "QDC entries: " << maxEntriesQDC << std::endl;

	for (i=0;i<maxEntriesQDC;i++)
	{
		if (i%10000 == 0) {std::cout << "entry " << i << std::endl;}
		EventBuilder *eb = new EventBuilder();
		bool qdcTree1InRange = false;
		bool qdcTree2InRange = false;
		bool qdcTree3InRange = false;
		if (qdcTree1 && i < numEntriesQDC1){tQDC1->GetEntry(i); qdcTree1InRange = true;}
		if (qdcTree2 && i < numEntriesQDC2){tQDC2->GetEntry(i); qdcTree2InRange = true;}
		if (qdcTree3 && i < numEntriesQDC3){tQDC3->GetEntry(i); qdcTree3InRange = true;}

		numHitBars = 0;
		oppBarEvent = false;
		int wasHit[24] = {0};

		//oppBarEvent = eb->WasOppBarEvent(qdc,OppositeBar,wasHit);
		currentbar = 0;

		for (j=0;j<fNumBars;j++){

			qL = 0;
			qR = 0;
			q = 0;
			zPos = 0;
		
			currentbar = j;
			std::stringstream schL, schR, sbar;
			sbar << j+1;
			schL << 2*(currentbar%8);
			schR << 2*(currentbar%8)+1;

			if (j < 8 && qdcTree1InRange){

				qL = eb->GetLeftCharge(qdc1,currentbar);
				qR = eb->GetRightCharge(qdc1,currentbar);
				zPos = eb->ZRecon(qdc1,InvAttCoeff[j],currentbar);
				q = Econst * std::sqrt(qL*qR);

				histObj = "qdc1CH" + schL.str();
				FillTH1D(f,histObj,qL);
				histObj = "qdc1CH" + schR.str();
				FillTH1D(f,histObj,qR);	
			}
			if (j >=8 && j < 16 && qdcTree2InRange){
				qL = eb->GetLeftCharge(qdc2,currentbar);
				qR = eb->GetRightCharge(qdc3,currentbar);
				zPos = eb->ZRecon(qdc2,InvAttCoeff[j],currentbar);
				q = Econst * std::sqrt(qL*qR);

				histObj = "qdc2CH" + schL.str();
				FillTH1D(f,histObj,qL);
				histObj = "qdc2CH" + schR.str();
				FillTH1D(f,histObj,qR);

			}
			if (j >= 16 && qdcTree3InRange){
				qL = eb->GetLeftCharge(qdc3,currentbar);
				qR = eb->GetRightCharge(qdc3,currentbar);
				zPos = eb->ZRecon(qdc3,InvAttCoeff[j],currentbar);	
				q = Econst * std::sqrt(qL*qR);	

				histObj = "qdc3CH" + schL.str();
				FillTH1D(f,histObj,qL);
				histObj = "qdc3CH" + schR.str();
				FillTH1D(f,histObj,qR);

			}
	
			if (q > barHitThreshold){whichBarsHit->Fill(currentbar); numHitBars++; wasHit[j] = 1;}

			histObj = "qdcBar" + sbar.str();
			FillTH1D(f,histObj,q);
			qdcALL->Fill(q);
			if (oppBarEvent) {qdcOppBarEvents->Fill(q);}			
		//zposition reconstruction
			histObj = "zPosBar" + sbar.str();
			FillTH1D(f,histObj,zPos);
			zPosALL->Fill(zPos);
		//charge in bar vs zpos
			energyVSzpos->Fill(zPos,q);	
				
		}
	
		numBarsHit->Fill(numHitBars);

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
	Int_t runNumberT1;
	UInt_t crateT1;
	UInt_t cardT1;
	UInt_t eventCountT1;
	UInt_t nValuesT1;
	std::vector<UInt_t> *tdc1 = 0;
	std::vector<UInt_t> *tdcUnder1 = 0;
	std::vector<UInt_t> *tdcOverflow1 = 0;
	if (tdcTree1){
		tTDC1->SetBranchAddress("runNumber",&runNumberT1);
		tTDC1->SetBranchAddress("crate",&crateT1);
		tTDC1->SetBranchAddress("card",&cardT1);
		tTDC1->SetBranchAddress("eventCount",&eventCountT1);
		tTDC1->SetBranchAddress("nValues",&nValuesT1);
		tTDC1->SetBranchAddress("tdc",&tdc1);
		tTDC1->SetBranchAddress("isUnderThresh",&tdcUnder1);
		tTDC1->SetBranchAddress("isOverflow",&tdcOverflow1);
	}
	Int_t runNumberT2;
	UInt_t crateT2;
	UInt_t cardT2;
	UInt_t eventCountT2;
	UInt_t nValuesT2;
	std::vector<UInt_t> *tdc2 = 0;
	std::vector<UInt_t> *tdcUnder2 = 0;
	std::vector<UInt_t> *tdcOverflow2 = 0;
	if (tdcTree2){
		tTDC2->SetBranchAddress("runNumber",&runNumberT2);
		tTDC2->SetBranchAddress("crate",&crateT2);
		tTDC2->SetBranchAddress("card",&cardT2);
		tTDC2->SetBranchAddress("eventCount",&eventCountT2);
		tTDC2->SetBranchAddress("nValues",&nValuesT2);
		tTDC2->SetBranchAddress("tdc",&tdc2);
		tTDC2->SetBranchAddress("isUnderThresh",&tdcUnder2);
		tTDC2->SetBranchAddress("isOverflow",&tdcOverflow2);
	}
	Int_t runNumberT3;
	UInt_t crateT3;
	UInt_t cardT3;
	UInt_t eventCountT3;
	UInt_t nValuesT3;
	std::vector<UInt_t> *tdc3 = 0;
	std::vector<UInt_t> *tdcUnder3 = 0;
	std::vector<UInt_t> *tdcOverflow3 = 0;
	if (tdcTree3){
		tTDC3->SetBranchAddress("runNumber",&runNumberT3);
		tTDC3->SetBranchAddress("crate",&crateT3);
		tTDC3->SetBranchAddress("card",&cardT3);
		tTDC3->SetBranchAddress("eventCount",&eventCountT3);
		tTDC3->SetBranchAddress("nValues",&nValuesT3);
		tTDC3->SetBranchAddress("tdc",&tdc3);
		tTDC3->SetBranchAddress("isUnderThresh",&tdcUnder3);
		tTDC3->SetBranchAddress("isOverflow",&tdcOverflow3);
	}
	
//create histograms


	
	TH1D *tdcALL = new TH1D("tdcALL","TDC All Channels",fNumTDCbins,fTDCmin,fTDCmax);

	for (i=0;i<fNumBars;i++) 
	{
		std::stringstream sbar;
		std::stringstream sch1;
		std::stringstream sch2;
		sbar << i+1;
		histObj = "tdcBar" + sbar.str();
		histTitle = "TDC Bar " + sbar.str();
		fHistPtr = new TH1D(histObj.c_str(),histTitle.c_str(),fNumTDCbins,fTDCmin,fTDCmax);
		if (i < 8 && tdcTree1){
			sch1 << 2*(i%8);
			sch2 << 2*(i%8)+1;
			histObj = "tdc1CH" + sch1.str();
			histTitle = "TDC1 Channel " + sch1.str();
			fHistPtr = new TH1D(histObj.c_str(),histTitle.c_str(),fNumTDCbins,fTDCmin,fTDCmax);
			histObj = "tdc1CH" + sch2.str();
			histTitle = "TDC1 Channel " + sch2.str();
			fHistPtr = new TH1D(histObj.c_str(),histTitle.c_str(),fNumTDCbins,fTDCmin,fTDCmax);
		}
		if (i >= 8 && i < 16 && tdcTree2){
			sch1 << 2*(i%8);
			sch2 << 2*(i%8)+1;
			histObj = "tdc2CH" + sch1.str();
			histTitle = "TDC2 Channel " + sch1.str();
			fHistPtr = new TH1D(histObj.c_str(),histTitle.c_str(),fNumTDCbins,fTDCmin,fTDCmax);
			histObj = "tdc2CH" + sch2.str();
			histTitle = "TDC2 Channel " + sch2.str();
			fHistPtr = new TH1D(histObj.c_str(),histTitle.c_str(),fNumTDCbins,fTDCmin,fTDCmax);
		}
		if (i >= 16 && tdcTree3){
			sch1 << 2*(i%8);
			sch2 << 2*(i%8)+1;
			histObj = "tdc3CH" + sch1.str();
			histTitle = "TDC3 Channel " + sch1.str();
			fHistPtr = new TH1D(histObj.c_str(),histTitle.c_str(),fNumTDCbins,fTDCmin,fTDCmax);
			histObj = "tdc3CH" + sch2.str();
			histTitle = "TDC3 Channel " + sch2.str();
			fHistPtr = new TH1D(histObj.c_str(),histTitle.c_str(),fNumTDCbins,fTDCmin,fTDCmax);
		}

	}
	
//fill histos

	long numEntriesTDC1, numEntriesTDC2, numEntriesTDC3, maxEntriesTDC;
	if (tdcTree1){ numEntriesTDC1 = tTDC1->GetEntries(); maxEntriesTDC = numEntriesTDC1;} else {numEntriesTDC1 = 0;}
	if (tdcTree2){ numEntriesTDC2 = tTDC2->GetEntries(); if (numEntriesTDC2 > maxEntriesTDC){ maxEntriesTDC = numEntriesTDC2;}} else {numEntriesTDC2 = 0;}
	if (tdcTree3){ numEntriesTDC3 = tTDC3->GetEntries(); if (numEntriesTDC3 > maxEntriesTDC){ maxEntriesTDC = numEntriesTDC3;}} else {numEntriesTDC3 = 0;}
	std::cout << "TDC entries " << maxEntriesTDC << std::endl;

	double tL, tR, t;

	for (i=0;i<maxEntriesTDC;i++){

		if (i%10000 == 0) {std::cout << "entry " << i << std::endl;}

		bool tdcTree1InRange = false;
		bool tdcTree2InRange = false;
		bool tdcTree3InRange = false;

		if (tdcTree1 && i < numEntriesTDC1){tdcTree1InRange = true; tTDC1->GetEntry(i);}
		if (tdcTree2 && i < numEntriesTDC2){tdcTree2InRange = true; tTDC2->GetEntry(i);}
		if (tdcTree3 && i < numEntriesTDC3){tdcTree3InRange = true; tTDC3->GetEntry(i);}

		EventBuilder* eb = new EventBuilder();

		for (j=0;j<fNumBars;j++)
		{
			tL = 0;
			tR = 0;
			t = 0;
			std::stringstream sbar;
			std::stringstream sch1;
			std::stringstream sch2;
			sbar << j+1;
			sch1 << 2*(currentbar%8);
			sch2 << 2*(currentbar%8)+1;
			currentbar = j;

			if (j < 8 && tdcTree1InRange){
				tL = eb->GetLeftTDCVal(tdc1,currentbar);
				tR = eb->GetRightTDCVal(tdc1,currentbar);
				t = tL + tR;
				histObj = "tdc1CH" + sch1.str();
				FillTH1D(f,histObj,tL);
				histObj = "tdc1CH" + sch2.str();
				FillTH1D(f,histObj,tR);
				histObj = "tdcBar" + sbar.str();
				FillTH1D(f,histObj,t);											
			}
			if (j >= 8 && j < 16 && tdcTree2InRange){
				tL = eb->GetLeftTDCVal(tdc2,currentbar);
				tR = eb->GetRightTDCVal(tdc2,currentbar);
				t = tL + tR;
				histObj = "tdc2CH" + sch1.str();
				FillTH1D(f,histObj,tL);
				histObj = "tdc2CH" + sch2.str();
				FillTH1D(f,histObj,tR);
				histObj = "tdcBar" + sbar.str();
				FillTH1D(f,histObj,t);											
			}
			if (j >= 16 && tdcTree3InRange){
				tL = eb->GetLeftTDCVal(tdc3,currentbar);
				tR = eb->GetRightTDCVal(tdc3,currentbar);
				t = tL + tR;
				histObj = "tdc3CH" + sch1.str();
				FillTH1D(f,histObj,tL);
				histObj = "tdc3CH" + sch2.str();
				FillTH1D(f,histObj,tR);
				histObj = "tdcBar" + sbar.str();
				FillTH1D(f,histObj,t);											
			}
			
		}
		
		delete eb;		
	}

}








void HistoMaker::DeleteHistos(TFile* f){

	int i;
	
//qdc,zpos
	for (i=0;i<fNumBars;i++)
	{
		std::stringstream sbar;
		std::stringstream schL;
		std::stringstream schR;
		sbar << i+1;
		histObj = "qdcBar" + sbar.str();
		f->GetObject(histObj.c_str(),fHistPtr);
		delete fHistPtr;
		if (i < 8 && qdcTree1){
			schL << 2*((i+1)%8)-2;
			schR << 2*((i+1)%8)-1;
			histObj = "qdc1CH" + schL.str();
			f->GetObject(histObj.c_str(),fHistPtr);
			delete fHistPtr;
			histObj = "qdc1CH" + schR.str();
			f->GetObject(histObj.c_str(),fHistPtr);
		}
		if (i >= 8 && i < 16 && qdcTree2){
			schL << 2*((i+1)%8)-2;
			schR << 2*((i+1)%8)-1;
			histObj = "qdc2CH" + schL.str();
			f->GetObject(histObj.c_str(),fHistPtr);
			delete fHistPtr;
			histObj = "qdc2CH" + schR.str();
			f->GetObject(histObj.c_str(),fHistPtr);			
		}
		if (i >= 16 && qdcTree3){
			schL << 2*((i+1)%8)-2;
			schR << 2*((i+1)%8)-1;
			histObj = "qdc3CH" + schL.str();
			f->GetObject(histObj.c_str(),fHistPtr);
			delete fHistPtr;
			histObj = "qdc3CH" + schR.str();
			f->GetObject(histObj.c_str(),fHistPtr);
		}

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

	for (i=0;i<fNumBars;i++){

		std::stringstream sbar;
		std::stringstream schL;
		std::stringstream schR;
		sbar << i+1;
		histObj = "tdcBar" + sbar.str();
		f->GetObject(histObj.c_str(),fHistPtr);
		delete fHistPtr;
		if (i < 8 && tdcTree1){
			schL << 2*((i+1)%8)-2;
			schR << 2*((i+1)%8)-1;
			histObj = "tdc1CH" + schL.str();
			f->GetObject(histObj.c_str(),fHistPtr);
			delete fHistPtr;
			histObj = "tdc1CH" + schR.str();
			f->GetObject(histObj.c_str(),fHistPtr);
		}
		if (i >= 8 && i < 16 && tdcTree2){
			schL << 2*((i+1)%8)-2;
			schR << 2*((i+1)%8)-1;
			histObj = "tdc2CH" + schL.str();
			f->GetObject(histObj.c_str(),fHistPtr);
			delete fHistPtr;
			histObj = "tdc2CH" + schR.str();
			f->GetObject(histObj.c_str(),fHistPtr);			
		}
		if (i >= 16 && tdcTree3){
			schL << 2*((i+1)%8)-2;
			schR << 2*((i+1)%8)-1;
			histObj = "tdc3CH" + schL.str();
			f->GetObject(histObj.c_str(),fHistPtr);
			delete fHistPtr;
			histObj = "tdc3CH" + schR.str();
			f->GetObject(histObj.c_str(),fHistPtr);
		}

	}		

	f->GetObject("tdcALL",fHistPtr);
	delete fHistPtr;
}
