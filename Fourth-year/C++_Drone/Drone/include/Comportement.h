#ifndef COMPORTEMENT_H
#define COMPORTEMENT_H

#include<vector>
#include "../include/Capteur.h"
#include "../include/VecteurR3.h"
/**
* Interface donnant la fonction fondamentale de comportement de chaque Drone: le choix d'un nouveau vecteur accélération.
* @author Louis
*/
class Comportement {
    public:
        /** Constructeur vide. */
        Comportement();
        /** Destructeur vide. */
        virtual ~Comportement();
        /** Méthode fondamentale de Comportement des Drones.
        * A partir des positions du Drone et de son premier objectif, détermine (la méthode importe peu ici) le vecteur accélération pour la frame suivante.
        * @param posActuelle la position du Drone au temps t.
        * @param destination la position à atteindre.
        * @param vCapteurs, le vecteur des Capteurs donnant l'information sensorielle du Drone.
        * @return le vecteur accélération
        */
        virtual VecteurR3 allerPoint(const VecteurR3 &posActuelle,const VecteurR3 &destination, const std::vector<Capteur> vCapteurs, const VecteurR3 vitesse)  =0;
    protected:

    private:
};

#endif // COMPORTEMENT_H
