#ifndef TESTSESSAIM_H
#define TESTSESSAIM_H

#include<vector>
#include <iostream>
#include <string>
#include <list>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <netinet/in.h>
#include"../include/VecteurR3.h"
#include"../include/Essaim.h"

/**
* classe de test pour la classe Essaim
* @author Simon
*/

class testsEssaim  : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(testsEssaim);
    CPPUNIT_TEST(testAjouterDrone);
    CPPUNIT_TEST(testRetirerColis);
    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);
    protected:
        void testAjouterDrone();
        /** teste si la m�thode affecterDronePos affecte au drone le noeud du maillage le plus proche de sa position
        * C'est une m�thode fastidieuse � tester. On va tester un exemple simple.
        * Etant donn� 8 noeuds issus d'un maillage d'une formation cubique, on cr�� 8 drones l�g�rement d�cal� au 8 sommets.
        * On v�rifie que chaque drone a comme objectif d'aller au sommet � cot� de lui.
        */
        /** teste la m�thode retirer colis. On va faire apparaitre un colis a un endroit et on v�rifie que le drone le plus proche a bien re�u l'ordre de s'y rendre.
        * Pour cela on regarde que les points de retrait et d�pose ont �t� ajout� � la liste des objectifs du drone le plus proche.
        */
        void testRetirerColis();
        /** Appelle la fonction et vérifie si le bon Drone est bien dans la liste */
        void testAffectationDronePos();


    private:
      // Nous ne créons pas un essaim général pour éviter les pb de croisement entre tests (liste Drones)
};

#endif // TESTSESSAIM_H
