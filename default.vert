#version 330 core
layout (location = 0) in vec3 apos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;

out vec3 crntpos;
out vec3 normal;
out vec3 color;
out vec2 texcoord;

uniform mat4 camMatrix;
uniform mat4 model;
uniform mat4 translate;
uniform mat4 rotation;
uniform mat4 scale;

void main()
{
crntpos = vec3(model * vec4(apos,1.0f));
normal = aNormal;
color = aColor;
texcoord = mat2(0.0f, -1.0f,1.0f,0.0f) * aTex;
gl_Position = camMatrix * vec4(crntpos, 1.0f);
}