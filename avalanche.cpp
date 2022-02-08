#include <iostream>
#include <cmath> 
#include <cstring>
#include <fstream>
#include <TCanvas.h>
#include <TApplication.h>
#include <TFile.h>
	
#include "Garfield/ComponentAnalyticField.hh"
#include "Garfield/ViewField.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/AvalancheMicroscopic.hh"
#include "Garfield/AvalancheMC.hh"
#include "Garfield/Random.hh"
#include "Garfield/Plotting.hh"
#include "Garfield/ViewMedium.hh"
#include "Garfield/ViewSignal.hh"
#include "Garfield/ViewCell.hh"
#include "Garfield/ViewDrift.hh"

	using namespace Garfield;
	using namespace std;
	
int main(int argc, char * argv[]){
	
	TApplication app("app", &argc, argv);
	
	const double inR = 0.008 ;// cm
	const double outR = 3.35 ;// cm 
	const double wireV = 700 ;// V (anodo)
	const double tubeV = 0 ;//   V (catodo)
	
	MediumMagboltz* gas = new MediumMagboltz();
	gas->SetComposition("ar",90.,"ch4",10.);
	gas->SetTemperature(293.15);
	gas->SetPressure(760.);
	const std::string path = getenv("GARFIELD_HOME");
	gas->LoadIonMobility(path + "/Data/IonMobility_Ar+_Ar.txt");
	
	ViewMedium* vM = new ViewMedium();
	vM->SetMedium(gas);
	vM->EnableAutoRangeX();
	vM->PlotElectronVelocity('e',false);
	
	app.Run(kTRUE);
	return 0;
	
}