#version 410

in vec3 pos;
in vec3 vertex_normal;
in vec2 vertex_texture;

out vec2 texture_coord;
out vec3 frag_position;
out vec3 frag_normal;

void main() {
	frag_position = pos;
	frag_normal = vertex_normal;
	texture_coord = vertex_texture;
	gl_Position = vec4(pos, 1.0);
}
