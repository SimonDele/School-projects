#include "../include/Environnement.h"
#include "../include/Obstacle.h"
#include "../include/Drone.h"
#include "../include/Essaim.h"
#include <iostream>
#include<vector>
#include <cmath>
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MAX3(a,b,c) (((MAX(a,b))>(c))?(MAX(a,b)):(c))
#define sgn(x) ((x >= 0) ? 1 : -1)

/**
* @authors Timothé, Simon, Théau
*/
Environnement::Environnement(const float tailleCote) {
  cote = tailleCote;
  origineEnv = VecteurR3(-cote/2.,-cote/2.,-cote/2.);
  gravite = VecteurR3(0,0,-3.5); // valeur du vect acc de gravité
  // Eventuellement créer des obstacles
  dt = 0.015;
  absorb = 0.5;
}

Environnement::~Environnement() {

}

float Environnement::getCote() const {return cote;}
VecteurR3 Environnement::getGravite() const {return gravite;}
VecteurR3 Environnement::getOrigineEnv() const {return origineEnv;}
std::vector<Obstacle> Environnement::getVObstacles() const{return vObstacles;}

Environnement Environnement::operator++(int a) {
  collisionsInterDrones();
  for (auto& pDrone : essaim->getVDrones()) {
    collisionBords(*pDrone);
    for (auto& obs : vObstacles)
      collisionObstacle(*pDrone, obs);
    calculerPos(*pDrone);
  }
  return *this;
}

void Environnement::ajouterObstacle(const Obstacle& obs) {
  vObstacles.push_back(obs);
}

void Environnement::calculerPos(Drone& drone) {
  // f(t+dt) = f(t) + f'(t)*dt
  drone.setVitesse(drone.getVitesse()+(drone.getAcceleration()+gravite)*dt);
  drone.setPosition(drone.getPosition()+drone.getVitesse()*dt);
}

void Environnement::collisionsInterDrones() {
  std::vector<Drone*> vPDrone = essaim->getVDrones();
  size_t sizeV = vPDrone.size(); // éviter deux accès
  for (size_t i = 0; i < sizeV; i++) {
    for (size_t j = i+1; j < sizeV; j++) {
      // ce couple (i,j) n'a nécessairement encore jamais été étudié
      VecteurR3 diffPos = vPDrone[i]->getPosition() - vPDrone[j]->getPosition();
      if (diffPos.norme2() < vPDrone[i]->getRayon()+vPDrone[j]->getRayon()) {
        vPDrone[i]->neFonctionnePlus();
        vPDrone[j]->neFonctionnePlus();
        VecteurR3 vColl = diffPos*(1./diffPos.norme2()); // Vecteur unitaire orthogonal au plan de collision
        // ici il serait plus opti de calculer une seule fois la matrice H(u) ...
        vPDrone[i]->setVitesse(vColl.reflexionPlanOrtho(vPDrone[i]->getVitesse())*absorb);
        vPDrone[j]->setVitesse(vColl.reflexionPlanOrtho(vPDrone[j]->getVitesse())*absorb);
        vPDrone[j]->setPosition(vPDrone[i]->getPosition()-diffPos*1.1);
      }
    }
  }
}

void Environnement::collisionBords(Drone& drone) {
  // Vérifications bords de l'Environnement
  float rayon = drone.getRayon();
  VecteurR3 dronePos = drone.getPosition();
  // Plans Z
  if (dronePos.getZ()-rayon < origineEnv.getZ()) {
    drone.neFonctionnePlus();
    dronePos.setZ(origineEnv.getZ()+rayon);
    drone.setPosition(dronePos);
    drone.setVitesse(VecteurR3(0,0,1).reflexionPlanOrtho(drone.getVitesse())*absorb);
  } else if (dronePos.getZ()+rayon > origineEnv.getZ()+cote) {
    drone.neFonctionnePlus();
    dronePos.setZ(origineEnv.getZ()-rayon+cote);
    drone.setPosition(dronePos);
    drone.setVitesse(VecteurR3(0,0,-1).reflexionPlanOrtho(drone.getVitesse())*absorb);
  }
  // Plans X
  if (dronePos.getX()-rayon < origineEnv.getX()) {
    drone.neFonctionnePlus();
    dronePos.setX(origineEnv.getX()+rayon);
    drone.setPosition(dronePos);
    drone.setVitesse(VecteurR3(1,0,0).reflexionPlanOrtho(drone.getVitesse())*absorb);
  } else if (dronePos.getX()+rayon > origineEnv.getX()+cote) {
    drone.neFonctionnePlus();
    dronePos.setX(origineEnv.getX()-rayon+cote);
    drone.setPosition(dronePos);
    drone.setVitesse(VecteurR3(-1,0,0).reflexionPlanOrtho(drone.getVitesse())*absorb);
  }
  // Plans Y
  if (dronePos.getY()-rayon < origineEnv.getY()) {
    drone.neFonctionnePlus();
    dronePos.setY(origineEnv.getY()+rayon);
    drone.setPosition(dronePos);
    drone.setVitesse(VecteurR3(0,1,0).reflexionPlanOrtho(drone.getVitesse())*absorb);
  } else if (dronePos.getY()+rayon > origineEnv.getY()+cote) {
    drone.neFonctionnePlus();
    dronePos.setY(origineEnv.getY()-rayon+cote);
    drone.setPosition(dronePos);
    drone.setVitesse(VecteurR3(0,-1,0).reflexionPlanOrtho(drone.getVitesse())*absorb);
  }
}


