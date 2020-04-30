#version 410 core
layout (location = 0) in vec3 w_aPos;
layout (location = 1) in vec2 w_aTexCoord;
layout (location = 2) in vec3 w_normals;

out vec2 w_TexCoord;
out vec3 w_ourColor;
out vec3 w_Normals;
out vec3 w_FragPos;

uniform mat4 w_model;
uniform mat4 w_view;
uniform mat4 w_projection;

void main()
{
	w_FragPos = vec3(w_model * vec4(w_aPos, 1.0));
	gl_Position = w_projection * w_view * w_model * vec4(w_aPos, 1.0f);
	w_TexCoord = w_aTexCoord;
	w_Normals = mat3(transpose(inverse(w_model))) * w_normals;
}