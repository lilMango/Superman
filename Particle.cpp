#include "Particle.h"

void Particle::reset(){
  r=r0;
  v=v0;
}

Particle::Particle(Vector3 a_r,Vector3 a_v, float a_m){
  r0=a_r;
  v0=a_v;

  r=a_r;
  v=a_v;
  m=a_m;
}

void Particle::update(float time){
  Vector3 A= F_sum*(1/m); //acceleration

  v = v + A*time;
  r = r + v*time;

  F_sum.reset();
}

void Particle::applyForce(Vector3 tmp_f){
  F_sum = F_sum + tmp_f;
}
