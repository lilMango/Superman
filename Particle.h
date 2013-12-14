#pragma once
#include "VecMatrix4.h"

class Particle{
 public:
  Vector3 r0;
  Vector3 v0;

  Vector3 r;//position
  Vector3 v;//velocity

  Vector3 F_sum;//Froce, reset and re computed per frame
  
  float m;//mass
  bool isMovable;

  Particle(){}
  Particle(Vector3 a_r,Vector3 a_v, float a_m);

  void reset();
  void update(float time);
  void draw();
  void applyForce(Vector3 tmp_f);
};
