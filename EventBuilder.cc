#include "EventBuilder.hh"
#include <cmath>

EventBuilder::EventBuilder(){
<<<<<<< HEAD
	fNumBars = 24;
=======
	fNumBars = 16;
>>>>>>> bf4189795b0f02b8b7647af1b04817fbd11eceb5
}
EventBuilder::~EventBuilder(){}


<<<<<<< HEAD
double EventBuilder::GetLeftCharge(std::vector<UInt_t> *qdc, int bar){

	int channel = 2*(bar%8);
=======
double EventBuilder::GetLeftCharge(std::vector<UInt_t> *qdc, int barNum){

	int channel = 2*barNum - 2;
>>>>>>> bf4189795b0f02b8b7647af1b04817fbd11eceb5
	double q = (double)qdc->at(channel);

	return q;
}

<<<<<<< HEAD
double EventBuilder::GetRightCharge(std::vector<UInt_t> *qdc, int bar){

	int channel = 2*(bar%8)+1;
=======
double EventBuilder::GetRightCharge(std::vector<UInt_t> *qdc, int barNum){

	int channel = 2*barNum - 1;
>>>>>>> bf4189795b0f02b8b7647af1b04817fbd11eceb5
	double q = (double)qdc->at(channel);	

	return q;
}

<<<<<<< HEAD
=======
double EventBuilder::GetChargeInBar(std::vector<UInt_t> *qdc,int barNum){

	double q = GetLeftCharge(qdc,barNum) + GetRightCharge(qdc,barNum);
	
	return q;
}
>>>>>>> bf4189795b0f02b8b7647af1b04817fbd11eceb5

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
<<<<<<< HEAD
	for (i=0;i<16;i++)
	{
		if ( qdc->at(i) > threshold && qdc->at(i+1) > threshold ) {barCount++;}
=======
	for (i=0;i<fNumBars;i++)
	{
		if ( (qdc->at(GetLeftChannel(i+1)) > threshold) && (qdc->at(GetRightChannel(i+1)) > threshold) ) {barCount++;}
>>>>>>> bf4189795b0f02b8b7647af1b04817fbd11eceb5
	}
	return barCount;
}

<<<<<<< HEAD


=======
>>>>>>> bf4189795b0f02b8b7647af1b04817fbd11eceb5
double EventBuilder::ZRecon(std::vector<UInt_t> *qdc,double invattcoeff,int barNum){

	double qL = GetLeftCharge(qdc,barNum);
	double qR = GetRightCharge(qdc,barNum);
	double zPos = invattcoeff*log(qL/qR);
	return zPos;
}


<<<<<<< HEAD
bool EventBuilder::WasOppBarEvent(int OppositeBar[24],int wasHit[24]){
=======
bool EventBuilder::WasOppBarEvent(std::vector<UInt_t>*,int OppositeBar[24],int wasHit[24]){
>>>>>>> bf4189795b0f02b8b7647af1b04817fbd11eceb5
	
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

<<<<<<< HEAD
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

=======
>>>>>>> bf4189795b0f02b8b7647af1b04817fbd11eceb5


















