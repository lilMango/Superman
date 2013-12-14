#pragma once
#include <math.h>   // include math functions, such as sin, cos, M_PI
#include <cstdarg> //for variable arguments
#include <iostream>
#include <vector>


class Vector3{

public: 
	double x,y,z;
	Vector3()							 {x=0.0;y=0.0;z=0.0;}
	Vector3(double x0,double y0,double z0)  {x=x0;y=y0;z=z0;}
	void set(double x0,double y0,double z0) {x=x0;y=y0;z=z0;}
	void set(Vector3 &a){
		x=a.x;y=a.y;z=a.z;
	}
	void set(int idx,double val){
	  switch (idx){
	  case 0: x=val;break;
	  case 1: y=val;break;
	  case 2: z=val;break;
	  default:printf("Invalid index");break;
	  }
	}

	void reset()						 {x=0.0;y=0.0;z=0.0;}
	double getX()						 {return x;}
	double getY()						 {return y;}
	double getZ()						 {return z;}
	double operator [](int arg)			 
	{
		switch(arg){
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			printf("Invalid Index");
			return -1;
		}
	}
	void add (Vector3 &a)				 {x+=a.x;y+=a.y;z+=a.z;}
	void add(Vector3 &a, Vector3 &b)	 {x=a.x+b.x;y=a.y+b.y;z=a.z+b.z;}
	Vector3 operator + (Vector3 a)		
	{
	  return Vector3(x+a.x, y+a.y, z+a.z);
	}
	void subtract(Vector3 &a)			 {x-=a.x;y-=a.y;z-=a.z;}
	void subtract(Vector3 &a,Vector3 &b) {x=a.x-b.x;y=a.y-b.y;z=a.z-b.z;}


	Vector3 operator - (Vector3 a)		 {
	  return Vector3(x-a.x,y-a.y,z-a.z);
	}

	void negate()						 {x=-x;y=-y;z=-z;}
	void negate(Vector3 &a)				 {x=-a.x;y=-a.y;z=-a.z;}
	Vector3 scale(double s)					 {return Vector3(x*s,y*s,z*s);}
	double dot(Vector3 a)				 {return x*a.x+y*a.y+z*a.z;}
	double operator * (Vector3 a){
	  return dot(a);
	}
	void cross(Vector3 a, Vector3 b)   
	{
		x=a.y*b.z-a.z*b.y;
		y=a.z*b.x-a.x*b.z;
		z=a.x*b.y-a.y*b.x;
	}
	Vector3 cross(Vector3 b){
  		double xn=y*b.z-z*b.y;
		double yn=z*b.x-x*b.z;
		double zn=x*b.y-y*b.x;
		return Vector3(xn,yn,zn);

	}
	Vector3 operator * (double fa){
	  return Vector3(x*fa, y*fa, z*fa);
	}
	
	double magnitude()					 {return sqrt(x*x+y*y+z*z);}
	void normalize()					
	{
		if(x==0 && y==0 && z==0)
			return;
		else
		scale(1.0/magnitude());
	}

	void print()				{
		printf("x=%4.3f y=%4.3f z=%4.3f\n",x,y,z);
	}
};
///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////Vector 3/////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

class Vector4{ //Points have nonzero w

public: 
	double x,y,z;
	double w;//scale factor

	Vector4()							 {x=0.0;y=0.0;z=0.0; w=0.0;}
	Vector4(double x0,double y0,double z0)  {x=x0;y=y0;z=z0; w=1;}
	Vector4(double x0,double y0,double z0,double w0)  {x=x0;y=y0;z=z0; w=w0;}
	Vector4(const double arr[4])
	{
		x=arr[0];y=arr[1];z=arr[2];w=arr[3];
	}
	Vector4(const float arr[4])
	{
		x=arr[0];y=arr[1];z=arr[2];w=arr[3];
	}

	Vector4(int arr[4]){
		x=arr[0];y=arr[1];z=arr[2];w=arr[3];
	}
	void set(int idx,double val){
	  switch (idx){
	  case 0: x=val;break;
	  case 1: y=val;break;
	  case 2: z=val;break;
	  case 3: w=val;break;
	  default:printf("Invalid index");break;
	  }
	}

