#include <stdio.h>
#include<string>
#include <stdlib.h>
#include <iostream>
#include <GLUT/glut.h>
#include "Camera.h"
#include "ReadObjGlobals.h"
#include "light.h"
#include "shader.h"
#include "SceneGraph.h"
#include "CityBuilder.h"
#include "fps.h"
#include "SOIL.h"
#include "Frustum.h"
#include "MyWindow.h"
#include "Particle.h"
#include "SpringDamper.h"
#include "AeroTriangle.h"
#include "Cloth.h"
#include "Mesh3D.h"

void mouseClick(int,int,int,int);
void mouseDrag(int,int);
void drawObj();
void changeObj();
void drawCube();
void drawPlane();
void drawCape();
void drawMiniScene();
void drawObj();
void buildSceneGraph();
unsigned char* loadPPM(const char* filename, int& width, int& height);
void loadTexture();
void drawSkybox();
void initSkybox();
using namespace std;


int pgmWidth,pgmHeight;

Building *oneBuilding=new Building(0,10,10,10);

//static Camera* camPtr=new Camera(0,10,10,  0,0,0,		 0,1,0		); //left corner top
static Camera* camPtr=new Camera(0,7,1,  0,7,0,	 0,1,0		); //camera for facing front OBJ drawings
//static Camera* camPtr=new Camera(0,-1,7,  0,0,7,	 0,0,1		); //camera for facing front OBJ drawings
Matrix4* Mobj2world=new Matrix4();
bool isDragging=false;
int prevXpix=0,prevYpix=0;
bool isScaling=false;
float scaleFactor=1;
int prevScaleDrag=0;//keep track of delta mouse drags
bool isPaused=false;

float *colors;;//pointer to colors array
bool isSpin=false;
bool isAdjust=true;
bool keepDrawing=false; //tell whether to redraw or not
bool moveObject=true;
bool isShader=true;
bool soloMode=false;

int shaderIdx=0;
Shader* shad;
Shader* tripShad, *waveShad, *inceptionShad, *skyboxShad, *envMapShad;
Mesh3D* boxMesh=new Mesh3D(1);//vao=1
Light *pointLight = new Light(0, 10, 20,0,
			      1,1,1,1);

int Window::width=512;int Window::height=512;

Frustum* frustum=new Frustum(100.0, Window::width/Window::height, 10.0, 1000);
int Node::S_HELLO=0;
Frustum* Node::FRUSTUM=frustum;
bool Node::DO_FRUSTUM_CULLING=true;
bool Node::SHOW_FRUSTUM=false;
bool Cloth::DEBUG=true;
MatrixTransform *world = new MatrixTransform();

Fps* fps= new Fps();

time_t startTime;
float mytimer=0.0; // use for fake time counter

const int NUM_TEXTURES=2;
GLuint textures[NUM_TEXTURES];
GLuint mytextureo;

void setModelView(Matrix4 C){
  
  glMatrixMode(GL_MODELVIEW);
  Matrix4 CM=camPtr->getCameraMatrix();
  CM=C*CM;
  glLoadMatrixd(CM.getPointer());
}



//---------------------------------------------------------------------------- 
//method when Mouse is clicked 
void mouseClick(int button, int state, int x, int y) { 
  isDragging = 1; 

  
  if(button == GLUT_LEFT_BUTTON) { 
    if(state == GLUT_DOWN) { 
  
      prevXpix=x;prevYpix=y; 
              
    }//end if GLUT_DOWN 
    else
      isDragging = 0; 
  }//end if GLUT_LEFT_button 
  
  //SCALING 
  else if(button == GLUT_RIGHT_BUTTON) { 
    if(state == GLUT_DOWN) { 
      isDragging=1; 
      isScaling=1; 
      //for scaling 
      prevScaleDrag=y; 
    }//end if GLUT_DOWN 
    else { 
      isDragging=0;isScaling=0; 
    } 
  }//end if button GLUT_RIGHT_BUTTON 
}//end mouseClick() 
  
