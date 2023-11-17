//dragon.vert setup by River

#version 450
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec2 vUV;
out vec2 UV;

void main(){
	UV = vUV;
	vec3 pos = vPos;
	pos *= 0.8; //scaling
	gl_Position = vec4(pos, 1.0);
}