	void set(double x0,double y0,double z0,double w0) {x=x0;y=y0;z=z0;w=w0;}
	double getX()						 {return x;}
	double getY()						 {return y;}
	double getZ()						 {return z;}
	double getW()						 {return w;}
	double operator [](int arg)			 
	{
		//column major order
		switch(arg){
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;
		default :
			printf("Invalid index");return x;
			return -1;
		}
		
	}

	void add (Vector4 &a)				 
	{
		x+=a.x;
		y+=a.y;
		z+=a.z;
		w+=a.w;
	}
	void add(Vector4 &a, Vector4 &b)	 
	{
		x=a.x+b.x;
		y=a.y+b.y;
		z=a.z+b.z; 
		w=a.w+b.w;
	}
	void operator + (Vector4 &a)		
	{
		x+=a.x;
		y+=a.y;
		z+=a.z; 
		w+=a.w;
	}

	void subtract (Vector4 &a)				 {x-=a.x;y-=a.y;z-=a.z;w-=a.w;}
	void subtract(Vector4 &a, Vector4 &b)	 {x=a.x-b.x;y=a.y-b.y;z=a.z-b.z; w=a.w-b.w;}
	Vector4 operator - (Vector4 &a)		
	{
		return Vector4(x-a.x,y-a.y,z-a.z,1);
	}

	void dehomogenize()						
	{
		if(!isVector()){
			x/=w;
			y/=w;
			z/=w; 
			w/=w;
		}
	}
	void print()							{ printf("[x=%4.3f y=%4.3f z=%4.3f w=%4.3f]\n",x,y,z,w);}

	Vector4 scale(double s)					 {
		return Vector4(x*s,y*s,z*s,w);
	}
	double magnitude()					 {return sqrt(x*x+y*y+z*z);}
	void normalize()					 {scale(1.0/magnitude());}



	bool isVector()
	{ return w==0.0;}

	double operator * (Vector4 a){
	  return dot(a);
	}
	double dot(Vector4 a)
	{
		return x*a.x+y*a.y+z*a.z+w*a.w;
	}
	Vector4 cross( Vector4 b)   
	{
		x=y*b.z-z*b.y;
		y=z*b.x-x*b.z;
		z=x*b.y-y*b.x;
		return Vector4(x,y,z,1);
	}

	Vector3 toVector3(){
		return Vector3(x,y,z);
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Matrix4{

public:		


	double M[4][4];	
	
	//makes identity matrix
	Matrix4(){
		for (int i=0;i<4;i++)
		{
		  for(int j=0;j<4;j++){
		    M[i][j]=0;
		  }
		}//end for
		M[0][0]=M[1][1]=M[2][2]=M[3][3]=1.0f;

	}
	
	Matrix4(double arg[16]){
	  int k=0;
	  for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
		  M[i][j]=arg[k];
		  k++;
		}
	  }
	}

	
	Matrix4(double arg[4][4]){
	  for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
		  M[i][j]=arg[i][j];
		}
	  }
	  
	}
	//parameter row order, insertion is row order
	Matrix4(double a0,double a1,double a2,double a3,
			double a4,double a5,double a6,double a7,
			double a8,double a9,double a10,double a11,
			double a12,double a13,double a14,double a15){

	  /*
	       M[0][0]=a0;  M[1][0]=a1;   M[2][0]=a2;    M[3][0]=a3;
		   M[0][1]=a4;  M[1][1]=a5;   M[2][1]=a6;    M[3][1]=a7;
		   M[0][2]=a8;  M[1][2]=a9;   M[2][2]=a10;   M[3][2]=a11;
		   M[0][3]=a12; M[1][3]=a13;  M[2][3]=a14;   M[3][3]=a15;
	   */
	       M[0][0]=a0;  M[0][1]=a1;   M[0][2]=a2;    M[0][3]=a3;
		   M[1][0]=a4;  M[1][1]=a5;   M[1][2]=a6;    M[1][3]=a7;
		   M[2][0]=a8;  M[2][1]=a9;   M[2][2]=a10;   M[2][3]=a11;
		   M[3][0]=a12; M[3][1]=a13;  M[3][2]=a14;   M[3][3]=a15;
	   

	}
	
//	data:(0) (1)  (2)  (3)

