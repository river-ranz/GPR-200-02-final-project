//background.frag setup by River

#version 450
out vec4 FragColor;
in vec2 UV;

// World Data
uniform float _Time;
uniform vec2 _Resolution;
uniform float _backgroundSpeed;

//color data
uniform vec4 _HillColor;

// Texture Data
uniform sampler2D _Mountain1;
uniform sampler2D _Mountain2;

void main(){
	vec4 color = vec4(0.2, 0.4, 0.8, 1.0);

	vec2 uv = vec2(UV.x, UV.y); //scaling

	//mountains by Liam

	float xPos = uv.x;
	if (xPos < 1 && xPos > 0) xPos = uv.x + _Time * (_backgroundSpeed / 12);
	else xPos = 1;
	//if (xPos > 1) xPos = 1;
	vec4 mountainA = texture(_Mountain1, vec2(xPos, uv.y));
	vec4 mountainB = texture(_Mountain2, vec2(xPos, uv.y));
	vec4 mountainLayer = mix(mountainA, mountainB, 0.5);

	//rolling hills by River
	
	float hills = 1.0 - step(sin(UV.x * 5 + _Time * _backgroundSpeed) * 0.1 + 0.3, UV.y);
	FragColor = mix(mountainA + mountainB, _HillColor, hills);
}