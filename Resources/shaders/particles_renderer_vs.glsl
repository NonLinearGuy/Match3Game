#version 400

layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 tex;
layout(location = 2) in vec4 col;
layout(location = 3) in vec2 offset;
layout(location = 4) in vec2 scaler;

uniform mat4 view;
uniform mat4 projection;

out vec2 tex_coords;
out vec4 color;

void main()
{

	tex_coords = tex;
	color = col;

	vec4 position = vec4(pos,0.0f,1.0f);
	position.xy *= scaler; //scaling first
	position.xy += offset; //then translating
	
	gl_Position = projection*view*position;

}
