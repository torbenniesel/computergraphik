#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

//out vec3 ourColor;
out vec3 ourFragPos;
out vec3 ourNormal;
out vec2 ourTexCoord;

uniform mat4 transform;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	ourFragPos = vec3(model * vec4(aPos, 1.0f));
	ourNormal = mat3(transpose(inverse(model))) * aNormal;
	//gl_Position = transform * vec4(aPos, 1.0f);
	gl_Position = projection * view * vec4(ourFragPos, 1.0f);

	//ourColor = aColor;
	ourTexCoord = aTexCoord;
}

#shader fragment
#version 330 core

out vec4 FragColor;

uniform vec3 lightColor;

void main(){
	FragColor = vec4(lightColor, 1.0f);
}