//dragon.frag setup by River

#version 450
out vec4 FragColor;
in vec2 UV;

uniform sampler2D _DragonTexture;

void main(){
	FragColor = texture(_DragonTexture, UV);
}