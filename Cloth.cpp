#include "Cloth.h"

Cloth::Cloth(){

  for(int j=0; j<NUM_C_PARTS; j++){
    for(int i=0; i<NUM_C_PARTS; i++){
      parts[i][j]=Particle(Vector3(i*1.0,0.0, -j), Vector3(),0.5);
      if(j==0){
	parts[i][j].isFixed=true; //pinned to shoulders
	
      }

      printf("cloth [%d][%d]:\t",i,j);
      parts[i][j].r.print();
    }
  }

  //insert springs
  for(int j=0; j<NUM_C_PARTS; j++){
    for(int i=0; i<NUM_C_PARTS; i++){
      //TODO so DIAG springs are useless..
      if(i>0 && j<(NUM_C_PARTS-1)){ //diag bottom right to top left
	//springDampers.push_back(SpringDamper(&parts[i][j], &parts[i-1][j+1], .1, .1, 1.4));
      }
      if(j<(NUM_C_PARTS-1)){//straight up
	springDampers.push_back(SpringDamper(&parts[i][j], &parts[i][j+1]));
      }
      if(i<(NUM_C_PARTS-1) && j<(NUM_C_PARTS-1)){//bottom left to top right
	//springDampers.push_back(SpringDamper(&parts[i][j], &parts[i+1][j+1], .1, .1, 1.4));
      }
      if(i<(NUM_C_PARTS-1)){//right across
	springDampers.push_back(SpringDamper(&parts[i][j], &parts[i+1][j]));
      }
      
    }
  }
  
  printf("springDampers size:%d\n", springDampers.size());

  //apply aerotriangles
  for(int j=1; j<NUM_C_PARTS; j++){
    for(int i=1; i<NUM_C_PARTS; i++){
      //lower triangle
      AeroTriangle at=AeroTriangle(&parts[i-1][j-1], &parts[i-1][j], &parts[i][j-1]);

      //upper triangle
      AeroTriangle at2=AeroTriangle(&parts[i][j], &parts[i][j-1], &parts[i-1][j]);

      if( !(i==1) && !(i==NUM_C_PARTS-1) && j>1){
	//TODO make resistant where body part block air drag
	//at.isResistant=true;
	//at2.isResistant=true;
      }
      
      triangles.push_back(at);
      triangles.push_back(at2);
    }
  }

}

void Cloth::reset(){
  for(int j=0; j<NUM_C_PARTS; j++){
    for(int i=0; i<NUM_C_PARTS; i++){
      parts[i][j].reset();
    }
  }
  
}

void Cloth::draw(Matrix4 C){
  glPushMatrix();
  setModelView(C);
  
  
   //apply gravity to all
  for(int j=0; j<NUM_C_PARTS; j++){
    for(int i=0; i<NUM_C_PARTS; i++){
       parts[i][j].F_sum=Vector3(0, 0, -.98);
    }
  }
  

  // apply all springDamper forces
  for(std::vector<SpringDamper>::iterator it = springDampers.begin(); it!=springDampers.end(); it++){
    it->computeForce();
  }
 
  

  //apply air force
  for(std::vector<AeroTriangle>::iterator it=triangles.begin(); it!=triangles.end();it++){
    it->computeForce(Vector3(3,-1,0));
  }
  

  //integrate all forces!
  for(int j=0; j<NUM_C_PARTS; j++){
    for(int i=0; i<NUM_C_PARTS; i++){
      parts[i][j].update(.03);
    }
  }


  //center
  glTranslatef(-NUM_C_PARTS/2, -NUM_C_PARTS/2, NUM_C_PARTS/2);
  //==== Actual DRAWING ====
  if(DEBUG){//DEBUG MODE
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

    for(SpringDamper sp:springDampers){
      glBegin(GL_LINES);
      glVertex3f((sp.p1)->r.x,(sp.p1)->r.y, (sp.p1)->r.z);
      glVertex3f((sp.p2)->r.x,(sp.p2)->r.y, (sp.p2)->r.z);
      glEnd();
    }
    
  }
 
  glColor3f(.57,0,.1);
  for(AeroTriangle t:triangles){
    t.draw();
  }
    
 
  glPopMatrix();
}
