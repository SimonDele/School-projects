#ifndef NAIF_H
#define NAIF_H

#include <vector>
#include "../include/VecteurR3.h"
#include "../include/Comportement.h"

/**
* Classe héritant de Comportement, c'est donc un algo possible de déplacement des drones.
* Il consiste à monter en altitude lorsque le drone rencontre un obstacle devant lui afin de passer au dessus.
*
* @author Simon
*/
class Naif : public Comportement {
    public:
        /** Initialise le point duquel le Drone part et sa vitesse */
        Naif(const VecteurR3, const VecteurR3);
        virtual ~Naif();
        /** Méthode fondamentale de Comportement des Drones.
        * A partir des positions du Drone, de son premier objectif et des capteurs, d�termine le vecteur acc�l�ration pour la frame suivante.
        * @param posActuelle la position du Drone au temps t.
        * @param destination la position � atteindre.
        * @param vCapteurs, le vecteur des Capteurs donnant l'information sensorielle du Drone.
        * @return le vecteur acc�l�ration
        */
        virtual VecteurR3 allerPoint(const VecteurR3 &posActuelle,const VecteurR3 &destination, const std::vector<Capteur> vCapteurs, const VecteurR3 vitesse) override;

        bool atteintFinal(const VecteurR3 &posActuelle,const VecteurR3 &destination)const;

        bool atteint(const VecteurR3 &posActuelle,const VecteurR3 &destination, const float &epsilon) const;

        bool presenceObstacles(const VecteurR3 posActuelle, const VecteurR3 destination,  const std::vector<Capteur> vCapteurs, const VecteurR3&);

        // ATTRIBUTS
        /** Position à laquelle le Drone a commencé à aller à l'objectif. Permet de réduire sa vitesse avant d'atteindre l'objectif.*/
        VecteurR3 depart;
        /** Destination à atteindre. Permet de réinitialiser le depart en cas de changement d'objectif. */
        VecteurR3 dest;
        /** Vitesse à laquelle le drone est parti */
        VecteurR3 v0;
    protected:

    private:
};

#endif // NAIF_H