//		 [0],[4] ,[8] ,[12]
//		 |1| |5|  |9|  |13|
//		 |2| |6|  |10| |14|
//		 [3] [7]  [11] [15]

	Matrix4(Vector3& a0,Vector3& a1,Vector3& a2, Vector3& a3) //(each arg is a column)
	{
			  M[0][0]=a0[0];  M[0][1]=a1[0];   M[0][2]=a2[0];    M[0][3]=a3[0];
			  M[1][0]=a0[1];  M[1][1]=a1[1];   M[1][2]=a2[1];    M[1][3]=a3[1];
			  M[2][0]=a0[2];  M[2][1]=a1[2];   M[2][2]=a2[2];    M[2][3]=a3[2];
			  M[3][0]=0;	  M[3][1]=0;       M[3][2]=0;		 M[3][3]=1;
	}
	Matrix4(Vector4& a0,Vector4& a1,Vector4& a2, Vector4& a3) //(each arg is a column)
	{
			  M[0][0]=a0[0];  M[0][1]=a1[0];   M[0][2]=a2[0];    M[0][3]=a3[0];
			  M[1][0]=a0[1];  M[1][1]=a1[1];   M[1][2]=a2[1];    M[1][3]=a3[1];
			  M[2][0]=a0[2];  M[2][1]=a1[2];   M[2][2]=a2[2];    M[2][3]=a3[2];
			  M[3][0]=a0[3];  M[3][1]=a1[3];   M[3][2]=a2[3];	 M[3][3]=a3[3];
	}


	void set(double a0,double a1,double a2,double a3,
			double a4,double a5,double a6,double a7,
			double a8,double a9,double a10,double a11,
			double a12,double a13,double a14,double a15){

	  /*
	       M[0][0]=a0;  M[1][0]=a1;   M[2][0]=a2;    M[3][0]=a3;
		   M[0][1]=a4;  M[1][1]=a5;   M[2][1]=a6;    M[3][1]=a7;
		   M[0][2]=a8;  M[1][2]=a9;   M[2][2]=a10;   M[3][2]=a11;
		   M[0][3]=a12; M[1][3]=a13;  M[2][3]=a14;   M[3][3]=a15;
	   */
	       M[0][0]=a0;  M[0][1]=a1;   M[0][2]=a2;    M[0][3]=a3;
		   M[1][0]=a4;  M[1][1]=a5;   M[1][2]=a6;    M[1][3]=a7;
		   M[2][0]=a8;  M[2][1]=a9;   M[2][2]=a10;   M[2][3]=a11;
		   M[3][0]=a12; M[3][1]=a13;  M[3][2]=a14;   M[3][3]=a15;

	}//end set()


	void set(Vector3& a0,Vector3& a1,Vector3& a2, Vector3& a3) //(each arg is a column)
	{
			  M[0][0]=a0[0];  M[0][1]=a1[0];   M[0][2]=a2[0];    M[0][3]=a3[0];
			  M[1][0]=a0[1];  M[1][1]=a1[1];   M[1][2]=a2[1];    M[1][3]=a3[1];
			  M[2][0]=a0[2];  M[2][1]=a1[2];   M[2][2]=a2[2];    M[2][3]=a3[2];
			  M[3][0]=0;	  M[3][1]=0;       M[3][2]=0;		 M[3][3]=1;
	}//end set

	void setIdentity(){
			  M[0][0]=1;  M[0][1]=0;   M[0][2]=0;    M[0][3]=0;
			  M[1][0]=0;  M[1][1]=1;   M[1][2]=0;    M[1][3]=0;
			  M[2][0]=0;  M[2][1]=0;   M[2][2]=1;    M[2][3]=0;
			  M[3][0]=0;  M[3][1]=0;   M[3][2]=0;    M[3][3]=1;
		
	}//end setIdentity()

	//address to first element of the matrix
	double * getPointer()
	{
		return &M[0][0];
	}
	
	double get(int x,int y){
	  return M[x][y];
	}
	
	void set(int x,int y, double val){
	  M[x][y]=val;
	}
	
	// Matrix by Matrix multiplication
	Matrix4 multiply(Matrix4 a)
	{ 
	  Matrix4 product=Matrix4();
	  
	  for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
		  double sum=0;
			
		  for(int k=0;k<4;k++){

			sum+=(M[i][k]*a.get(k,j));

		  }
		  product.set(i,j,sum);
		}
	  }
		return product;
	}//end MatrixMultiply
	Matrix4 operator * (Matrix4 a)		
	{
		return multiply(a);
	}
	Vector4 operator * (Vector4 a)		
	{
		return multiply(a);
	}

