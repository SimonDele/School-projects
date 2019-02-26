#ifndef DLITE_H
#define DLITE_H

#include "../include/Comportement.h"

/**
* Type de Comportement: algorithme Dlite: amélioration dynamique de l'algorithme de pathfinding conventionnel A*.
*/
class Dlite : public Comportement {
    public:
        /** Constructeur de l'algorithme. */
        Dlite();
        /** Destructeur de l'algorithme. */
        virtual ~Dlite();
        /** Méthode fondamentale de Comportement des Drones.
        * A partir des positions du Drone, de son premier objectif et des capteurs, détermine le vecteur accélération pour la frame suivante.
        * @param posActuelle la position du Drone au temps t.
        * @param destination la position à atteindre.
        * @param vCapteurs, le vecteur des Capteurs donnant l'information sensorielle du Drone.
        * @return le vecteur accélération
        */
        VecteurR3 allerPoint(VecteurR3 posActuelle, VecteurR3 destination, std::vector<Capteur> vCapteurs);
    protected:

    private:
};

#endif // DLITE_H
