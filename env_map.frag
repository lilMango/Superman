varying vec4 pos_eye;
varying vec3 n_eye;
varying mat4 View;
uniform samplerCube tex_cube;

void main(){
     
     vec3 incident_eye = normalize(pos_eye.xyz);
     vec3 normal = normalize(n_eye);
     
     vec3 reflected = reflect(incident_eye, normal);
     
     //convert from eye to worldspace

     //reflected = vec3 (inverse(View) * vec4(reflected,0.0));

     
     gl_FragColor = textureCube(tex_cube, reflected);     

}	