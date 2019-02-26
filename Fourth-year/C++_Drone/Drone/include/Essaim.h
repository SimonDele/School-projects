#ifndef ESSAIM_H
#define ESSAIM_H

#include <vector>
#include <iostream>
#include <stdexcept>
#include "../include/Environnement.h"
#include "../include/VecteurR3.h"
#include "../include/Formation.h"
#include "../include/Comportement.h"
#include "../include/Capteur.h"
#include "../include/Drone.h"

/**
* La classe Essaim est celle qui contient l'ensemble des drones
* Elle a pour objectif de contrôler leurs objectifs (Attribution des colis aux drones, formations, ...)
*
* @authors Timothé, Simon
*/

class Essaim {
    public:

        /** Constructeur vide */
        Essaim();
        /** Constructeur principal (utilisé dans le main de l'application) prenant l'Environnement et le nombre de Drones */
        Essaim(Environnement &env, int nbDrones);

        virtual ~Essaim();
        /** Ordre d'aller retirer un colis. Le drone qui doit aller le colis au point B est determiné dans le corps de la fonction et non passé en entrée
          * @param retrait point de retrait du colis
          * @param depot lieu où déposer le colis
          */
        void retirerColis(VecteurR3 retrait, VecteurR3 depot);

        /** Ordre aux drones de l'essaim de réaliser une formation */
        void formation(Formation& F);

        /** Ajoute un drone à l'essaim (dans le vector de drone) */
        void ajouterDrone(Drone&);

        /** getter du vector de Drone */
        std::vector<Drone*> getVDrones() const;
    protected:

    private:
        /** L'ensemble des drones qui composent l'essaim */
        std::vector<Drone*> vDrones;
        /**
        * A partir de la liste des objectifs à atteindre, y affecte les Drones en fonction de leur position actuelle.
        * ex : vector<int> = [2, 1, 3], le drone numéro 2 ira à vPosFormation[1]
        * @param nuagePoints le nuage de points (VecteurR3) à atteindre
        * @return Vecteur permutation qui donne l'ordre des drones de l'Essaim dans le vecteur pos (vecteur d'entrée)
        */
        std::vector<int> affecterDronePos(vector<VecteurR3> nuagePoints);
};

#endif // ESSAIM_H
