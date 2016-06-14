#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "EnergyCal.hh"


int main(int argc, char** argv){

//deal with input file

	if (argc != 2){ std::cout << "Supply root file" << std::endl;}
	std::string inputFile = argv[1];
	
	TFile fin(inputFile.c_str());

//get trees from root file

	TTree *tTDC;
	TTree *tQDC; 
	fin.GetObject("treeName",tTDC);
	fin.GetObject("treeName_2",tQDC);

//deal with output file

	std::string outputFile;
	std::string outputFile1;
	
	if( inputFile.find(".") < inputFile.length() ) {
        	if( inputFile.substr(inputFile.find_last_of(".")) == ".root" ) {
            		outputFile = inputFile.substr(0, inputFile.find_last_of(".") );
			outputFile1 = outputFile + "Histos.root";
        	}
    	}
	
	const char *histos = outputFile1.c_str();
	TFile* fout = new TFile(histos,"recreate");

//energy calibration, return scaling factors for each bar
	
	EnergyCal energycalibration;
	std::vector<double> *energyScalingFactors = 0;
	energyScalingFactors = energycalibration.Calibrate(tQDC,fout);

	fout->Write();
	energycalibration.DeleteBarHistos(fout);
	
//for run with the collimator, get 1/mu for each bar

	//PositionCal positioncalibration;
	//std::vector<double> *invattcoeff = 0;
	
	//invattcoeff = positioncalibration.Calibrate(tQDC,fout);

	
return 0;

}
