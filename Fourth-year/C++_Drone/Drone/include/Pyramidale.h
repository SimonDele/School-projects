#ifndef PYRAMIDALE_H
#define PYRAMIDALE_H

#include "../include/Formation.h"
#include "../include/VecteurR3.h"
#include<vector>

/**
 * Classe fille de Formation; dessine une pyramide.
 * @author Margot, Théau et Morgan
 * @date 13/04/18
 */

class Pyramidale : public Formation
{
    public:
        Pyramidale();
        virtual ~Pyramidale();

    protected:
  /** Points formant la base de la pyramide*/
	vector<VecteurR3> vPointsBase;
  /** Point sommet de la pyramide*/
	VecteurR3 sommet;

    private:
};

#endif // PYRAMIDALE_H
