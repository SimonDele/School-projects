
#include "../include/Capteur.h"
#include "../include/Environnement.h"
#include <cmath>
#include <stdexcept>
#include "testsCapteur.h"

void testsCapteur::testUpdateDistanceDetectee(void)
{
    /*
  Capteur capteur = new Capteur(50,50,VecteurR3(),new Environnement());
  vector<VecteurR3> posObstacle(4);

  /** Je crée un obstacle carré je vais placer dans l'environnement*/
  /*
  posObstacle[0] = new VecteurR3(2,2,2);
  posObstacle[1] = new VecteurR3(3,2,2);
  posObstacle[2] = new VecteurR3(2,3,2);
  posObstacle[3] =new VecteurR3(2,2,3);

/** J'ajoute l'obstacle à l'environnement*/
  //env.ajouterObstacle(new Obstacle(posObstacle));

  /** Je lance la detection*/
  //capteur.updateDistanceDetectee();
/** Je vérifie que mon capteur detecte bien l'obstacle*/
  //CCPUNIT_ASSERT(capteur.distanceDectectee == 4);

}
