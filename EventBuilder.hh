#ifndef EVENTBUILDER_H
#define EVENTBUILDER_H

#include <TH1D.h>
#include <TTree.h>
#include <TFile.h>
#include <vector>


class EventBuilder
{

public: 
	EventBuilder();
	~EventBuilder();
	
	double GetLeftCharge(std::vector<UInt_t>*,int barNum);
	double GetRightCharge(std::vector<UInt_t>*,int barNum);
	double GetChargeInBar(std::vector<UInt_t>*,int barNum);
	void WhichBars(std::vector<UInt_t>*,int wasHit[24],UInt_t threshold);
	int NumOfHitBars(std::vector<UInt_t>*,UInt_t threshold);
	double ZRecon(std::vector<UInt_t>*,double invattcoeff,int barNum);
	int GetLeftChannel(int barNum){return 2*barNum - 2;}
	int GetRightChannel(int barNum){return 2*barNum - 1;}
	bool WasOppBarEvent(std::vector<UInt_t>*,int OppositeBar[24],int wasHit[24]);
	
	
	
private:

	int fNumBars;



};


#endif
