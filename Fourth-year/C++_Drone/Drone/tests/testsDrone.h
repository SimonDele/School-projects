#ifndef TESTSDRONE_H
#define TESTSDRONE_H

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
#include "../include/Drone.h"
#include "../include/Environnement.h"

class testsDrone : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(testsDrone);
    CPPUNIT_TEST(testAjouterObjectif);
    CPPUNIT_TEST(testLivrerColis);
    CPPUNIT_TEST(testAtteintObjectif);
    CPPUNIT_TEST(testplusplus);
    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);
    protected:
        /** Teste l'ajout d'un objectif dans la liste des points à atteindre du Drone.
         * ASSERT si l'objectif a bien été ajouté; c'est-à-dire que la liste est plus grande d'un élément, qui est celui affiché.
         * La vérification de la validité du point n'est pas du ressort du Drone (et donc de cette fonction).
         */
        void testAjouterObjectif();

        /** Teste l'ordre de livraison de colis.
          * Réalise globalement les mêmes tests que testAjouterObjectif, sur deux points.
          * @see testAjouterObjectif
          */
        void testLivrerColis();
        /** Teste si l'objectif est bien considéré comme atteint et bien supprimé de la liste */
        void testAtteintObjectif();
        /** Teste si la position est bien actualisé */
        void testplusplus();
    private:
};

#endif // TESTSDRONE_H
