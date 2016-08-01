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
<<<<<<< HEAD
=======
	double GetChargeInBar(std::vector<UInt_t>*,int barNum);
>>>>>>> bf4189795b0f02b8b7647af1b04817fbd11eceb5
	void WhichBars(std::vector<UInt_t>*,int wasHit[24],UInt_t threshold);
	int NumOfHitBars(std::vector<UInt_t>*,UInt_t threshold);
	double ZRecon(std::vector<UInt_t>*,double invattcoeff,int barNum);
	int GetLeftChannel(int barNum){return 2*barNum - 2;}
	int GetRightChannel(int barNum){return 2*barNum - 1;}
<<<<<<< HEAD
	bool WasOppBarEvent(int OppositeBar[24],int wasHit[24]);
	double GetLeftTDCVal(std::vector<UInt_t>*,int);
	double GetRightTDCVal(std::vector<UInt_t>*,int);
=======
	bool WasOppBarEvent(std::vector<UInt_t>*,int OppositeBar[24],int wasHit[24]);
>>>>>>> bf4189795b0f02b8b7647af1b04817fbd11eceb5
	
	
	
private:

	int fNumBars;



};


#endif
