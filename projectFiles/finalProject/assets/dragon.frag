#version 450
out vec4 FragColor;
in vec2 UV;

uniform sampler2D _DragonTexture;

void main(){
	//FragColor = texture(_DragonTexture, UV);
	FragColor = vec4(UV.x, UV.y, 0.0, 1.0);
}