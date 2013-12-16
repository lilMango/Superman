#pragma once
#include "Particle.h"
#include "VecMatrix4.h"
#include <GLUT/glut.h>

class AeroTriangle{
 public:
  Particle *p1,*p2,*p3;
  Vector3 n;//normal
  AeroTriangle(Particle* a1,Particle* a2, Particle* a3);
  bool isResistant;
  void computeForce(Vector3);//apply Force to each Particle
  void draw();
};
