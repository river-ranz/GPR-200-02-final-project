//dragon.frag setup by River

#version 450
out vec4 FragColor;
in vec2 UV;

//https://gist.github.com/passiomatic/4e108740db98eea5d2e6873267271f37
uniform sampler2D _DragonTexture;
vec2 spriteSheetSize = (256, 256);

void main(){
	FragColor = texture(_DragonTexture, UV);
}