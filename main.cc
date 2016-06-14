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







	HistoMaker histomaker;
	EnergyCal energycalibration;
	PositionCal positioncalibration;

	histomaker.MakeHistos(tTDC,tQDC,fout);
	
	//energycalibration.Calibrate(tQDC,fout);
	//positioncalibration.Calibrate(tQDC,fout);

	


	fout->Write();
	histomaker.DeleteHistos(fout);



	
return 0;

}
