#version 410

in vec2 texture_coord;
in vec3 frag_position;
in vec3 frag_normal;

out vec4 frag_colour;

uniform sampler2D tex;

void main() {
	vec4 surface_color;

	surface_color = texture(tex, texture_coord);
	frag_colour = surface_color;
}
