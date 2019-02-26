
#include "../tests/testsDrone.h"

void testsDrone::testAjouterObjectif() {
    Drone d = Drone(VecteurR3());
    VecteurR3 posObj = VecteurR3(1,0,0);
    d.ajouterObjectif(posObj);
    CPPUNIT_ASSERT(d.getVObjectifs().size() == 1 && d.getVObjectifs().front() == posObj);
}

void testsDrone::testLivrerColis() {
  Drone d = Drone(VecteurR3());
  VecteurR3 posRetrait = VecteurR3(0,1,0);
  VecteurR3 posDepot = VecteurR3(0.5,0.25,0);
  d.livrerColis(posRetrait, posDepot);
  CPPUNIT_ASSERT(d.getVObjectifs().size() == 2 &&
                 d.getVObjectifs().front() == posRetrait &&
                 d.getVObjectifs().back() == posDepot);
}

void testsDrone::testAtteintObjectif() {
  Drone d = Drone(VecteurR3());
  d.ajouterObjectif(VecteurR3());
  CPPUNIT_ASSERT(d.atteintObjectif() && !d.aObjectif());
}
void testsDrone::testplusplus(){
  Environnement env = Environnement(2.);
  // Obstacle qui obstruit la direction X
  env.ajouterObstacle(Obstacle(VecteurR3(0.5,-1,-1),0.5,2,2));
  vector<Capteur> vCapteur;
  vCapteur.push_back(Capteur(1.,VecteurR3(1,0,0),&env));
  Drone d = Drone(0.1,VecteurR3(),vCapteur,env.getGravite());
  d++;
  bool testCapteur = d.getVCapteurs()[0].detecteQQch();
  //Test si le drone contre la gravité (n'a pas d'objectif)
  VecteurR3 vAcc = VecteurR3(1,1,1);
  d.setAcceleration(vAcc);
  d++;
  bool testContreGravite = (d.getAcceleration()==env.getGravite()*-1);

  //Maintenant s'il a un objectif il devrait bouger
  d.ajouterObjectif(VecteurR3(1,1,1));
  d++;
  bool testObj = !((d.getAcceleration()==VecteurR3()) ||
                   (d.getAcceleration()==env.getGravite()*-1));

  // Teste si le drone ne fait bien aucune action s'il n'est plus fonctionnel
  d.neFonctionnePlus();
  d++;
  bool testNonFonctionnel = (d.getAcceleration()==VecteurR3());

  CPPUNIT_ASSERT(testCapteur && testContreGravite && testObj && testNonFonctionnel);
}

void testsDrone::tearDown(){
}
void testsDrone::setUp(){}
