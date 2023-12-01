//background.frag setup by River

#version 450
out vec4 FragColor;
in vec2 UV;

// World Data
uniform float _Time;
uniform float _ScrollSpeed;
uniform vec2 _Resolution;

// Texture Data
uniform sampler2D _Mountain1;
uniform sampler2D _Mountain2;

void main(){
	vec3 color = vec3(0.0, 0.0, 0.5);
	FragColor = vec4(color, 1.0);
}