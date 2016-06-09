#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int main(int argc, char** argv){

//get file
	if (argc != 2){ std::cout << "Supply root file" << std::endl;}
	const char *FileName = argv[1];
	std::cout << "FileName: " << FileName << std::endl;
	
	TFile f(FileName);


//branch addresses
//tdc
	Int_t runNumber;
	UInt_t crate;
	UInt_t card;
	UInt_t eventCount;
	UInt_t nValues;
	vector<UInt_t> *tdc = 0;
	vector<UInt_t> *tdcUnder = 0;
	vector<UInt_t> *tdcOverflow = 0;

	TTree *t;
	f.GetObject("treeName",t);

	t->SetBranchAddress("runNumber",&runNumber);
	t->SetBranchAddress("crate",&crate);
	t->SetBranchAddress("card",&card);
	t->SetBranchAddress("eventCount",&eventCount);
	t->SetBranchAddress("nValues",&nValues);
	t->SetBranchAddress("tdc",&tdc);
	t->SetBranchAddress("isUnderThresh",&tdcUnder);
	t->SetBranchAddress("isOverflow",&tdcOverflow);
//qdc
	Int_t runNumber2;
	UInt_t crate2;
	UInt_t card2;
	UInt_t eventCount2;
	UInt_t nValues2;
	vector<UInt_t> *qdc = 0;
	vector<UInt_t> *qdcUnder = 0;
	vector<UInt_t> *qdcOverflow = 0;

	TTree *t2;
	f.GetObject("treeName_2",t2);

	t2->SetBranchAddress("runNumber",&runNumber2);
	t2->SetBranchAddress("crate",&crate2);
	t2->SetBranchAddress("card",&card2);
	t2->SetBranchAddress("eventCount",&eventCount2);
	t2->SetBranchAddress("nValues",&nValues2);
	t2->SetBranchAddress("qdc",&qdc);
	t2->SetBranchAddress("isUnderThresh",&qdcUnder);
	t2->SetBranchAddress("isOverflow",&qdcOverflow);


//create output file
	std::string inputFile = argv[1];
	std::string outputFile;
	std::string outputFile1;
	
	if( inputFile.find(".") < inputFile.length() ) {
        	if( inputFile.substr(inputFile.find_last_of(".")) == ".root" ) {
            		outputFile = inputFile.substr(0, inputFile.find_last_of(".") );
			outputFile1 = outputFile + "Histos.root";
        	}
    	}
	
	const char *histos = outputFile1.c_str();
	TFile* fnew = new TFile(histos,"recreate");
	

//variables for filling,etc

	int i;
	int j;
	TH1D* histPtr;

//tdc
	long numEntries = t->GetEntries();
	int numChannels = 32;
	int numTDCbins = 100;
	int TDCmin = 0;
	int TDCmax = 400;

//qdc
	long numEntries2 = t2->GetEntries();
	int numChannels2 = 32;
	int numQDCbins = 100;
	int QDCmin = 0;
	int QDCmax = 200;

//zpos
	int numBars = 16;
	int numzPosbins = 100;
	double zPosmin = 0;
	double zPosmax = 400;
	double zPos;
	int zPosChL;
	int zPosChR;
	double chargeL = 0;
	double chargeR = 0;
			

	
