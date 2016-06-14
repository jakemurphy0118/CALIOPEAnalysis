#include "PositionCal.hh"
#include <cmath>

PositionCal::PositionCal(){}
PositionCal::~PositionCal(){}

std::vector<double> * PositionCal::Calibrate(TTree* t,TFile* f){

//branch addressing
	Int_t runNumber2;
	UInt_t crate2;
	UInt_t card2;
	UInt_t eventCount2;
	UInt_t nValues2;
	std::vector<UInt_t> *qdc = 0;
	std::vector<UInt_t> *qdcUnder = 0;
	std::vector<UInt_t> *qdcOverflow = 0;

	t->SetBranchAddress("runNumber",&runNumber2);
	t->SetBranchAddress("crate",&crate2);
	t->SetBranchAddress("card",&card2);
	t->SetBranchAddress("eventCount",&eventCount2);
	t->SetBranchAddress("nValues",&nValues2);
	t->SetBranchAddress("qdc",&qdc);
	t->SetBranchAddress("isUnderThresh",&qdcUnder);
	t->SetBranchAddress("isOverflow",&qdcOverflow);

//fill array of log(q1/q2) for each bar
//q1 is from left channel, q2 from right channel
//2-D array: logratios[bar-1][channel]


	long numEntries = t->GetEntries();
	double logratios[16][numEntries];
	double q1overq2;
	int i;
	int j;

	for (i=0;i<numEntries;i++)
	{
		t->GetEntry(i);
		
		for (j=0;j<16;j++)
		{

			int *ch = GetChannelsForBar(j+1);

			if ((qdc->at(ch[0]) != 0) && (qdc->at(ch[1]) != 0))
			{
				q1overq2 = (qdc->at(ch[0]))/(qdc->at(ch[1]));
				logratios[j][i] = q1overq2;
			}		
			else logratios[j][i] = 0;
		}
		
	}


	std::vector<double> *invattcoeff = 0;
	return invattcoeff;


}








