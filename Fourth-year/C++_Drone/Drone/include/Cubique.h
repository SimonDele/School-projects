#ifndef CUBIQUE_H
#define CUBIQUE_H

#include "../include/Formation.h"
#include "../include/VecteurR3.h"
#include<vector>

using namespace std;
/**
 * Classe fille de Formation, qui permet de dessiner un cube.
 * @author Margot, Théau et Morgan
 * @date 13/04/18
 */
class Cubique : public Formation {
    public:
        /** Constructeur de la Formation. */
        Cubique(VecteurR3,float, int);
        /** Destructeur usuel de la Formation. */
        virtual ~Cubique();
        /** Méthode héritée, calcule le maillage adapté à la formation cubique */
        virtual vector<VecteurR3> genererMaillage();

    protected:
    /** Longueur du côté du cube*/
    float longueurCote;
    /** Orgine du cube */
    VecteurR3 origine;

    private:
};

#endif // CUBIQUE_H
