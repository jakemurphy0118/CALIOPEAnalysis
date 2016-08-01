#ifndef HISTOMAKER_H
#define HISTOMAKER_H

#include <TTree.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <iostream>
#include <string>

class HistoMaker
{

public:
	HistoMaker();
	~HistoMaker();

	void MakeHistos(TTree*,TTree*,TTree*,TTree*,TTree*,TTree*,TFile*);
	void DeleteHistos(TFile*);
	void SetInvAttCoeff();
	void SetOppositeBars();
	void FillTH1D(TFile*,std::string,double);
	void FillTH2D(TFile*,std::string,double,double);

private:
	int fNumBars;
	int fNumQDCbins;
	int fQDCmax;
	int fQDCmin;
	int fNumTDCbins;
	int fTDCmax;
	int fTDCmin;
	int fNumZPosbins;
	int fZPosmax;
	int fZPosmin;


	TH1D *fHistPtr;
	std::string histObj;
	std::string histTitle;
//disable trees not used
	bool qdcTree1, qdcTree2, qdcTree3;
	bool tdcTree1, tdcTree2, tdcTree3;
//inverse attenuation coefficients
	double InvAttCoeff[24];
//input: bar#-1, output: opposite bar#
	int OppositeBar[24];

};

#endif

