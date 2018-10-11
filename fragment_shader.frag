#version 410

in vec2 texture_coord;
in vec3 frag_position;
in vec3 frag_normal;

out vec4 frag_colour;

uniform sampler2D material_texture_diffuse1;
uniform sampler2D material_texture_diffuse2;

void main() {
	vec4 surface_color;

	surface_color = texture(material_texture_diffuse1, texture_coord);
	frag_colour = surface_color;
}