//---------------------------------------------------------------------------- 
//method when user drags mouse and a mouse Button at the same  
void mouseDrag(int x, int y) { 
  
  if(isDragging) { 
    if(isScaling){ 

      float diff=prevScaleDrag-y;//diff<0 scale down 
      //diff>0 scale up 
      //diff/100;//to lower sensitivity 
      if(diff<0){ //zoom out
	camPtr->zoomOut();

	if(soloMode){
	  scaleFactor-=.1;
	}
      } 
      else { //zoom in
	camPtr->zoomIn();
	
	if(soloMode){
	  scaleFactor+=.1;
	}
      } 
      
      if(scaleFactor<0)scaleFactor=.1;//.5 is lowest before matrix manipulations prodcut goes to 0\
      else if(scaleFactor>20)scaleFactor=20;


              
      prevScaleDrag=y; 
      drawObj(); 
    }else{//rotation 
      if(moveObject)
	Mobj2world->trackballRotation(Window::width,Window::height,prevXpix,prevYpix,x,y);
      
      //save end vector to start vector for next iteration 
      prevXpix=x;prevYpix=y; 
  
      drawObj(); 
    }//end rotating 
  }//end fi isDragging 
      
}//end mouseDrag() 
  
void drawCube(){

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D,textures[1]);//TODO can change to textures[1] for diff img of PPM, textures[0] is SOIL's
  // Draw sides of cube in object coordinate system:
  glBegin(GL_QUADS);
  //glColor3f(139.0f/256.0f,  119.0f/256.0f,   101.0f/256.0f);
  glColor3f(1,1,1);
  glTexCoord2f(0, 1); glVertex3f(-2, -1, 0);
  glTexCoord2f(1, 1); glVertex3f(2, -1, 0);
  glTexCoord2f(1, 0); glVertex3f(2, 1, 0);
  glTexCoord2f(0, 0); glVertex3f(-2, 1, 0);
  glEnd();

}//end drawCube()

void drawPlane(){
  const float DIM=500.0f;
  const float DELTA=DIM/100.0f;
  glColor3f(1,0,0);

  for(float y=-DIM; y<DIM; y+=DELTA){
    //glBegin(GL_TRIANGLE_STRIP);
	glBegin(GL_POINTS);glPointSize(1);
    for(float x=-DIM; x<DIM; x+=DELTA){
      glNormal3f(0,1,0);      
            glVertex2f(x,y);
	    //    glVertex3f(x,y,0);
	    //glVertex3f(x,y+DELTA,0);
    }
    glEnd();
  }//end forx
  
}//end drawPlane()

Cloth* cape=new Cloth();  
void drawCape(){
  Matrix4 M=Matrix4(1,0,0,0,
		    0,1,0,0,
		    0,0,1,0,
		    0,0,0,1);
  cape->draw(M);
}

 
void drawMiniScene(){


  const float DIM=2000.0f;
  const float DELTA=DIM/100.0f;
  
  
  for(float y=-DIM/10; y<DIM/10; y+=10){
    int xCount=0;
    for(float x=-DIM/10; x<DIM/10; x+=20){
      xCount++;
       glPushMatrix();
       glTranslatef(x,y,0);
       if(y>100){
	 if(xCount==4){
	   xCount=0;

	   for(int z=0;z<100;z+=7){
	     glPushMatrix();
	     glTranslatef(0,0,z);
	     glColor3f(1,0,1);
	     glutSolidCube(7.0);
	     glPopMatrix();
	     
	     if(z==0){
	       
	       Matrix4 tm=Matrix4(1,0,0,0,
				  0,1,0,0,
				  0,0,1,0,
				  0,0,5,1);
	       oneBuilding->draw(tm);
	     }
	   }
	   
	 }
       }
       else{
	 glColor3f(0,1,0);
	 glutSolidSphere(1.5,20,20);
       }
       glPopMatrix();
    }
  }//end forx
  
 
 }

