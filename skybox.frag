varying vec3 texcoords;
uniform samplerCube tex_cube;

void main(){
     gl_FragColor = textureCube(tex_cube, texcoords);
}	