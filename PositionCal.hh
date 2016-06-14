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
	void Calibrate(TTree*,TFile*);


private:

	int fNumBars;
	int fNumChannels;

};


#endif

