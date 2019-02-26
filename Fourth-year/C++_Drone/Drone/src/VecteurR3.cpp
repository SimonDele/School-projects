#include "../include/VecteurR3.h"
#include <cmath>

VecteurR3::VecteurR3() {
  x=0;
  y=0;
  z=0;
}

VecteurR3::VecteurR3(const float & cx,const float & cy,const float & cz) {
  x=cx;
  y=cy;
  z=cz;
}

VecteurR3::~VecteurR3() {
  // Destructeur vide (suppression de type float géré par le langage)
}

float VecteurR3::getX() const {return x;};
float VecteurR3::getY() const {return y;};
float VecteurR3::getZ() const {return z;};

void VecteurR3::setX(const float& _x) {x=_x;};
void VecteurR3::setY(const float& _y) {y=_y;};
void VecteurR3::setZ(const float& _z) {z=_z;};

float VecteurR3::operator[](const int& index) const {
  switch (index) {
    case 0: return x;
            break;
    case 1: return y;
            break;
    case 2: return z;
            break;
    default: throw std::out_of_range ("Index hors limites (0,1 ou 2 uniquement)");
  }
}

bool VecteurR3::egal (const VecteurR3 &vComp, const float &epsilon) const {
  return((std::abs(x-vComp.getX())<epsilon)&&(std::abs(y-vComp.getY())<epsilon)
                                      &&(std::abs(z-vComp.getZ())<epsilon));
}

bool VecteurR3::operator== (const VecteurR3 &vComp) const {
  return(x==vComp.getX()&&y==vComp.getY()&&z==vComp.getZ());
}

VecteurR3 VecteurR3::operator+(const VecteurR3 &v) const {
  return(VecteurR3(x+v.getX(), y+v.getY(), z+v.getZ()));
}

VecteurR3 VecteurR3::operator-(const VecteurR3 &v) const {
  return(VecteurR3(x-v.getX(), y-v.getY(), z-v.getZ()));
}

void VecteurR3::operator=(const VecteurR3 &v) {
  x=v.getX();
  y=v.getY();
  z=v.getZ();
}

void VecteurR3::operator+=(const VecteurR3 &v) {
  x+=v.getX();
  y+=v.getY();
  z+=v.getZ();
}
void VecteurR3::operator-=(const VecteurR3 &v) {
  x-=v.getX();
  y-=v.getY();
  z-=v.getZ();
}

float VecteurR3::operator*(const VecteurR3 &v) const {
  return(x*v[0]+y*v[1]+z*v[2]);
}

VecteurR3 VecteurR3::multi(const VecteurR3 &v) const {
  return (VecteurR3(x*v[0],y*v[1],z*v[2]));
}

VecteurR3 VecteurR3::div(const VecteurR3 &v) const {
  return (VecteurR3(x/v[0],y/v[1],z/v[2]));
}

VecteurR3 VecteurR3::operator*(const float &scal) const{
  return VecteurR3(x*scal,y*scal,z*scal);
}

float VecteurR3::norme22() const {
  return(x*x+y*y+z*z);
}

float VecteurR3::norme2() const {
  return(sqrt(VecteurR3::norme22()));
}

VecteurR3 VecteurR3::prodVec(const VecteurR3 &v) const {
    return VecteurR3(y*v[2]-z*v[1],z*v[0]-x*v[2],x*v[1]-y*v[0]);
}


VecteurR3 VecteurR3::valeurAbsolue() const {
  return VecteurR3(fabs(x),fabs(y),fabs(z));
}


VecteurR3 VecteurR3::reflexionPlanOrtho(const VecteurR3& v) const {
  // return H(u).x = (I-2u'u).x
  return VecteurR3(
    v[0]*(1-2*x*x)-2*x*(y*v[1]-z*v[2]),
    v[1]*(1-2*y*y)-2*y*(x*v[0]-z*v[2]),
    v[2]*(1-2*z*z)-2*z*(x*v[0]-y*v[1])
  );
}

// Friend function
std::ostream& operator <<(std::ostream& s, const VecteurR3& v) {
  s << "(" << v[0] << "," << v[1] << "," << v[2] << ")";
  return s;
}
