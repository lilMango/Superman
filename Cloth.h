#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <GLUT/glut.h>

#include "Particle.h"
#include "SpringDamper.h"
#include "AeroTriangle.h"
#include <vector>
#include "SceneGraph.h"
#include "VecMatrix4.h"


class Cloth:public Geode{
  const static int NUM_C_PARTS = 7;
  Particle parts[NUM_C_PARTS][NUM_C_PARTS];
  std::vector<SpringDamper> springDampers;

 public:
  Cloth();
  
  void reset();

  void draw(Matrix4);
};