// Matrix by vector multiplication
//		4x[4|4]x1 = 4x1 
	Vector4 multiply(Vector4 a)
	{
	  Vector4 product=Vector4();

	  for(int i=0;i<4;i++){
		double sum=0;
		for(int k=0;k<4;k++){
		  sum+=M[i][k]*a[k];
		}
		product.set(i,sum);
	  }
	  return product;

	}//end M*V


	//Ra--rotateArbitrary
	Matrix4 Ra(double a0,double a1,double a2,double theta)
	{
		Vector4 a=Vector4(a0,a1,a2);		
		a.normalize();
		double ax=a.getX();
		double ay=a.getY();
		double az=a.getZ();
		
		return Matrix4(
				ax*ax+cosf(theta)*(1-ax*ax),ax*ay*(1-cosf(theta))-az*sinf(theta),ax*az*(1-cosf(theta))+ay*sinf(theta),0,
				ax*ay*(1-cosf(theta))+az*sinf(theta),ay*ay+cosf(theta)*(1-ay*ay),ay*az*(1-cosf(theta))-ax*sinf(theta),0,
				ax*az*(1-cosf(theta))-ay*sinf(theta),ay*az*(1-cosf(theta))+ax*sinf(theta),az*az+cosf(theta)*(1-az*az),0,
				0,0,0,1);

	}//end Ra

	//Tr--translate
	Matrix4 Tr(double tx,double ty,double tz)
	{		
		return Matrix4(
				1,0,0,tx,
				0,1,0,ty,
				0,0,1,tz,
				0,0,0,1);
	}//end translate

	//this=a 
	void assign(Matrix4 a) 
	{ 
	  for (int i=0;i<4;i++){ 
	    for(int j=0;j<4;j++){ 
	      set(i,j,a.get(i,j)); 
	    }//end for i 
	  }//end for j 
	}//end assign 


	//rotateArbitrary
	void rotateArbitrary(double a0,double a1,double a2,double theta)
	{
		Vector4 a=Vector4(a0,a1,a2);		
		a.normalize();
		double ax=a.getX();
		double ay=a.getY();
		double az=a.getZ();
		


		Matrix4 Ra=Matrix4(
				ax*ax+cosf(theta)*(1-ax*ax),ax*ay*(1-cosf(theta))-az*sinf(theta),ax*az*(1-cosf(theta))+ay*sinf(theta),0,
				ax*ay*(1-cosf(theta))+az*sinf(theta),ay*ay+cosf(theta)*(1-ay*ay),ay*az*(1-cosf(theta))-ax*sinf(theta),0,
				ax*az*(1-cosf(theta))-ay*sinf(theta),ay*az*(1-cosf(theta))+ax*sinf(theta),az*az+cosf(theta)*(1-az*az),0,
				0,0,0,1);
		
				//		assign(Ra.multiply(Matrix4(M)));
		assign(Ra*Matrix4(M));

	}//end rotateArbitrary

	void scale(double sx,double sy,double sz)
	{
		Matrix4 Sc=  Matrix4(
			sx,0,0,0,
			0,sy,0,0,
			0,0,sz,0,
			0,0,0,1);
			
		assign(Sc.multiply(Matrix4(M)));
		//assign(Matrix4(M)*Sc);
	}//end scale

	void translate(double tx,double ty,double tz)
	{		
		Matrix4 Tr=Matrix4(
				1,0,0,tx,
				0,1,0,ty,
				0,0,1,tz,
				0,0,0,1);
		
		assign(Tr.multiply(Matrix4(M)));

	}//end translate

	
	void print(){
		printf("\n{\n");

		for(int i=0;i<3;i++){
		  
		}
		printf("[%4.1f, %4.1f, %4.1f, %4.1f],\n", M[0][0],M[0][1],M[0][2],M[0][3]);
		printf("[%4.1f, %4.1f, %4.1f, %4.1f],\n", M[1][0],M[1][1],M[1][2],M[1][3]);
		printf("[%4.1f, %4.1f, %4.1f, %4.1f],\n", M[2][0],M[2][1],M[2][2],M[2][3]);
		printf("[%4.1f, %4.1f, %4.1f, %4.1f],\n", M[3][0],M[3][1],M[3][2],M[3][3]);
		printf("}\n");

	}

	Matrix4 transpose()
	{

		Matrix4 res=Matrix4();

		for(int i=0;i<4;i++){
		  for(int j=0;j<4;j++){
			res.set(j,i,M[i][j]);
		  }
		}

		return res;
	}//end transpose()

	void copyRot(Matrix4 m){

		for(int i=0;i<3;i++){
		  for(int j=0;j<3;j++){
		    M[i][j]=m.get(i,j);
		  }
		}
	M[3][0]=M[3][1]=M[3][2]=0;
	M[0][3]=M[1][3]=M[2][3]=0; M[3][3]=1;
	}
	
	//http://harinadha.wordpress.com/tag/model-view-matrix-inverse/
	/*

		C = a b c d
		    e f y x
			2 3 4 5
			0 0 0 1
			
		R = a b c 0 
		     e f y 0 
			 2 3 4 0
			 0 0 0 1

		T^-1 = 1 0 0 -d 
		     0 1 0 -x 
			 0 0 1 -5 
			 0 0 0 1
		C^-1 = (T^-1) ' * R
		R * T = C
	*/
	Matrix4 inverseM()
	{
	  Matrix4 T_inv=Matrix4(1,0,0,-M[0][3],
							0,1,0,-M[1][3],
							0,0,1,-M[2][3],
							0,0,0,1);
							//							-M[0][3], -M[1][3],-M[2][3],1);

	  Matrix4 R=Matrix4(M[0][0],M[0][1],M[0][2],0,
							M[1][0],M[1][1],M[1][2],0,
							M[2][0],M[2][1],M[2][2],0,
							0,0,0,1);

	  return T_inv.transpose()*R;
   
	}//end inverseM()
	

	
	void trackballRotation(int width,int height,int fromX,int fromY,int toX,int toY){
	  const float TRACKBALL_SIZE=1.3f;
	  float smallSize;
	  float halfWidth=(float)width/2.0f,halfHeight=(float)height/2.0f;
	  float d;//distance
      
      
	  smallSize=halfWidth<halfHeight? halfWidth:halfHeight;
	  Vector3 v1,v2;
	  v1.set(0, ((float)fromX-halfWidth)/smallSize);
	  v1.set(1, ((float)(height-fromY)-halfHeight)/smallSize);
      
	  v2.set(0, ((float)toX-halfWidth)/smallSize);
	  v2.set(1, ((float)(height-toY)-halfHeight)/smallSize);

	  d = sqrtf(v1[0]*v1[0]+v1[1]*v1[1]);
	  v1.set(2, expf(-TRACKBALL_SIZE*d*d));
	  d = sqrtf(v2[0]*v2[0]+v2[1]*v2[1]);
	  v2.set(2, expf(-TRACKBALL_SIZE*d*d));


	  //A dot B=ABcos theta=|A||B|cos theta 
	  double magA=v1.magnitude(); 
	  double magB=v2.magnitude(); 
	  double AdotB=v1*v2; 

	  //get cross product of start and end vector to get AXIS to revolve around 
	  Vector3 vA;
	  vA.cross(v1,v2); 
	  vA.normalize(); 
              
	  //cos theta=(A dot B)/(|A||B|) 
	  double theta=acos(AdotB/(magA*magB));//radians 
	  theta=theta*180.00/3.14159;//degrees 
	  theta=theta/20;//so trackball isn't so sensitive 
	  
	  Matrix4 mInv;
	  mInv.setIdentity();
	  mInv.copyRot(*this);
	  //mInv=mInv.transpose();
	  Vector4 vB;
	  vB=(mInv*Vector4(vA[0],vA[1],vA[2],0));
	  vB.normalize();
	  rotateArbitrary(vB[0],vB[1],vB[2],-theta); 
	  


	   
	}//end trackBallRotation()

	
}; //end class Matrix4



