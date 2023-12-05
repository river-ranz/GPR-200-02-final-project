//background.frag setup by River

#version 450
out vec4 FragColor;
in vec2 UV;

// World Data
uniform float _Time;
uniform float _ScrollSpeed;
uniform vec2 _Resolution;

//color data
uniform vec3 _HillColor;

// Texture Data
uniform sampler2D _Mountain1;
uniform sampler2D _Mountain2;

void main(){
	vec3 color = vec3(0.2, 0.4, 0.8);

	vec2 uv = vec2(UV.x * 0.5, UV.y * 0.5); //scaling

	//rolling hills by River
	float hills = 1.0 - step(sin(UV.x * 5 + _Time) * 0.1 + 0.3, UV.y);
	color = mix(color, _HillColor, hills);

	FragColor = vec4(color, 1.0);
}