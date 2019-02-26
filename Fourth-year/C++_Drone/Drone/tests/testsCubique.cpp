/*
#include "../tests/testsCubique.h"
#include "../include/VecteurR3.h"

#include<vector>

testsCubique::setUp()
{
    fCubique = new Cubique(new VecteurR3(0,0,0),1, 8);
}

testsCubique::~tearDown()
{
    delete fCubique;
}
testsCubique::testsGenererMaillage()
{
    vector<VecteurR3> maillage = fCubique.genererMaillage();
    //On verifie que la taille du vector en sortie est bonne
    CPPUNIT_ASSERT(maillage.size() == 10);
    //On verifie chaque point du cube. Ce cas particulier doit sortir tous les sommets du cube
    CPPUNIT_ASSERT(
                   find(maillage.begin(),maillage.end(),VecteurR3(1,0,0) !=maillage.end()) &&
                   find(maillage.begin(),maillage.end(),VecteurR3(1,1,0) !=maillage.end()) &&
                   find(maillage.begin(),maillage.end(),VecteurR3(1,1,1) !=maillage.end()) &&
                   find(maillage.begin(),maillage.end(),VecteurR3(0,1,0) !=maillage.end()) &&
                   find(maillage.begin(),maillage.end(),VecteurR3(0,1,1) !=maillage.end()) &&
                   find(maillage.begin(),maillage.end(),VecteurR3(0,0,1) !=maillage.end()) &&
                   find(maillage.begin(),maillage.end(),VecteurR3(1,0,1) !=maillage.end()) &&
                   find(maillage.begin(),maillage.end(),VecteurR3(0,0,0) !=maillage.end()) &&

                   );


}
*/
