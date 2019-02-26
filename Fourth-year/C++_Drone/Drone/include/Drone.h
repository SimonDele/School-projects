#ifndef DRONE_H
#define DRONE_H

#include "../include/VecteurR3.h"
#include "../include/Comportement.h"
#include "../include/Naif.h"
#include <cstddef>
#include<vector>
#include<queue>

/**
* Agent du réseau qui a pour principale fonctionnalité de pouvoir se rendre d'un point à un autre, en suivant liste d'objectifs. Il se déplace en se donnant un vecteur accélération, qui donnera sa vitesse et position en temps t+1 via la classe Environnement.
* @author Louis, Quentin
*/
class Drone {
  private:
    /** Rayon du Drone, puisqu'il est modélisé comme une sphère */
    float rayon;
    /** Indique si le Drone porte un colis. */
    bool porteColis;
    /** Indique si le Drone ne s'est pas pris un Obstacle (fixe) ou un autre Drone. */
    bool fonctionne;
    /** Classe gestionnaire du vecteur accélération, en se basant sur les objectifs et les Capteurs du Drone. */
    Comportement *comportement;
    /** Position du Drone dans l'espace. */
    VecteurR3 position;
    /** Vitesse du Drone, calculée à partir de l'accélération et de la vitesse en t-1. */
    VecteurR3 vitesse;
    /** Vecteur accélération du Drone, donné par le Comportement en fonction de son voisinage. Mis à jour à chaque tour de boucle. */
    VecteurR3 acceleration;
    /** Ensemble des Capteurs du Drones, répartis autour de ce dernier. Cela permet de discrétiser son voisinage et les informations reçues. */
    std::vector<Capteur> vCapteurs;
    /** Liste des objectifs du Drone - c'est-à-dire liste de colis à livrer ou de position de formation à laquelle aller. */
    std::queue<VecteurR3> vObjectifs;
    /** Gravite de l'environnement. Le Drone ne connait que ceci de l'Environnement,
     * pour pouvoir la contrer sans encombrer le Comportement. */
    VecteurR3 gravite;
    /** Fonction qui renvoie vrai si le drone a atteint le premier de ses objectifs */
    bool objectifDone();

  public:
    /** Constructeur de Drone pour tests, avec position */
    Drone(const VecteurR3);
    /** Constructeur de test des Capteurs */
    Drone(const float, const VecteurR3, const std::vector<Capteur>&);
    /** Constructeur effectif de Drone. Prend une position et (éventuellement) vitesse initiales, un rayon et un vecteur de Capteurs. */
    Drone(const float rayon, VecteurR3 pos, std::vector<Capteur> vCap, const VecteurR3 _gravite,VecteurR3 vit = VecteurR3());
    /**  */
    Drone operator++(int);
    /** Destructeur de Drone. */
    virtual ~Drone();

    /** Getter du premier objectif du Drone */
    VecteurR3 getPremierObjectif() const;
    /** Getter des objectifs du Drone */
    std::queue<VecteurR3> getVObjectifs() const;
    /** Getter du vecteur de capteurs */
    std::vector<Capteur> getVCapteurs() const;
    /** Getter du vecteur position */
    VecteurR3 getPosition() const;
    /** Getter du vecteur vitesse */
    VecteurR3 getVitesse() const;
    /** Getter du vecteur acceleration */
    VecteurR3 getAcceleration() const;
    /** Setter du vecteur position */
    void setPosition(const VecteurR3);
    /** Setter du vecteur vitesse */
    void setVitesse(const VecteurR3);
    /** Setter du vecteur acceleration */
    void setAcceleration(const VecteurR3&);
    /** Getter du rayon du Drone */
    float getRayon() const;
    /** affecte au bool 'fonctionne' la valeur false. */
    void neFonctionnePlus();
    /** Getter sur l'état du drone */
    bool estFonctionnel() const;
    /** Fonction qui indique si le drone a au moins un objectif (liste non nulle) */
    bool aObjectif() const;
    /** Teste si le drone a atteint son objectif.
     *Le cas échéant, l'objectif est supprimé de la liste. */
    bool atteintObjectif();
    /**
    * getter porteColis
    */
    bool porteUnColis() const;
    /**
    * Méthode qui ajoute une destination à la liste des objectifs.
    * @param obj le point de R3 à ajouter à la liste d'objectifs.
    */
    void ajouterObjectif(const VecteurR3& obj);
    /**
    * Ajoute à liste des objectifs le point de retrait et de dépôt du colis.
    * @param retrait Le point auquel récupérer le colis.
    * @param depot Le point auquel déposer le colis.
    */
    void livrerColis(const VecteurR3& retrait, const VecteurR3& depot);
};

#endif // DRONE_H