//////////////////////// Matrix3x3 begin /////////////////
class Matrix3{

public:		


	double M[3][3];	
	
	//makes identity matrix
	Matrix3(){
		for (int i=0;i<3;i++)
		{
		  for(int j=0;j<3;j++){
		    M[i][j]=0;
		  }
		}//end for
		M[0][0]=M[1][1]=M[2][2]=1.0f;

	}
	
	Matrix3(double arg[9]){
	  int k=0;
	  for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
		  M[i][j]=arg[k];
		  k++;
		}
	  }
	}

	
	Matrix3(double arg[3][3]){
	  for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
		  M[i][j]=arg[i][j];
		}
	  }
	  
	}
	//parameter row order, insertion is row order
	Matrix3(double a0,double a1,double a2,
		double a4,double a5,double a6,
		double a8,double a9,double a10){

	       M[0][0]=a0;  M[0][1]=a1;   M[0][2]=a2; 
		   M[1][0]=a4;  M[1][1]=a5;   M[1][2]=a6;
		   M[2][0]=a8;  M[2][1]=a9;   M[2][2]=a10;
	}
	
//	data:(0) (1)  (2)  (3)

//		 [0],[4] ,[8] ,[12]
//		 |1| |5|  |9|  |13|
//		 |2| |6|  |10| |14|
//		 [3] [7]  [11] [15]

	void set(double a0,double a1,double a2,
		 double a4,double a5,double a6,
		 double a8,double a9,double a10){


	       M[0][0]=a0;  M[0][1]=a1;   M[0][2]=a2;  
	       M[1][0]=a4;  M[1][1]=a5;   M[1][2]=a6; 
	       M[2][0]=a8;  M[2][1]=a9;   M[2][2]=a10;

	}//end set()

	void setIdentity(){
			  M[0][0]=1;  M[0][1]=0;   M[0][2]=0;
			  M[1][0]=0;  M[1][1]=1;   M[1][2]=0;
			  M[2][0]=0;  M[2][1]=0;   M[2][2]=1;
		
	}//end setIdentity()

	//address to first element of the matrix
	double * getPointer()
	{
		return &M[0][0];
	}
	
	double get(int x,int y){
	  return M[x][y];
	}
	
	void set(int x,int y, double val){
	  M[x][y]=val;
	}
	
	// Matrix by Matrix multiplication
	Matrix3 multiply(Matrix3 a)
	{ 
	  Matrix3 product=Matrix3();
	  
	  for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
		  double sum=0;
			
		  for(int k=0;k<3;k++){

			sum+=(M[i][k]*a.get(k,j));

		  }
		  product.set(i,j,sum);
		}
	  }
		return product;
	}//end MatrixMultiply
	Matrix3 operator * (Matrix3 a)		
	{
		return multiply(a);
	}
	Vector3 operator * (Vector3 a)		
	{
		return multiply(a);
	}

