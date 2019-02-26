/*
#ifndef TESTSCUBIQUE_H
#define TESTSCUBIQUE_H

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
#include "../include/Cubique.h"

/**
* classe de test de la classe Cubique
* @author Simon
*/
/*
class testsCubique : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(testsCubique);
    CPPUNIT_TEST(testsGenererMaillage());
    CPPUNIT_TEST_SUITE_END();
    public:
        void setUp(void);
        void tearDown(void);
    protected:
        /** A partir des informations relatives à la formation cubique (nbre drones, longeur  coté et origine
        On verifie que le maillage est celui attendu.
        * Plus précisement on va créer une formation à l'origine du repère, de longueur 1 pour 8 drones.
        * On vérifie alors que le retour de la fonction est les 8 sommets du cube.
        */
/*        void testsGenererMaillage();
    private:
        /** Objet a tester */
  //      Cubique fCubique;
//};

//#endif // TESTSCUBIQUE_H
