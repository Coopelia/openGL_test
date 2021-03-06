#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;//法向量
layout (location = 2) in vec2 aTexCoord;

out vec3 Normal;
out vec3 FragPos; //片段位置
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));//世界坐标系中
    Normal = mat3(transpose(inverse(model))) * aNormal;                           
    TexCoord = aTexCoord;

    gl_Position = projection * view * model * vec4(aPos, 1.0);
}