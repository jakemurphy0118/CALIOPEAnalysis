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

private:

	TH1D *fHistPtr;

	
};

#endif
