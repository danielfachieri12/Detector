#include <iostream>
#include <cmath> 
#include <cstring>
#include <fstream>
#include <TCanvas.h>
#include <TApplication.h>

#include "Garfield/MediumMagboltz.hh"
#include "Garfield/ComponentElmer.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/ViewField.hh"
#include "Garfield/Plotting.hh"
#include "Garfield/ViewFEMesh.hh"
#include "Garfield/ViewSignal.hh"
#include "Garfield/GarfieldConstants.hh"
#include "Garfield/Random.hh"
#include "Garfield/AvalancheMicroscopic.hh"


using namespace Garfield;
using namespace std;

int main(int argc, char * argv[]) {

    	TApplication app("app", &argc, argv);
	char* electronpos = new char[150];
	char* ionpos = new char[150];

	
	MediumMagboltz* gas = new MediumMagboltz();
    	gas->SetTemperature(293.15);                  // definindo temperatura em kelvin
    	gas->SetPressure(740.);                       // definindo a pressão em torr
    	gas->EnableDrift();                           // permitindo deriva no meio
    	gas->SetComposition("ar", 70., "co2", 30.);   // definindo mistura de argonio com co2 em 70:30
	//gas->SetMaxElectronEnergy(200.);
	gas->EnableDebugging();
	gas->Initialise();
	gas->DisableDebugging();
	const std::string path = getenv("GARFIELD_HOME");
	gas->LoadIonMobility(path + "/Data/IonMobility_Ar+_Ar.txt");
	gas->EnablePenningTransfer(0.45,0.0,"ar");
	
	ComponentElmer * elm = new ComponentElmer("mesh.header","mesh.elements","mesh.nodes","dielectrics.dat","potfield.result" ,"mm");
	elm->SetMedium(0,gas);
	//elm->EnablePeriodicityX();
	//elm->EnablePeriodicityZ();
	//elm->EnableMirrorPeriodicityz();
	elm->SetWeightingField("wtfield.result","wtfield");
	elm->PrintMaterials();
	elm->PrintRange();
	
	Sensor* sensor = new Sensor();
	sensor->AddComponent(elm);
	sensor->SetArea(-33.5,-33.5,0,33.5,33.5,168);
	

	// começar a deriva dos eletrons
	
	AvalancheMicroscopic* aval = new AvalancheMicroscopic();
	aval->SetSensor(sensor);
	aval->SetCollisionSteps(100);
	aval->EnableSignalCalculation();
	
	// começar a deriva dos ions
	
	AvalancheMC* drift = new AvalancheMC();
	drift->SetSensor(sensor);
	drift->SetDistanceSteps(5.e-4);
	drift->EnableSignalCalculation();
	
	// Variáveis para guardar a posições(finais e iniciais) dos eletrons e dos ions nos efeitos de avalanche
	
	double xe1, ye1, ze1, te1, ee1;
	double xe2, ye2, ze2, te2, ee2;
	int e_status;
	
	double xi1, yi1, zi1, ti1;
	double xi2, yi2, zi2, ti2;
	int i_status;
	
	// posição inicial dos eletrons que vão iniciar a avalanche durante a simulação
	
	double xi = 0;
	double yi = 15;
	double zi = 84;
	
	int ava = 5; // numero de avalanches que vao ocorrer
	
	for (int i = 0; i < ava ; i++){
	std::cout<<"Calculando avalanche: "<< i << endl;	
	std::fstream fpositionion;
	std::fstream fpositionelectron;
	
	//Inicia a avalanche dos eletrons
			
	aval->AvalancheElectron(xi, yi, zi, 0, 0, 0., 0., 0.);

	
	const int nElec = aval->GetNumberOfElectronEndpoints();  //Número de elétrons gerados na avalanche

		for (int l=0; l<nElec; l++) //Loop em nElec para recuperar a posição dos elétrons e fazer a deriva dos ions
			{	
			aval->GetElectronEndpoint(l, xe1, ye1, ze1, te1, ee1, xe2, ye2, ze2, te2, ee2, e_status);	//Guarda a posição do eletron
			drift->DriftIon(xe1, ye1, ze1, te1);		//Calcula a deriva do ion na posição onde um eletron foi gerado
			drift->GetIonEndpoint(0, xi1, yi1, zi1, ti1, xi2, yi2, zi2, ti2, i_status); // Guarda a posição do ion
				

			fpositionelectron.open(electronpos, std::fstream::out | std::fstream::app); //Abre o arquivo txt e printa as posições dos eletrons
			fpositionelectron << l << ' ' << xe1 << ' ' << ye1 << ' ' << ze1 << ' ' << te1 << ' ' << ee1 << ' ' << xe2 << ' ' << ye2 << ' ' << ze2 << ' ' << te2 << ' ' << ee2 << ' ' << e_status << std::endl; 
			fpositionelectron.close();  //fecha o txt
				
				
			fpositionion.open(ionpos, std::fstream::out | std::fstream::app); //Abre o arquivo txt e printa as posições dos íons
			fpositionion << l << ' ' << xi1 << ' ' << yi1 << ' ' << zi1 << ' ' << ti1 << ' ' << 0 << ' ' << xi2 << ' ' << yi2 << ' ' << zi2 << ' ' << ti2 << ' ' << 0 << ' ' << i_status << std::endl; //
			fpositionion.close();  //Fecha o txt
			
			}
			
		}
	
	ViewDrift* vD = new ViewDrift();
	vD->SetArea(-1,-1,167,1,1,169);
	aval->EnablePlotting(vD);
	drift->EnablePlotting(vD);
	
	return 0;
	}