unsigned char* loadPPM(const char* filename, int& width, int& height){

  const int BUFSIZE = 128;
  FILE* fp;
  unsigned int read;
  unsigned char* rawData;
  char buf[3][BUFSIZE];
  char* retval_fgets;
  size_t retval_sscanf;

  if ( (fp=fopen(filename, "rb")) == NULL)
    {
      std::cerr << "error reading ppm file, could not locate " << filename << std::endl;
      width = 0;
      height = 0;
      return NULL;
    }

  // Read magic number:
  retval_fgets = fgets(buf[0], BUFSIZE, fp);

  // Read width and height:
  do
    {
      retval_fgets=fgets(buf[0], BUFSIZE, fp);
    } while (buf[0][0] == '#');
  retval_sscanf=sscanf(buf[0], "%s %s", buf[1], buf[2]);
  width  = atoi(buf[1]);
  height = atoi(buf[2]);

  // Read maxval:
  do
    {
      retval_fgets=fgets(buf[0], BUFSIZE, fp);
    } while (buf[0][0] == '#');

  // Read image data:
  rawData = new unsigned char[width * height * 3];
  read = fread(rawData, width * height * 3, 1, fp);
  fclose(fp);
  if (read != 1)
    {
      std::cerr << "error parsing ppm file, incomplete data" << std::endl;
      delete[] rawData;
      width = 0;
      height = 0;
      return NULL;
    }

  return rawData;
}//end loadPPM

  //http://stackoverflow.com/questions/8866904/need-help-understanding-the-differences-and-relationship-between-glactivetexture
//const int NUM_TEXTURES=2;
//GLuint textures[NUM_TEXTURES];
//GLuint mytexture;
void loadTexture(){
  //  glGenTextures(NUM_TEXTURES, &textures[0]);  
 printf("HEHEHE\n");
 ////using the SOIL function one shot function
 glActiveTexture(GL_TEXTURE0+0);
 glBindTexture(GL_TEXTURE_2D, textures[0]);
 textures[0] = SOIL_load_OGL_texture
   //mytexture= SOIL_load_OGL_texture
      (
       //"smiley.png",
       "explosion.png",
       SOIL_LOAD_AUTO,
       //textures[0],       
         SOIL_CREATE_NEW_ID,

      SOIL_FLAG_MIPMAPS
              | SOIL_FLAG_TEXTURE_RECTANGLE 
       //| SOIL_FLAG_NTSC_SAFE_RGB 
       //| SOIL_FLAG_COMPRESS_TO_DXT
       );
    

  for(int i=1;i<NUM_TEXTURES;i++){
    //glActiveTexture(GL_TEXTURE0+1);
    glBindTexture(GL_TEXTURE_2D, textures[i]);  
   

    int twidth, theight;
    unsigned char* tdata;
    
    //tdata = loadPPM("explosion.ppm", twidth, theight);
    tdata = loadPPM("baratheon.ppm", twidth, theight);
    //tdata = loadPPM("confederate.ppm", twidth, theight);
    if(tdata==NULL){
      printf("Null PPM\n");
      return;
    }    
    
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    
    glTexImage2D(GL_TEXTURE_2D, 0 , 3, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);
    delete [] tdata;

  }//end for
      
  glEnable(GL_TEXTURE_2D);
}//end loadTexture



void drawSkybox(){
  const float SB=10.0f;//has to be >10
  
  glPushMatrix();
  
  glColor3f(1,1,1);
  glDepthMask(GL_FALSE);
  glDisable(GL_LIGHTING);

  //left CCW
  glBegin(GL_TRIANGLE_STRIP);
  glVertex3f(-SB,SB,SB);
  glVertex3f(-SB,-SB,SB);
  glVertex3f(-SB,SB,-SB);
  glVertex3f(-SB,-SB,-SB);
  glEnd();

  //front
  glBegin(GL_TRIANGLE_STRIP);
  glVertex3f(-SB,SB,-SB);
  glVertex3f(-SB,-SB,-SB);
  glVertex3f(SB,SB,-SB);
  glVertex3f(SB,-SB,-SB);
  glEnd();
  
  glEnable(GL_LIGHTING);
  glDepthMask(GL_TRUE);
  glPopMatrix();
}

