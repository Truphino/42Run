#version 410

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 vertex_normal;
layout (location = 2) in vec2 vertex_texture;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;

out vec2 texture_coord;
out vec3 frag_position;
out vec3 frag_normal;

void main() {
	frag_normal = vertex_normal;
	texture_coord = vertex_texture;
	frag_position = pos;
	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(pos, 1.0f);
}
