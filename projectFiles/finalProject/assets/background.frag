//background.frag setup by River & Liam

#version 450
out vec4 FragColor;
in vec2 UV;

// World Data
uniform float _Time;
uniform float _backgroundSpeed;

//color data
uniform vec4 _HillColor;

// Texture Data
uniform sampler2D _Texture;
uniform int _ImageID;
uniform float _SpriteStartPos;

void main(){
	vec4 color = vec4(0.2, 0.4, 0.8, 1.0);

	vec2 uv = vec2(UV.x, UV.y); //scaling

	//Texture code by Liam
	float xPos = uv.x;
	if (xPos < 1 && xPos > 0)
	{
		if (_ImageID == 1 || _ImageID == 3)
		{
			xPos = uv.x + _Time * (_backgroundSpeed / 18);
		}
		else
		{
			xPos = uv.x + _Time * (_backgroundSpeed / 36);
		}
	}
	else
	{
		xPos = 1;
	}
	vec4 texCoords = texture(_Texture, vec2(xPos + _SpriteStartPos, uv.y));

	//rolling hills by River
	float hills = 1.0 - step(sin(UV.x * 5 + _Time * _backgroundSpeed) * 0.1 + 0.3, UV.y);

	FragColor = mix(texCoords, _HillColor, hills);
}