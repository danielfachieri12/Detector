#include <iostream>
#include <fstream>
#include <cstdlib>

#include <TCanvas.h>
#include <TROOT.h>
#include <TApplication.h>

#include "Garfield/ViewCell.hh"
#include "Garfield/ViewDrift.hh"
#include "Garfield/ViewSignal.hh"
#include "Garfield/ViewMedium.hh"

#include "Garfield/ComponentAnalyticField.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/TrackHeed.hh"
#include "Garfield/ViewField.hh"
#include "Garfield/AvalancheMicroscopic.hh"
#include "Garfield/DriftLineRKF.hh"

using namespace Garfield;
using namespace std;

int main(int argc, char * argv[]) {

	TApplication app("app", &argc, argv);
	
	const double inR = 0.034 ;// cm
	const double outR = 3.35 ;// cm 
	const double wireV = 700 ;// V (anodo)
	const double tubeV = 0 ;//   V (catodo)
	
	MediumMagboltz* gas = new MediumMagboltz();     
	gas->SetComposition("ar",90.0,"ch4",10.0);      
	gas->SetTemperature(273.15);                    
	gas->SetPressure(760.0);
	gas->SetMaxElectronEnergy(200.0);
	const std::string path = getenv("GARFIELD_HOME");
	gas->LoadIonMobility(path + "/Data/IonMobility_Ar+_Ar.txt");
	
	ComponentAnalyticField* cmp = new ComponentAnalyticField(); //mesmas dimensões da latinha
	cmp->SetMedium(gas);
	cmp->AddWire(0,0,inR,wireV,"anodo");
	cmp->AddTube(outR,tubeV,0,"catodo");
	cmp->AddReadout("anodo");
	
	Sensor* sensor = new Sensor();
	sensor->AddComponent(cmp);
	sensor->AddElectrode(cmp, "anodo");
	sensor->SetTimeWindow(-0.25,0.5,500);

	int nel;

	TrackHeed* track = new TrackHeed();
	track->SetSensor(sensor);
	track->TransportPhoton(inR + 0.2, -2,0,0,7e3,0,1,0, nel);
	
	
	DriftLineRKF* drift = new DriftLineRKF();
	drift->SetSensor(sensor);
	drfit->EnableSignalCalculation();
	
	double xc=0.,yc=0.,zc=0.,tc=0.,ec=0.,extra=0;
	int nc=0;
	
	TCanvas* cd = new TCanvas("cd","DriftLines",600,600);
	ViewCell* cellview = new ViewCell();
	ViewDrift* vdrift = new ViewDrift();
	cellview->SetCanvas(cd);
	cellview->SetComponent(cmp);
	vdrift->SetCanvas(cd);
	drift->EnablePlotting();
	track->Enable
	
	while (track->GetCluster(xc,yc,zc,tc,nc,ec,extra)){
		for (int k =0; k <nc; k++){
			double xe=0.,ye=0.,ze=0.,te=0.,ee=0.;
			double dx=0.,dy=0.,dz=0.;
			track->GetElectron(k,xe,ye,ze,te,ee,dx,dy,dz);
			drift->DriftElectron(xe,ye,ze,te);
		}
	}
	
	cd->Clear();
	cellview->Plot2d();
	vdrift->Plot(true,false);
	
	TCanvas* cs = new TCanvas("cs","Signal",600,600);
	ViewSignal* signal = new ViewSignal();
	signal->SetCanvas(cs);
	signal->SetSensor(sensor);
	signal->PlotSignal("anodo");
	
	
	app.Run(kTRUE);
	return 0;
	
	
}