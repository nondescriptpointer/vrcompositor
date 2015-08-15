#version 450

//precision mediump float;

uniform sampler2D textureUnit;
smooth in vec2 vTex;

out vec4 gl_FragColor;

void main(void){
    gl_FragColor = vec4(texture(textureUnit,vTex));
}