//create histos
	TH1D *tdcALL = new TH1D("tdcALL","TDC All Channels",numTDCbins,TDCmin,TDCmax);
	TH1D *qdcALL = new TH1D("qdcALL","QDC All Channels",numQDCbins,QDCmin,QDCmax);
	TH1D *zPosALL = new TH1D("zPosALL","zPos All Bars",numzPosbins,zPosmin,zPosmax);


	for (i=0;i<numChannels;i++) 
	{
	//tdc histos
		std::string histObj = "tdc";
		std::string histTitle = "TDC Channel ";
		std::string channel;
		std::stringstream ch;		
		ch << i;
		channel = ch.str();
		histObj = histObj + channel;
		histTitle = histTitle + channel;
		const char *Obj = histObj.c_str();
		const char *Title = histTitle.c_str();
		histPtr = new TH1D(Obj,Title,numTDCbins,TDCmin,TDCmax);
	//qdc histos
		histObj = "qdc";
		histTitle = "QDC Channel ";
		histObj = histObj + channel;
		histTitle = histTitle + channel;
		Obj = histObj.c_str();
		Title = histTitle.c_str();
		histPtr = new TH1D(Obj,Title,numQDCbins,QDCmin,QDCmax);
	//zPos histos
		if (i<numBars)
		{
			histObj = "zPos";
			histTitle = "zPos Bar ";
			std::string barNum;
			stringstream bar;
			bar << (i+1);
			barNum = bar.str();
			histObj = histObj + barNum;
			histTitle = histTitle + barNum;
			Obj = histObj.c_str();
			Title = histTitle.c_str();
			histPtr = new TH1D(Obj,Title,numzPosbins,zPosmin,zPosmax);
		}		
				
	}

//fill histos	

//tdc
	for (i=0;i<numEntries;i++)
	{
		t->GetEntry(i);

		for (j=0;j<numChannels;j++)
		{
			std::string histObj = "tdc";
			std::string channel;
			stringstream ss;
			ss << j;
			channel = ss.str();
			histObj = histObj + channel;
			const char *Obj = histObj.c_str();
			fnew->GetObject(Obj,histPtr);
			histPtr->Fill(tdc->at(j));
			tdcALL->Fill(tdc->at(j));
	
		}
	}	
	

//qdc,zPos
	for (i=0;i<numEntries2;i++)
	{
		t2->GetEntry(i);

		for (j=0;j<numChannels2;j++)
		{
			std::string histObj = "qdc";
			std::string channel;
			stringstream ss;
			ss << j;
			channel = ss.str();
			histObj = histObj + channel;
			const char *Obj = histObj.c_str();
			fnew->GetObject(Obj,histPtr);
			histPtr->Fill(qdc->at(j));
			qdcALL->Fill(qdc->at(j));
			
		}
		for (j=0;j<numBars;j++)
		{
			std::string histObj = "zPos";
			stringstream bar;
			std::string numBar;
			bar << j+1;
			numBar = bar.str();
			histObj = histObj + numBar;
			const char *Obj = histObj.c_str();
			fnew->GetObject(Obj,histPtr);
			//get appropriate channels for the bar in question
			zPosChL = (j+1) + (j+1) - 1;
			zPosChR = zPosChL - 1;
			//get qdc vals for those channels
			chargeL = qdc->at(zPosChL);
			chargeR = qdc->at(zPosChR);
			//calculate zpos (the avg is just a test)
			if ((chargeL!=0) && (chargeR!=0))
			{
				zPos = (chargeL+chargeR)/2;
				histPtr->Fill(zPos);
				zPosALL->Fill(zPos);
			}			
						
		}

	}


//write
	fnew->Write();
//delete
//tdc
	for (i=0;i<numChannels;i++)
	{
		std::string histObj = "tdc";
		std::string channel;
		stringstream ss;
		ss << j;
		channel = ss.str();
		histObj = histObj + channel;
		const char *Obj = histObj.c_str();
		fnew->GetObject(Obj,histPtr);
		delete histPtr;
	}
//qdc
	for (i=0;i<numChannels2;i++)
	{
		std::string histObj = "qdc";
		std::string channel;
		stringstream ss;
		ss << j;
		channel = ss.str();
		histObj = histObj + channel;
		const char *Obj = histObj.c_str();
		fnew->GetObject(Obj,histPtr);
		delete histPtr;
	}
//zPos
	for (i=0;i<numBars;i++)
	{
		std::string histObj = "zPos";
		stringstream bar;
		std::string numBar;
		bar << (i+1);
		numBar = bar.str();
		histObj = histObj + numBar;
		const char *Obj = histObj.c_str();
		fnew->GetObject(Obj,histPtr);
		delete histPtr;
	}

	

//others
	delete tdcALL;
	delete qdcALL;
	delete zPosALL;


}
