#ifndef VECTEURR3_H
#define VECTEURR3_H

#include <iostream>

/**
 * Classe d'un vecteur dans R3, avec trois coordonnées et les opérations classiques des ensembles vectoriels.
 * @authors : Margot, Morgan, Théau, Louis
 * @version 1.0
 * @13 avril 2018
 */

class VecteurR3 {
  private:
    float x,y,z;

  public:

    /**
    * Constructeur de VecteurR3 initilisant les coordonnées à l'origine.
    */
    VecteurR3();
    /** Constructeur de VecteurR3 à partir de trois coordonnées données. */
    VecteurR3(const float& x,const float &y, const float& z);
    /** Destructeur d'un VecteurR3. */
    virtual ~VecteurR3();

    // Getters des coordonnées
    float getX() const;
    float getY() const;
    float getZ() const;
    // Setters des coordonnées
    void setX(const float&);
    void setY(const float&);
    void setZ(const float&);
    /** Alternative aux getters : operateur [] */
    float operator[](const int&) const;

    bool operator==(const VecteurR3& vComp) const;
    /**Comparaison de deux vecteurs à un voisinage de rayon donné près
     * @param vComp le VecteurR3 auquel se comparer
     * @param epsilon la marge d'erreur que l'on se laisse
     * @return si le vecteur est bien le même que celui en entrée, à une précision epsilon
     */
    bool egal (const VecteurR3& vComp, const float& epsilon=0) const;

    /**Addition de deux vecteurs composante par composante */
    VecteurR3 operator+(const VecteurR3&) const;

    /**Soustraction de deux vecteurs composante par composante */
    VecteurR3 operator-(const VecteurR3&) const;

    /**division de deux vecteurs composante par composante */
    VecteurR3 div(const VecteurR3&) const;

    /**multiplication de deux vecteurs composante par composante */
    VecteurR3 multi(const VecteurR3&) const;

    /**Affectation d'un vecteur à partir d'un autre*/
    void operator=(const VecteurR3&);

    /** Addition des coordonnées actuelles avec celles d'un autre (raccourci +=)*/
    void operator+=(const VecteurR3&);
    /** Soustraction des coordonnées actuelles avec celles d'un autre (raccourci -=)*/
    void operator-=(const VecteurR3&);

    /** Produit scalaire de ce vecteur avec un autre*/
    float operator*(const VecteurR3&) const;

    /**Multiplication d'un vecteur par un scalaire */
    VecteurR3 operator*(const float&) const;

    /** Norme AU CARRE du vecteur (pour optimisation, lorsque la distance même n'est pas nécessaire) */
    float norme22() const;

    /** Norme (ou distance à l'origine) du vecteur. Calcule simplement la racine de norme22. */
    float norme2() const;

    /** Calcul du produit vectoriel. (Useful pour verifier la colinearite). */
    VecteurR3 prodVec(const VecteurR3&) const;
    /** Ressort la valeur absolue composante par composante */
    VecteurR3 valeurAbsolue() const;
    /** Calcul le produit de la matrice de Householder générée par ce VecteurR3 (this)
     * avec un vecteur donné en entrée. Cela donne le vecteur de reflexion par rapport
     * au plan orthogonal à ce vecteur. */
    VecteurR3 reflexionPlanOrtho(const VecteurR3&) const;
    /** Methode d'affichage pour debug */
    friend std::ostream& operator<<(std::ostream& os, const VecteurR3&);
};

#endif // VECTEURR3_H
