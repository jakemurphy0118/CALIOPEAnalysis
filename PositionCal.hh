#ifndef POSITIONCAL_H
#define POSITIONCAL_H

#include <TTree.h>
#include <TFile.h>
#include <string>
#include <sstream>
#include <TH1D.h>

class PositionCal{

public: 
	PositionCal();
	~PositionCal();
	std::vector<double> * Calibrate(TTree*,TFile*);
//returns array of left-pmt channel number then right-pmt channel number
	int * GetChannelsForBar(int bar){
		int ch[2];
		ch[0] = bar + bar - 2;
		ch[1] = ch[0] + 1;
		return ch;
	}


private:

	int fNumBars;
	int fNumChannels;

};


#endif

