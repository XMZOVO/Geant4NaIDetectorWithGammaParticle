#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4GeneralParticleSource;
class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
	public:
		PrimaryGeneratorAction();	
		virtual ~PrimaryGeneratorAction();

		virtual void GeneratePrimaries(G4Event* event);

    private:
    G4GeneralParticleSource*  fParticleGun; // pointer a to G4 gun class
};
