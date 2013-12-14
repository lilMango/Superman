#pragma once
#include "Particle.h"
#include "VecMatrix4.h"

class AeroTriangle{
 public:
  Particle *p1,*p2,*p3;

  AeroTriangle(Particle* a1,Particle* a2, Particle* a3);

  void computeForce(Vector3);//apply Force to each Particle
};
