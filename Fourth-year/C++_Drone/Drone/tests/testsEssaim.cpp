
#include "testsEssaim.h"
#include "../include/VecteurR3.h"
#include "../include/Cubique.h"

void testsEssaim::setUp(void){
}

void testsEssaim::tearDown(){

}

void testsEssaim::testAjouterDrone() {
  Essaim essaim = Essaim();
  Drone d0 = Drone(VecteurR3());
  Drone d1 = Drone(VecteurR3(1,0,0));
  essaim.ajouterDrone(d0);
  essaim.ajouterDrone(d1);
  CPPUNIT_ASSERT(essaim.getVDrones().size()==2
    && essaim.getVDrones()[0]->getPosition()==d0.getPosition()
    && essaim.getVDrones()[1]->getPosition()==d1.getPosition());
}

void testsEssaim::testRetirerColis() {
  Essaim essaim = Essaim();
  Drone d0 = Drone(VecteurR3());
  Drone d1 = Drone(VecteurR3(1,0,0));
  essaim.ajouterDrone(d0);
  essaim.ajouterDrone(d1);
  VecteurR3 retrait = VecteurR3(.8,0,0); // plus proche de d1
  VecteurR3 depot = VecteurR3(.8,0,1); // wherever
  // Appel de la fonction à vérifier
  essaim.retirerColis(retrait, depot);

  std::queue<VecteurR3> vObjD1 = essaim.getVDrones()[1]->getVObjectifs();
  bool resD1 = (vObjD1.size() == 2);
  resD1 &= (vObjD1.front()==retrait);
  resD1 &= (vObjD1.back()==depot);
  CPPUNIT_ASSERT(!essaim.getVDrones()[0]->aObjectif() && resD1);
}

void testsEssaim::testAffectationDronePos() {
  // non implémenté
}