#define FRONT "negz.jpg"
#define BACK "posz.jpg"
#define TOP "posy.jpg"
#define BOTTOM "negy.jpg"
#define LEFT "negx.jpg"
#define RIGHT "posx.jpg"
GLuint tex_cube;
unsigned int vbo=0, vao=0;
unsigned int loc_vp_att=0;

void initSkybox(){
  float points[] = {
    -3.0f,  3.0f, -3.0f,
    -3.0f, -3.0f, -3.0f,
    3.0f, -3.0f, -3.0f,
    3.0f, -3.0f, -3.0f,
    3.0f,  3.0f, -3.0f,
    -3.0f,  3.0f, -3.0f,
  
    -3.0f, -3.0f,  3.0f,
    -3.0f, -3.0f, -3.0f,
    -3.0f,  3.0f, -3.0f,
    -3.0f,  3.0f, -3.0f,
    -3.0f,  3.0f,  3.0f,
    -3.0f, -3.0f,  3.0f,
  
    3.0f, -3.0f, -3.0f,
    3.0f, -3.0f,  3.0f,
    3.0f,  3.0f,  3.0f,
    3.0f,  3.0f,  3.0f,
    3.0f,  3.0f, -3.0f,
    3.0f, -3.0f, -3.0f,
   
    -3.0f, -3.0f,  3.0f,
    -3.0f,  3.0f,  3.0f,
    3.0f,  3.0f,  3.0f,
    3.0f,  3.0f,  3.0f,
    3.0f, -3.0f,  3.0f,
    -3.0f, -3.0f,  3.0f,
  
    -3.0f,  3.0f, -3.0f,
    3.0f,  3.0f, -3.0f,
    3.0f,  3.0f,  3.0f,
    3.0f,  3.0f,  3.0f,
    -3.0f,  3.0f,  3.0f,
    -3.0f,  3.0f, -3.0f,
  
    -3.0f, -3.0f, -3.0f,
    -3.0f, -3.0f,  3.0f,
    3.0f, -3.0f, -3.0f,
    3.0f, -3.0f, -3.0f,
    -3.0f, -3.0f,  3.0f,
    3.0f, -3.0f,  3.0f
  };
  //unsigned int vbo = 0;
  glGenBuffers (1, &vbo);
  glBindBuffer (GL_ARRAY_BUFFER, vbo);
  glBufferData (GL_ARRAY_BUFFER, 3 * 36 * sizeof (float), &points[0], GL_STATIC_DRAW);

  //unsigned int vao = 0;
  glGenVertexArraysAPPLE (1, &vao);
  glBindVertexArrayAPPLE (vao);
  glEnableVertexAttribArray (loc_vp_att);
  glBindBuffer (GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer (loc_vp_att, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);//param 0=0 means vertex positions
  //param 0 == 1 could mean color, texcoord, normals, etc

  printf(" @@@@@@@@@@ vbo: %u\n",vbo);
  printf(" @@@@@@@@@@ vao: %u\n",vao);




  ///////////

  tex_cube = SOIL_load_OGL_cubemap (
					   RIGHT,
					   LEFT,
					   TOP,
					   BOTTOM,
					   BACK,
					   FRONT,
					   SOIL_LOAD_RGB,
					   SOIL_CREATE_NEW_ID,
					   0
					   );
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  if (0 == tex_cube) {
    printf("SOIL loading error: '%s'\n", SOIL_last_result());
  }  
}//end initSkybox
