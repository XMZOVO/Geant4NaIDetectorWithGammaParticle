#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "Analysis.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
	:G4UserRunAction()
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetVerboseLevel(1);
    analysisManager->SetFirstHistoId(1);

	// Creating histograms
	//
	analysisManager->CreateH1("EDet1","Edep in Det1", 4096, 0.0, 1.5*MeV);

//	// Creating ntuple
	//
//	analysisManager->CreateNtuple("Cs137", "Edep");
//	analysisManager->CreateNtupleDColumn(0,"EDet1");
//	analysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
	delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* )
{

	auto analysisManager = G4AnalysisManager::Instance();

	// Open an output file
	//
    G4String fileName = "/Users/roy/Documents/Geant4EX/lrd_v1/build/EuCs-35-20000000.root";
	analysisManager->OpenFile(fileName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* )
{

	// Print histogram statistics
	//
    if (isMaster) G4Random::showEngineStatus();

    //save histograms
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
