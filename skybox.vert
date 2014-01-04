#version 120

varying vec3 texcoords;

void main(){
     
     texcoords = gl_Vertex.xyz;

     gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
     //gl_Position = vec4(vp, 1.0);
}