#include "EventAction.hh"
#include "RunAction.hh"
#include "Analysis.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include <iomanip>
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction()
	:G4UserEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* )
{

	// Set beginning deposition as 0
	fEnergyDet1 = 0.;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* evt)
{
	auto analysisManager = G4AnalysisManager::Instance();

    FILE *opf1 = fopen("out.dat","a");
    if (fEnergyDet1>0. ) {
        fprintf(opf1,"%d  %e \n", evt->GetEventID()+1, fEnergyDet1/MeV);
    }
    fclose(opf1);
	analysisManager->FillH1(1, fEnergyDet1);
//    analysisManager->FillNtupleDColumn(0,0, fEnergyDet1);
//    analysisManager->AddNtupleRow();

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
