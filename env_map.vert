#version 120

varying vec4 pos_eye;
varying vec3 n_eye;
varying mat4 View;
uniform mat4 V;
	
void main(){
     
     View=V;
     pos_eye = gl_ModelViewMatrix * gl_Vertex;
     n_eye = gl_NormalMatrix * gl_Normal;
     gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
}