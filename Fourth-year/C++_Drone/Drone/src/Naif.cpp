#include <vector>
#include "../include/VecteurR3.h"
#include "../include/Naif.h"
#include "../include/Capteur.h"
#include<cmath>

Naif::Naif(const VecteurR3 _depart, const VecteurR3 _v0) {
  depart = _depart;
  dest = depart;
  v0=_v0;
}

Naif::~Naif() {
    //dtor
}

// Indique si le drone se trouve au dessus/en dessous de l'objectif
bool Naif::atteint(const VecteurR3 &posActuelle, const VecteurR3 &destination, const float &epsilon) const {
    return((std::abs(posActuelle.getX()-destination.getX())<epsilon)&&(std::abs(posActuelle.getY()-destination.getY())<epsilon));
}


// Méthode qui selectionne les capteurs pertinents en fonction du vecteur directionnel, et regarde s'ils indiquent la présence ou non d'un obstacle
bool Naif::presenceObstacles(const VecteurR3 posActuelle, const VecteurR3 destination,  const std::vector<Capteur> vCapteurs, const VecteurR3& vitesse) {
    bool res = false;
    for (auto& capteur : vCapteurs)
      if ((capteur.getDirection()*(destination-posActuelle)>0)&&(capteur.detecteQQch())) {
        res = true;
        depart = posActuelle;
        v0 = vitesse;
        break;
      }
    return res;
}


// Retourne le vecteur accélération en fonction du cas dans lequel on se trouve
VecteurR3 Naif::allerPoint(const VecteurR3 &posActuelle,const VecteurR3 &destination,const std::vector<Capteur> vCapteurs, const VecteurR3 vitesse ) {
  VecteurR3 acc = VecteurR3();

  if (!(dest == destination)) {
    depart = posActuelle;
    v0 = vitesse;
    dest = destination;
  }
  /* Version simplifiée, fonctionnelle.
  VecteurR3 diffPos = destination - posActuelle;
  return (posActuelle*-2 + depart + destination)*(1/4.); */
  VecteurR3 diffPos = dest - posActuelle;
  // S'il y a un obstacle et que nous ne sommes pas au dessus du but
  if (presenceObstacles(posActuelle, dest, vCapteurs, vitesse) &&
      !diffPos.egal(VecteurR3(0,0,diffPos[2]),0.05)) {
    acc -= vitesse*10; // Freine brutalement
    acc += VecteurR3(0,0,3); // on monte
  } else {
    VecteurR3 milieu = (dest+depart)*0.5;
    acc = depart+dest-posActuelle*2;
    // Code Theau Morgan
    //acc = v0.multi((posActuelle*2-(destination+milieu)).div(((depart-milieu).multi(depart-destination))))+(posActuelle*-2)+destination+depart;

  }
  return acc;
}
