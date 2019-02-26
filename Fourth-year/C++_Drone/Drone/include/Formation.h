#ifndef FORMATION_H
#define FORMATION_H

#include<vector>
#include "../include/VecteurR3.h"

using namespace std;
/**
 * Classe abstraite correspondant à une figure géométrique aérienne que peut réaliser une parte ou l'ensemble de l'essaim.
 * @author Margot, Théau et Morgan
 * @date 13/04/18
 */
class Formation {
    public:
				/** Constructeur inutilisable (classe abstraite) */
        Formation();
				/** Destructeur inutilisable (classe abstraite) */
        virtual ~Formation();

 /**
  * Méthode permettant de générer le maillage à partir des points et des contraintes de taille de Formation.
  * @return Retourne une nouvelle liste de vecteurs
  */
        virtual vector<VecteurR3> genererMaillage() = 0;

    protected:
    /** Altitude de la formation */
    float altitude;
    /** Le nombre de drones qui composent la formation */
    int nbDrones;

    private:
};

#endif // FORMATION_H
