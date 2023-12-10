//dragon.frag by River

#version 450
out vec4 FragColor;
in vec2 UV;

uniform float _Time;
uniform sampler2D _DragonTexture;

//https://stackoverflow.com/questions/71421703/how-do-i-use-opengl-to-make-spritesheet-animation

const float col = 2.0;
const float row = 1.0;
const uint numSprites = 2;

void main(){
	uint sprite = int(_Time * 5) % numSprites;
    vec2 pos = vec2(sprite % int(col), int(sprite / col));
    FragColor = texture(_DragonTexture, vec2((UV.x / col) + pos.x * (1.0 / col), (UV.y / row) + pos.y * (1.0 / row)));
}