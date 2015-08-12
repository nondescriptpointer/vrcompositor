#version 450

//precision mediump float;
uniform vec4 vColor;
out vec4 gl_FragColor;

void main(void){
    gl_FragColor = vColor;
}