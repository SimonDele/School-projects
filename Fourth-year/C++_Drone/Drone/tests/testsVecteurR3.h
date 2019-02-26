#ifndef TESTSVECTEURR3_H
#define TESTSVECTEURR3_H

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

#include "../include/VecteurR3.h"

class testsVecteurR3 : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(testsVecteurR3);
    CPPUNIT_TEST(testEgalite);
    CPPUNIT_TEST(testAddition);
    CPPUNIT_TEST(testSoustraction);
    CPPUNIT_TEST(testMulti);
    CPPUNIT_TEST(testDiv);
    CPPUNIT_TEST(testProdScal);
    CPPUNIT_TEST(testMultiplicationScalaire);
    CPPUNIT_TEST(testIncrementation);
    CPPUNIT_TEST(testNorme22);
    CPPUNIT_TEST(testprodVec);
    CPPUNIT_TEST(testValeurAbsolue);
    CPPUNIT_TEST(testReflexionPlanOrtho);
    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);
    protected:
        void testEgalite(void);
        void testAddition(void);
        void testSoustraction(void);
        void testMulti(void);
        void testDiv(void);
        void testProdScal(void);
        void testMultiplicationScalaire(void);
        void testIncrementation(void);
        void testNorme22(void);
        void testprodVec(void);
        void testValeurAbsolue(void);
        void testReflexionPlanOrtho(void);

    private:
        VecteurR3 v1;
        VecteurR3 v2;
};

#endif // TESTSVECTEURR3_H
