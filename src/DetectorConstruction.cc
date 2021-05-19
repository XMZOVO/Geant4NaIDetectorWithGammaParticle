#include "DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4RotationMatrix.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4SubtractionSolid.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4Cons.hh"


DetectorConstruction::DetectorConstruction()
        :G4VUserDetectorConstruction(),
         fDet1(nullptr)
{
    SetDefaults();
    fMessenger = new DetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{
    delete fMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{
    //
    // define Elements
    //
//    G4Element* Mg  = new G4Element("Magnesium" ,"Mg" ,  12.,  24.31*g/mole);
    G4Element* O  = new G4Element("Oxygen"   ,"O" , 8,  16.00*g/mole);
    G4Element* elAl = new G4Element( "Aluminium","Al", 13,  27.00*g/mole);
    //
    // define materials
    //
//    G4Material* MgO =
//            new G4Material("MgO", density= 3.58*g/cm3, 2);
//    MgO->AddElement(Mg, 2);
//    MgO->AddElement(O, 1);

    G4Material* Al2O3 = new G4Material("Al2O3", 3.970*g/cm3, 2);
    Al2O3->AddElement(elAl, 2);
    Al2O3->AddElement(O, 3);

}

G4VPhysicalVolume* DetectorConstruction::Construct()
{

    // Get nist material manager
    DefineMaterials();
    auto nist = G4NistManager::Instance();

    // Build Materials
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR"); //世界材料空气
//	G4Material* Quartz_mat = nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE"); //二氧化硅材料
    G4Material* NaI_mat = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE"); //碘化钠材料
//	G4Material* Pb = nist->FindOrBuildMaterial("G4_Pb"); //铅屏蔽层材料
//	G4Material* MgO = nist->FindOrBuildMaterial("MgO"); //外壳材料
    G4Material* Al_mat = nist->FindOrBuildMaterial("G4_Al"); //外壳材料
    G4Material* Si_mat = nist->FindOrBuildMaterial("G4_Si");
    G4Material* Al2O3 = nist->FindOrBuildMaterial("Al2O3");

    G4bool checkOverlaps = true;

    //
    // World
    //
    G4double world_sizeXY = 100*cm;
    G4double world_sizeZ = 100*cm;

    auto solidWorld =
            new G4Box("World",									//its name
                      world_sizeXY, world_sizeXY, world_sizeZ);		//its size

    auto logicWorld =
            new G4LogicalVolume(solidWorld,						//its solid
                                world_mat,						//its material
                                "World");							//its name

    auto physWorld =
            new G4PVPlacement(0,								//no rotation
                              G4ThreeVector(),						//at (0,0,0)
                              logicWorld,							//its logical volume
                              "World",							//its name
                              0,								//its mother	volume.q
                              false,								//no boolean operation
                              0,								//copy number
                              checkOverlaps);						//overlaps checking

    //Cylinder NaI Detectors
    G4double innerRadius = 0.*cm;
    G4double outerRadius = 7.6*cm;
    G4double hz = 7.6*cm;
    G4double startAngle = 0.*deg;
    G4double spanningAngle = 360.*deg;
    G4Tubs* solidNaIDetector = new G4Tubs("NaIDetector", innerRadius, outerRadius,
                                          hz, startAngle, spanningAngle);

    auto logicShape1 =
            new G4LogicalVolume(solidNaIDetector,				//its solid
                                NaI_mat,						//its material
                                "NaIDetector");				//its name

    G4ThreeVector pos1 = G4ThreeVector(0*cm, 0*cm, 0*cm);
//	G4ThreeVector pos2 = G4ThreeVector(5.3*cm+fSpace, 0*cm, 0*cm);
    G4RotationMatrix* myRotation1 = new G4RotationMatrix(); //旋转向量
    myRotation1->rotateX(0.*deg);
    myRotation1->rotateY(90.*deg); //绕Y轴顺时针旋转90度
    myRotation1->rotateZ(0.*deg);

    fDet1 = new G4PVPlacement(myRotation1,					//rotation
                              pos1,						//at position
                              logicShape1,					//its logical volume
                              "NaIDetector1",				//its name
                              logicWorld,					//its mother volume
                              false,						//no boolean operation
                              0,							//copy number
                              checkOverlaps);				//overlaps checking

    //Lead Box for setup
//	auto leadOuter = new G4Box("leadOuter",36*cm,36*cm,36*cm); //铅外壳外高
//	auto leadInner = new G4Box("leadInner",30*cm,30*cm,30*cm); //铅外壳内高
//	auto solidLeadBox = new G4SubtractionSolid("LogicLeadBox",leadOuter,leadInner);//铅屏蔽层
//	auto logicLeadBox = new G4LogicalVolume(solidLeadBox,Pb,"logLeadBox");
//	new G4PVPlacement(0,G4ThreeVector(-27.3*cm,0*cm,0*cm),logicLeadBox,"LeadBox",logicWorld,false,0,checkOverlaps);
//
//	auto leadBoxVis = new G4VisAttributes(G4Colour(1.,1.,1.));
//	leadBoxVis->SetForceWireframe(true);
//	logicLeadBox->SetVisAttributes(leadBoxVis);

//    //Casing for detector
    auto casingBot1 = new G4Tubs("casingBot1",7.6*cm,8.0*cm,7.6*cm,0.*deg,360.*deg);
    auto casingBot2 = new G4Tubs("casingBot2",8.0*cm,8.3*cm,8.1*cm,0.*deg,360.*deg);
    auto casingEx1 = new G4Tubs("casingEx1",0*cm,8.0*cm,0.3*cm,0.*deg,360.*deg);
    auto casingEx2 = new G4Tubs("casingEx2",0*cm,8.3*cm,0.15*cm,0.*deg,360.*deg);
    auto casingEx3 = new G4Tubs("casingEx3",0*cm,8.0*cm,0.2*cm,0.*deg,360.*deg);

    auto logicCasingBot1 = new G4LogicalVolume(casingBot1,Al2O3,"logicCasingBot1");
    auto logicCasingBot2 = new G4LogicalVolume(casingBot2,Al_mat,"logicCasingBot2");
    auto logicCasingEx1 = new G4LogicalVolume(casingEx1,Al2O3,"logicCasingEx1");
    auto logicCasingEx2 = new G4LogicalVolume(casingEx2,Al_mat,"logicCasingEx2");
    auto logicCasingEx3 = new G4LogicalVolume(casingEx3,Si_mat,"logicCasingEx3");

    //内层外壳PV
    new G4PVPlacement(myRotation1,G4ThreeVector(0.*cm, 0.*cm, 0.*cm),logicCasingBot1,"casingBot1",logicWorld,false,0,checkOverlaps);
    new G4PVPlacement(myRotation1,G4ThreeVector(7.9*cm, 0.*cm, 0.*cm),logicCasingEx1,"casingEx1",logicWorld,false,0,checkOverlaps);
    //外层外壳PV
    new G4PVPlacement(myRotation1,G4ThreeVector(0.5*cm, 0.*cm, 0.*cm),logicCasingBot2,"casingBot2",logicWorld,false,0,checkOverlaps);
    new G4PVPlacement(myRotation1,G4ThreeVector(8.75*cm, 0.*cm, 0.*cm),logicCasingEx2,"casingEx2",logicWorld,false,0,checkOverlaps);
    new G4PVPlacement(myRotation1,G4ThreeVector(8.4*cm,0*cm,0*cm),logicCasingEx3,"casingEx3",logicWorld,false,0,checkOverlaps);
//
    //Quartz Piece
    auto FakePMT = new G4Tubs("FakePMT",0*cm,8.32*cm,3*cm,0.*deg,360.*deg);
    auto logicFakePMT = new G4LogicalVolume(FakePMT,Al_mat,"logicFakePMT");
    new G4PVPlacement(myRotation1,G4ThreeVector(-10.6*cm, 0.*cm, 0.*cm),logicFakePMT,"FakePMT",logicWorld,false,0,checkOverlaps);

    //
    return physWorld;
}

//Commands for modifying geometry
void DetectorConstruction::SetSpacing(G4double space) {
    fSpace=space;
    G4cout << "Spacing set to: " << space << G4endl;
    G4RunManager::GetRunManager()->ReinitializeGeometry();
}

void DetectorConstruction::SetDefaults() {
    //Resets to default values
    fSpace=4.7*cm;
}

void DetectorConstruction::SetMaterial(const G4String& materialChoice)
{
    // search the material by its name, or build it from nist data base
    G4Material* pttoMaterial =
            G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);

    if (pttoMaterial) {
        fMaterial = pttoMaterial;
        if(fBox) { fBox->GetLogicalVolume()->SetMaterial(fMaterial); }
        G4RunManager::GetRunManager()->PhysicsHasBeenModified();
    } else {
        G4cout << "\n--> warning from DetectorConstruction::SetMaterial : "
               << materialChoice << " not found" << G4endl;
    }
}

