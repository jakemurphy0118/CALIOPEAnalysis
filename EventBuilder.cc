#include "EventBuilder.hh"
#include <cmath>

EventBuilder::EventBuilder(){
	fNumBars = 24;
}
EventBuilder::~EventBuilder(){}


double EventBuilder::GetLeftCharge(std::vector<UInt_t> *qdc, int bar){

	int channel = 2*(bar%8);
	double q = (double)qdc->at(channel);

	return q;
}

double EventBuilder::GetRightCharge(std::vector<UInt_t> *qdc, int bar){

	int channel = 2*(bar%8)+1;
	double q = (double)qdc->at(channel);	

	return q;
}


void EventBuilder::WhichBars(std::vector<UInt_t> *qdc,int wasHit[24], UInt_t threshold){

	int i;
	for (i=0;i<fNumBars;i++)
	{
		if ( (qdc->at(GetLeftChannel(i+1)) > threshold) && (qdc->at(GetRightChannel(i+1)) > threshold) ) {wasHit[i] = 1;}
		else {wasHit[i] = 0;}
	}
}

int EventBuilder::NumOfHitBars(std::vector<UInt_t> *qdc,UInt_t threshold){
	
	int i;
	int barCount = 0;
	for (i=0;i<16;i++)
	{
		if ( qdc->at(i) > threshold && qdc->at(i+1) > threshold ) {barCount++;}
	}
	return barCount;
}



double EventBuilder::ZRecon(std::vector<UInt_t> *qdc,double invattcoeff,int barNum){

	double qL = GetLeftCharge(qdc,barNum);
	double qR = GetRightCharge(qdc,barNum);
	double zPos = invattcoeff*log(qL/qR);
	return zPos;
}


bool EventBuilder::WasOppBarEvent(int OppositeBar[24],int wasHit[24]){
	
	bool touch[24] = {false};
	int i;
	int oppbarnum;
	bool any = false;
	for (i=0;i<24;i++)
	{
		oppbarnum = OppositeBar[i];
		if ( (wasHit[i]==1) && (wasHit[oppbarnum-1]==1) ) 
		{
			if (touch[i] == true) {break;}
			any = true;
			touch[oppbarnum-1] = true;
		}
	}
	
	return any;

}

double EventBuilder::GetLeftTDCVal(std::vector<UInt_t> *tdc, int bar){
	
	int channel = 2*(bar%8);
	double t = (double)tdc->at(channel);
	return t;
}

double EventBuilder::GetRightTDCVal(std::vector<UInt_t> *tdc, int bar){
	
	int channel = 2*(bar%8)+1;
	double t = (double)tdc->at(channel);
	return t;
}



















