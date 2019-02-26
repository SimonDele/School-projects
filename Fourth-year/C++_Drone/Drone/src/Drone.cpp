#include "../include/Drone.h"
#include "../include/VecteurR3.h"
#include <cstddef>

Drone::Drone(const VecteurR3 pos) {
  position = pos;
}

Drone::Drone(const float rayonDrone, const VecteurR3 pos, const std::vector<Capteur>& vCap) {
  rayon = rayonDrone;
  position = pos;
  vCapteurs = vCap;
}

Drone::Drone(const float rayonDrone, const VecteurR3 posInit, const std::vector<Capteur> vCap, const VecteurR3 _gravite,const VecteurR3 vitInit) {
  rayon = rayonDrone;
  position = posInit;
  vitesse = vitInit;
  acceleration = _gravite*-1;
  vCapteurs = vCap;
  for (auto& capteur : vCapteurs) capteur.associerInfoDrone(rayon, &position);
  fonctionne = true;
  porteColis = false;
  gravite = _gravite;
  comportement = new Naif(position,vitesse);
}

Drone::~Drone() {
  //dtor
}

VecteurR3 Drone::getPremierObjectif() const {return vObjectifs.front();}
std::queue<VecteurR3> Drone::getVObjectifs() const {return vObjectifs;}
std::vector<Capteur> Drone::getVCapteurs() const {return vCapteurs;}
VecteurR3 Drone::getPosition() const {return position;}
VecteurR3 Drone::getVitesse() const {return vitesse;}
VecteurR3 Drone::getAcceleration() const {return acceleration;}
void Drone::setPosition(const VecteurR3 nvllPos) {position=nvllPos;}
void Drone::setVitesse(const VecteurR3 nvllVit) {vitesse=nvllVit;}
void Drone::setAcceleration(const VecteurR3& _acc) {acceleration = _acc;}
float Drone::getRayon() const {return rayon;}
void Drone::neFonctionnePlus() {fonctionne = false;}
bool Drone::estFonctionnel() const {return fonctionne;}
bool Drone::aObjectif() const {return vObjectifs.size()>0;}
bool Drone::porteUnColis() const {return porteColis;}

bool Drone::atteintObjectif() {
  bool ret = false;
  if(position.egal(getPremierObjectif(), rayon*0.01)) {
    ret = true;
    vObjectifs.pop();
    porteColis = !porteColis;
  }
  return ret;
}

Drone Drone::operator++(int a) {
  //Update capteurs
  for(auto &capteur : vCapteurs){
      capteur.updateDistanceDetectee();
  }

  acceleration = VecteurR3();
  //Deplacement
  if (fonctionne) {
    if (aObjectif()) {
      atteintObjectif();
      acceleration = comportement->allerPoint(position,getPremierObjectif(),vCapteurs, vitesse);
    } else acceleration = vitesse*-5; // le faire freiner pour atteindre v=0
    acceleration+=gravite*(-1); // il contre la gravité par défaut
  }
  return *this;
}

void Drone::ajouterObjectif(const VecteurR3 &obj){
    vObjectifs.push(obj);
}
void Drone::livrerColis(const VecteurR3& retrait, const VecteurR3& depot)
{
    ajouterObjectif(retrait);
    ajouterObjectif(depot);
}
