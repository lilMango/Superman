#include "Cloth.h"

Cloth::Cloth(){

  for(int j=0; j<NUM_C_PARTS; j++){
    for(int i=0; i<NUM_C_PARTS; i++){
      parts[i][j]=Particle(Vector3(i*1+0.0,j+0.0, 0.0), Vector3(),0.5);
      if(j==NUM_C_PARTS-1){
	parts[i][j].isMovable=false; //pinned to shoulders
	
      }

      printf("cloth [%d][%d]:\t",i,j);
      parts[i][j].r.print();
    }
  }

  //insert springs
  for(int j=0; j<NUM_C_PARTS; j++){
    for(int i=0; i<NUM_C_PARTS; i++){
      if(i>0 && j<(NUM_C_PARTS-1)){ //diag bottom right to top left
	springDampers.push_back(SpringDamper(&parts[i][j],&parts[i-1][j+1]));
      }
      if(j<(NUM_C_PARTS-1)){//straight up
	springDampers.push_back(SpringDamper(&parts[i][j],&parts[i][j+1]));
      }
      if(i<(NUM_C_PARTS-1) && j<(NUM_C_PARTS-1)){//bottom left to top right
	springDampers.push_back(SpringDamper(&parts[i][j],&parts[i+1][j+1]));
      }
      if(i<(NUM_C_PARTS-1)){//right across
	springDampers.push_back(SpringDamper(&parts[i][j],&parts[i+1][j]));
      }
      
    }
  }
  
  printf("springDampers size:%d\n", springDampers.size());

}

void Cloth::reset(){
  for(int j=0; j<NUM_C_PARTS-1; j++){
    for(int i=0; i<NUM_C_PARTS; i++){
      parts[i][j].reset();
    }
  }
  
}

void Cloth::draw(Matrix4 C){
  glPushMatrix();
  setModelView(C);
  
  
   //apply gravity to all
  for(int j=0; j<NUM_C_PARTS-1; j++){
    for(int i=0; i<NUM_C_PARTS; i++){
       parts[i][j].F_sum=Vector3(0, 0, -.08);
    }
  }
  

  // apply all springDamper forces
  for(std::vector<SpringDamper>::iterator it = springDampers.begin(); it!=springDampers.end(); it++){
    it->computeForce();
  }

  //apply aerodynamic per triangle
  for(int j=1; j<NUM_C_PARTS; j++){
    for(int i=1; i<NUM_C_PARTS; i++){
      if( !(i==1) && !(i==NUM_C_PARTS-1) && j>1){
	continue;
      }
      //lower triangle
      AeroTriangle at=AeroTriangle(&parts[i-1][j-1], &parts[i][j-1], &parts[i-1][j]);
      at.computeForce(Vector3(0,-1,0));
      
      //upper triangle
      AeroTriangle at2=AeroTriangle(&parts[i][j], &parts[i-1][j], &parts[i][j-1]);
      at2.computeForce(Vector3(0,-1,0));
    }
  }
  
  


  //integrate all forces!
  for(int j=0; j<NUM_C_PARTS; j++){
    for(int i=0; i<NUM_C_PARTS; i++){
      parts[i][j].update(.03);
    }
  }


  

  //center
  glTranslatef(-NUM_C_PARTS,-NUM_C_PARTS/2,-NUM_C_PARTS/2);
  //==== Actual DRAWING ====
  if(true){//DEBUG MODE
    for(int j=0; j<NUM_C_PARTS; j++){
      for(int i=0; i<NUM_C_PARTS; i++){
	glPushMatrix();
	if(parts[i][j].F_sum.magnitude()<0){
	  glColor3f(1,0,0);
	}else if(parts[i][j].F_sum.magnitude() < 0.5){
	  glColor3f(0,1,0);
	}else{
	  glColor3f(0,0,1);
	}
	glTranslatef(parts[i][j].r[0], parts[i][j].r[1], parts[i][j].r[2]);
	glutSolidSphere(0.3,10,10);
	glPopMatrix();
      }
      glEnd();
    }
  }

  for(int j=0; j<NUM_C_PARTS-1; j++){
    glBegin(GL_TRIANGLE_STRIP);
    for(int i=0; i<NUM_C_PARTS; i++){
      glColor3f(.57,0, .1);
      glVertex3f(parts[i][j].r[0], parts[i][j].r[1], parts[i][j].r[2]);
      glVertex3f(parts[i][j+1].r[0], parts[i][j+1].r[1], parts[i][j+1].r[2]);
    }
    glEnd();
  }

    
  for(SpringDamper sp:springDampers){
    glBegin(GL_LINES);
    glVertex3f((sp.p1)->r.x,(sp.p1)->r.y, (sp.p1)->r.z);
    glVertex3f((sp.p2)->r.x,(sp.p2)->r.y, (sp.p2)->r.z);
    glEnd();
  }
 
  glPopMatrix();
}
