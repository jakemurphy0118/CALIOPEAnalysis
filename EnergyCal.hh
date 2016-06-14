#ifndef ENERGYCAL_H
#define ENERGYCAL_H

#include <TTree.h>
#include <TFile.h>
#include <TH1D.h>
#include <iostream>
#include <string>

class EnergyCal
{

public:
	EnergyCal();
	~EnergyCal();
	void Calibrate(TTree*,TFile*);
	void MakeBarHistos(TTree*,TFile*);
	void DeleteBarHistos(TFile*);
//returns array of left-pmt channel number then right-pmt channel number
	int * GetChannelsForBar(int bar){
		int ch[2];
		ch[0] = bar + bar - 2;
		ch[1] = ch[0] + 1;
		return ch;
	}
private:

	int fNumBars;
	int fNumQDCbins;
	int fQDCmax;
	int fQDCmin;
	TH1D *fHistPtr;
	std::string histObj;
	std::string histTitle;
	
};

#endif
