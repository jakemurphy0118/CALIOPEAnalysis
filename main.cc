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
#include "PositionCal.hh"
#include "HistoMaker.hh"


int main(int argc, char** argv){

//deal with input file

	if (argc != 2){ std::cout << "Supply root file" << std::endl;}
	std::string inputFile = argv[1];
	
	TFile fin(inputFile.c_str());

//get trees from root file

	TTree* tTDC1;
	TTree* tTDC2;
	TTree* tTDC3;
	TTree* tQDC1;
	TTree* tQDC2;
	TTree* tQDC3; 
	fin.GetObject("treeName",tTDC1);
	fin.GetObject("treeName_2",tQDC1);

//deal with output file

	std::string outputFile;
	if( inputFile.find(".") < inputFile.length() ) {
        	if( inputFile.substr(inputFile.find_last_of(".")) == ".root" ) {
            		outputFile = inputFile.substr(0, inputFile.find_last_of(".") );
			outputFile = outputFile + "Histos.root";
        	}
    	}
	
	const char *histos = outputFile.c_str();
	TFile* fout = new TFile(histos,"recreate");







	HistoMaker histomaker;
	//EnergyCal energycalibration;
	//PositionCal positioncalibration;

	histomaker.MakeHistos(tTDC1,tTDC2,tTDC3,tQDC1,tQDC2,tQDC3,fout);
	
	//energycalibration.Calibrate(tQDC,fout);
	//positioncalibration.Calibrate(tQDC,fout);

	


	fout->Write();
	histomaker.DeleteHistos(fout);



	
return 0;

}
