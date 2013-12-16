#include "AeroTriangle.h"

AeroTriangle::AeroTriangle(Particle* a1, Particle *a2, Particle *a3){
  p1=a1;
  p2=a2;
  p3=a3;

  n.cross((p2->r)-(p1->r), (p3->r)-(p1->r));
  n.normalize();
  isResistant=false;
}

void AeroTriangle::computeForce(Vector3 v_air){
  if(isResistant)return;

  Vector3 v_surface = ( (p1->v) + (p2->v) + (p3->v) ) * (1.0/3.0);
  Vector3 v = v_surface - v_air;
  
  Vector3 n0 = Vector3();
  n.cross((p2->r)-(p1->r), (p3->r)-(p1->r));
  n0=n;
  n.normalize();

  double a0 = 0.5 * n0.magnitude();
  double a = a0 * (v*n) * (1.0/ v.magnitude());
  
  Vector3 f_aero = n * (-0.5 * v.magnitude() * v.magnitude() * a) * (1.0/3.0);
  p1->applyForce(f_aero);
  p2->applyForce(f_aero);
  p3->applyForce(f_aero);
}

void AeroTriangle::draw(){
  glBegin(GL_TRIANGLES);
  glNormal3f(n.x, n.y, n.z);
  glVertex3f(p1->r.x, p1->r.y, p1->r.z);
  glVertex3f(p2->r.x, p2->r.y, p2->r.z);
  glVertex3f(p3->r.x, p3->r.y, p3->r.z);
  glEnd();
}
