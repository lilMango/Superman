#pragma once
#include "Particle.h"

class SpringDamper{
  //  float k_s=.1, k_d=.1; //spring constant, dampingfactor
  float k_s=.1, k_d=.1; //spring constant, dampingfactor
  float l0=1.0;//rest length
  

 public:
  Particle *p1,*p2;

  SpringDamper(Particle *p1, Particle *p2);
  SpringDamper(Particle*,Particle*,double,double,double);
  void setKs(float,float,float);
  void computeForce();//apply to p1 and p2
  
  
};
