#include <iostream>
#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <string>
#include <sstream>


int main(int argc, char **argv){

	if (argc != 2){ std::cout << "Supply root file" << std::endl;}
	std::string file = argv[1];
	TFile f(file.c_str());

	int numch = 32;
	int i;
	TH1D *histptr;
	TCanvas c1;
	std::string pdf = ".pdf";
	


	for (i=0;i<numch;i++)
	{
		std::stringstream sch;
		std::stringstream sbar;
		sch << i;
		sbar << i+1;
		std::string histo = "qdc" + sch.str();
		f.GetObject(histo.c_str(),histptr);
		histptr->Draw();
		gPad->SetLogy();
		histo = histo + pdf;
		c1.SaveAs(histo.c_str());

		histo = "tdc" + sch.str();
		f.GetObject(histo.c_str(),histptr);
		histptr->Draw();
		gPad->SetLogy();
		histo = histo + pdf;
		c1.SaveAs(histo.c_str());
		
	}

	//misc
	f.GetObject("qdcALL",histptr);
	histptr->Draw();
	gPad->SetLogy();
	c1.SaveAs("qdcALL.pdf");
	f.GetObject("tdcALL",histptr);
	gPad->SetLogy();
	histptr->Draw();
	c1.SaveAs("tdcALL.pdf");

return 0;

}
