#include "../tests/testsVecteurR3.h"
#include <cmath>

void testsVecteurR3::setUp(void) {
    //Methode appel� d�s le debut, c'est ici qu'on est cens� cr�er les objets
    v1 = VecteurR3(1,2,3);
    v2 = VecteurR3(2,3,4);
}

void testsVecteurR3::tearDown(void) {
    //C'est ici qu'on d�truit les objets
}

void testsVecteurR3::testEgalite(void) {
  VecteurR3 vTemp = v1;
  CPPUNIT_ASSERT((v1[0]==vTemp[0])&&(v1[1]==vTemp[1])&&(v1[2]==vTemp[2]));
}

void testsVecteurR3::testAddition(void) {
    VecteurR3 add = v1 + v2;
    CPPUNIT_ASSERT(add==VecteurR3(3,5,7));
}

void testsVecteurR3::testSoustraction(void) {
    VecteurR3 sub = v1 - v2;
    CPPUNIT_ASSERT(sub==VecteurR3(-1,-1,-1));
}

void testsVecteurR3::testMulti(void) {
    CPPUNIT_ASSERT(v1.multi(v2)==VecteurR3(2,6,12));
}

void testsVecteurR3::testDiv(void) {
    CPPUNIT_ASSERT(v1.div(v2)==VecteurR3(1/2.,2/3.,3/4.));
}

void testsVecteurR3::testProdScal(void) {
    CPPUNIT_ASSERT((v1*v2)==(2+6+12));
}

void testsVecteurR3::testMultiplicationScalaire(void) {
    CPPUNIT_ASSERT(v1*2 == VecteurR3(1*2,2*2,3*2));
}

void testsVecteurR3::testIncrementation(void) {
    VecteurR3 vTemp = VecteurR3(1,1,1);
    vTemp += v2;
    CPPUNIT_ASSERT(vTemp==VecteurR3(3,4,5));
}

void testsVecteurR3::testNorme22(void) {
    CPPUNIT_ASSERT(v1.norme22()==14);
}

void testsVecteurR3::testprodVec(void) {
  CPPUNIT_ASSERT(v1.prodVec(v2)==VecteurR3(-1,2,-1));
}

void testsVecteurR3::testValeurAbsolue(void) {
  CPPUNIT_ASSERT(VecteurR3(-1,2,-3).valeurAbsolue()==v1);
}
void testsVecteurR3::testReflexionPlanOrtho(void) {
  CPPUNIT_ASSERT(VecteurR3(1,0,0).reflexionPlanOrtho(v1)==VecteurR3(-v1[0],v1[1],v1[2]));
}
