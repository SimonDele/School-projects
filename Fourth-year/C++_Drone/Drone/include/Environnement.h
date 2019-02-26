#ifndef ENVIRONNEMENT_H
#define ENVIRONNEMENT_H

#include <vector>
#include <iostream>
#include "../include/Essaim.h"
#include "../include/Obstacle.h"
#include "../include/Drone.h"
#include "../include/VecteurR3.h"
class Essaim;
/**
*
* Classe contenant les éléments de l'environnement et leurs positions (i.e Essaim, Obstacles, colis)
* Gère la détection de collision et le calcul de la position des drones.
* C'est le moteur physique du projet.
*
* @authors Timothé, Simon
*/
class Environnement {
    private:
        /** Point aux coordonnées x,y,z minimales dans le cube de travail */
        VecteurR3 origineEnv;
        /** coté du cube */
        float cote;
        /** Coefficient d'absorbtion des collisions */
        float absorb;
        /** Liste des obstacles de l'environnement */
        std::vector<Obstacle> vObstacles;

        /** Essaim de drone, c'est l'ensemble de drones */
        Essaim *essaim;

        /** Vecteur acceleration de gravité, perpétuellement subie par les drones */
        VecteurR3 gravite;
        /** Constante de delta temps, dans la formule f(t+dt) = f(t)+dt*f'(t)  */
        float dt;
        /** Liste des points de Retrait présents dans l'environnement */
        std::vector<VecteurR3> vRetraits;
        /** Liste des points de Depot présents dans l'environnement */
        std::vector<VecteurR3> vDepots;

        /** Calcule la position d'un drone en prenant en compte le vecteur accélération du drone et la gravité de l'environnement */
        void calculerPos(Drone&);

        /** Vérifie de manière optimisée si les drones entrent en collision;
        * affecte les valeurs de vitesse correspondantes le cas échéant.*/
        void collisionsInterDrones();
        /** Vérifie si un drone entre en collision avec bord de l'Environnement.
         * Affecte directement la vitesse de l'objet le cas échéant.
         */
        void collisionBords(Drone&);
        /** Vérifie si un drone entre en collision avec un Obstacle.
         * Affecte directement la vitesse de l'objet le cas échéant.
         */
        void collisionObstacle(Drone&,Obstacle&);

    public:
        /** Constructeur vide */
        Environnement();
        /** Constructeur d'Environnement avec la taille d'un côté.
         * Le reste sera ajouté via les méthodes prévues à cet effet. */
        Environnement(const float tailleCote);
        virtual ~Environnement();

        float getCote() const;
        VecteurR3 getGravite() const;
        std::vector<VecteurR3> getVRetraits() const;
        std::vector<VecteurR3> getVDepots() const;
        VecteurR3 getOrigineEnv() const;
        std::vector<Obstacle> getVObstacles() const;

        /** Surchage de l'opérateur ++, afin de passer au temps+1 */
        Environnement operator++(int);
        /** Ajoute directement un objet Obstacle à la liste de l'Environnement */
        void ajouterObstacle(const Obstacle&);
        /** Ajoute un colis dans la liste à récupérer */
        void ajouterColis(const VecteurR3&, const VecteurR3&);
        /** Donne sa valeur à l'attribut essaim une fois ce dernier créé (juste un set) */
        void associerEssaim(Essaim*);
        /** Getter des Drones pour simplifier l'accès lors de l'affichage */
        std::vector<Drone*> getEssaimDrones() const;
    protected:
};

#endif // ENVIRONNEMENT_H