void Environnement::collisionObstacle(Drone& drone, Obstacle& obs) {
  float posx = drone.getPosition().getX();
  float posy = drone.getPosition().getY();
  float posz = drone.getPosition().getZ();
  float minx = obs.getInit().getX();
  float miny = obs.getInit().getY();
  float minz = obs.getInit().getZ();
  float maxx = minx + obs.getTailleX();
  float maxy = miny + obs.getTailleY();
  float maxz = minz + obs.getTailleZ();
  float rayon = drone.getRayon();

  VecteurR3 posDrone = drone.getPosition();
  VecteurR3 vecfinal = VecteurR3(0,0,0);
  VecteurR3 diffPos = (obs.getCentre()-posDrone).valeurAbsolue();
  VecteurR3 Centre = obs.getCentre();


  // Vérification naïve : considérer la phère comme un cube
  if ((posx>minx-rayon) && (posx<maxx+rayon) &&
      (posy>miny-rayon) && (posy<maxy+rayon) &&
      (posz>minz-rayon) && (posz<maxz+rayon)) {


  if ((fabs(diffPos[0]<obs.getTailleX()/2.)) && (fabs(diffPos[1]<obs.getTailleY()/2.)))
  {
  vecfinal = VecteurR3(0,0,sgn(posz-Centre[2]));
  drone.setPosition(VecteurR3(posx,posy,Centre.getZ()+sgn(posz-Centre[2])*obs.getTailleZ()/2.+sgn(posz-Centre[2])*drone.getRayon()));

  }

  if ((fabs(diffPos[1]<obs.getTailleY()/2.)) && (fabs(diffPos[2]<obs.getTailleZ()/2.)))
  {
  vecfinal = VecteurR3(sgn(posx-Centre[0]),0,0);
  drone.setPosition(VecteurR3(Centre.getX()+sgn(posx-Centre[0])*obs.getTailleX()/2.+sgn(posx-Centre[0])*drone.getRayon(),posy,posz));
  //drone.setPosition(VecteurR3(0,0,0));
  }

  if ((fabs(diffPos[0]<obs.getTailleX()/2.)) && (fabs(diffPos[2]<obs.getTailleZ()/2.)))
  {
  vecfinal = VecteurR3(0,sgn(posy-Centre[1]),0);
  drone.setPosition(VecteurR3(posx,Centre.getY()+sgn(posy-Centre[1])*obs.getTailleY()/2.+sgn(posy-Centre[1])*drone.getRayon(),posz));
  //drone.setPosition(VecteurR3(0.5,0,0));

  }

    drone.neFonctionnePlus();
    drone.setVitesse(vecfinal.reflexionPlanOrtho(drone.getVitesse())*absorb);
  }
}

void Environnement::ajouterColis(const VecteurR3& retrait, const VecteurR3& depot){
  vRetraits.push_back(retrait);
  vDepots.push_back(depot);
}

void Environnement::associerEssaim(Essaim *e) {
  essaim = e;
}


std::vector<VecteurR3> Environnement::getVRetraits() const{return vRetraits;}
std::vector<VecteurR3> Environnement::getVDepots() const{return vDepots;}

std::vector<Drone*> Environnement::getEssaimDrones() const {
  return essaim->getVDrones();
}
