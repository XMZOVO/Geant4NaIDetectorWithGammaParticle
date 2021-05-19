#include "G4UserEventAction.hh"
#include "globals.hh"

/// Event action class
///

class EventAction : public G4UserEventAction
{
public:
    EventAction();
    virtual ~EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep(G4double de); //Declares function to add energy


private:
    G4double fEnergyDet1; //records energy deposition
};

inline void EventAction::AddEdep(G4double de) {
    fEnergyDet1 += de; //records change in energy in fdet1
}


