#version 410

in vec2 texture_coord;
in vec3 frag_position;
in vec3 frag_normal;

out vec4 frag_colour;

uniform sampler2D material_texture_diffuse1;
uniform sampler2D material_texture_specular1;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float lightAmbient;
uniform vec3 eyePos;

void main() {
	vec4 surface_color = texture(material_texture_diffuse1, texture_coord);
	vec3 specular_color = vec3(texture(material_texture_specular1, texture_coord));

	vec3 norm = normalize(frag_normal);
	vec3 lightDir = normalize(lightPos - frag_position);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 viewDir = normalize(eyePos - frag_position);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = spec * specular_color * lightColor;

	frag_colour = vec4(lightAmbient + diffuse, 1.0f) * surface_color;
}
