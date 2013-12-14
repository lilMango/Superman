#include "SpringDamper.h"

SpringDamper::SpringDamper(Particle *a1, Particle *a2){
  p1=a1;
  p2=a2;

  k_s = k_d = 0.1;
  l0=1.0;
}

SpringDamper::SpringDamper(Particle *a1, Particle *a2,double s,double d, double l){
  p1=a1;
  p2=a2;

  k_s = s; 
  k_d = d;

  l0 = l;
}


void SpringDamper::setKs(float s, float d, float l){
  k_s = s; 
  k_d = d;

  l0 = l;
}

void SpringDamper::computeForce(){
  Vector3 e = (p2->r) - (p1->r);
  double l = e.magnitude();
  e.normalize();


  double v1 = e * (p1->v);
  double v2 = e * (p2->v);
  
  double f_sd = -k_s * (l0 - l) - k_d * (v1-v2);

  Vector3 f1 = e * f_sd;
  Vector3 f2 = e * (-f_sd);
  

  //apply forces to each particle
  p1 ->applyForce(f1);
  p2 ->applyForce(f2);

}
