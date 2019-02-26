#ifndef TESTSENVIRONNEMENT_H
#define TESTSENVIRONNEMENT_H

#include <iostream>
#include <string>
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

#include "../include/Environnement.h"


class testsEnvironnement
{

  CPPUNIT_TEST_SUITE(testsEnvironnement);
  CPPUNIT_TEST(testcalculerPos);
  CPPUNIT_TEST(testcolision);
  CPPUNIT_TEST_SUITE_END();

    public:
      void setup(void);
      void tearDown(void);
    protected:
      void testcalculerPos(void);
      void testcolision(void);
    private:
};

#endif // TESTSENVIRONNEMENT_H