// Matrix by vector multiplication
//		3x[3|3]x1 = 3x1 
	Vector3 multiply(Vector3 a)
	{
	  Vector3 product=Vector3();

	  for(int i=0;i<3;i++){
		double sum=0;
		for(int k=0;k<3;k++){
		  sum+=M[i][k]*a[k];
		}
		product.set(i,sum);
	  }
	  return product;

	}//end M*V

	//this=a 
	void assign(Matrix3 a) 
	{ 
	  for (int i=0;i<4;i++){ 
	    for(int j=0;j<4;j++){ 
	      set(i,j,a.get(i,j)); 
	    }//end for i 
	  }//end for j 
	}//end assign 


	void print(){
		printf("\n{\n");

		for(int i=0;i<3;i++){
		  
		}
		printf("[%4.1f, %4.1f, %4.1f],\n", M[0][0],M[0][1],M[0][2]);
		printf("[%4.1f, %4.1f, %4.1f],\n", M[1][0],M[1][1],M[1][2]);
		printf("[%4.1f, %4.1f, %4.1f],\n", M[2][0],M[2][1],M[2][2]);
		printf("}\n");
	}

	Matrix3 transpose()
	{

		Matrix3 res=Matrix3();

		for(int i=0;i<3;i++){
		  for(int j=0;j<3;j++){
			res.set(j,i,M[i][j]);
		  }
		}

		return res;
	}//end transpose()
};//end class Matrix3


