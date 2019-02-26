#include "../include/Capteur.h"
#include "../include/Environnement.h"
#include<cmath>
Capteur::Capteur(const float &p, const VecteurR3 &dir, Environnement *environnement) {
  portee = p;
  env = environnement;
  direction = dir;
  distanceDetectee = portee;
}

Capteur::~Capteur() {}

float Capteur::getDistanceDetectee() const {return distanceDetectee;}
float Capteur::getPortee() const {return portee;}
VecteurR3 Capteur::getDirection() const {return direction;}

bool Capteur::detecteQQch() const {
  return distanceDetectee<portee;
}

void Capteur::associerInfoDrone(const float rayon, VecteurR3 *_pPositionDrone) {
  tailleDrone = rayon;
  pPositionDrone = _pPositionDrone;
}

void Capteur::updateDistanceDetecteeObstacle() {
  //On itére sur les obstacles

  for (auto& obs : env->getVObstacles()){
    VecteurR3 centreObs = obs.getCentre();
    vector<VecteurR3> face; //C'est la face de l'obstacle vers lequel le capteur pointe

    //On répère la face pointée le capteur
    if(direction[0] != 0){
      if((centreObs - (*pPositionDrone))[0] > 0 ) face = obs.getFaceXMin();
      else face = obs.getFaceXMax();
    } else if(direction[1] != 0){
      if((centreObs - (*pPositionDrone))[1] > 0 ) face = obs.getFaceYMin();
      else face = obs.getFaceYMax();
    } else if(direction[2] != 0){
      if((centreObs - (*pPositionDrone))[2] > 0 ) face = obs.getFaceZMin();
      else face = obs.getFaceZMax();
    }

    //On calcule les sommets de la face
    float xmin = min(face[0][0], face[2][0]);
    float xmax = max(face[0][0], face[2][0]);
    float ymin = min(face[0][1], face[2][1]);
    float ymax = max(face[0][1], face[2][1]);
    float zmin = min(face[0][2], face[2][2]);
    float zmax = max(face[0][2], face[2][2]);

    //On calcule la distance détectée
    //Pour cela il faut vérifier que le drone est bien en face de la face et non pas en dehors
    //Dans ce cas la distance détectée est calculée
    //Sinon elle est "infinie" du coup on renverra la portée du capteur
    if(direction[0] != 0){
      if(((*pPositionDrone)[1] >= ymin) && ((*pPositionDrone)[1] <= ymax) &&
      ((*pPositionDrone)[2] >= zmin) && ((*pPositionDrone)[2] <= zmax) &&
      ((xmin-(*pPositionDrone)[0])*direction[0]>0)) {
        distanceDetectee = abs(xmin - (*pPositionDrone)[0] + tailleDrone); // xmin == xmax ici
      } else distanceDetectee = portee;

    }else if(direction[1] != 0){
      if(((*pPositionDrone)[0] >= xmin) && ((*pPositionDrone)[0] <= xmax) &&
      ((*pPositionDrone)[2] >= zmin) && ((*pPositionDrone)[2] <= zmax) &&
      ((ymin-(*pPositionDrone)[1])*direction[1]>0)) {
        distanceDetectee = abs(ymin - (*pPositionDrone)[1] + tailleDrone);
      } else distanceDetectee = portee;
    }else if(direction[2] != 0){
      if(((*pPositionDrone)[1] >= ymin) && ((*pPositionDrone)[1] <= ymax) &&
      ((*pPositionDrone)[0] >= xmin) && ((*pPositionDrone)[0] <= xmax) &&
      ((zmin-(*pPositionDrone)[2])*direction[2]>0)) {
        distanceDetectee = abs(zmin - (*pPositionDrone)[2] + tailleDrone);
      } else distanceDetectee = portee;
    }
  }
  distanceDetectee = min(portee, distanceDetectee);
}

void Capteur::updateDistanceDetecteeBords() {
  for (size_t i = 0; i < 3; i++) {
    // Une seule des directions est non nulle dans notre cas
    if (direction[i]>0) {
      distanceDetectee = min(distanceDetectee, (env->getOrigineEnv()[i]+env->getCote())-(*pPositionDrone)[i]-tailleDrone);
    } else if (direction[i]<0) {
      distanceDetectee = min(distanceDetectee, (*pPositionDrone)[i]-tailleDrone-env->getOrigineEnv()[i]);
    }
  }
}

void Capteur::updateDistanceDetectee() {
  distanceDetectee = portee;
  updateDistanceDetecteeObstacle();
  //updateDistanceDetecteeBords();
}
