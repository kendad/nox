#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float time;
uniform float speed;
uniform float randX;
uniform float randY;

float rand(vec2 co){
  return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
    TexCoords = aTexCoords;
	Normal=mat3(transpose(inverse(model))) * aNormal;
	FragPos=vec3(model*vec4(aPos,1.0f));

	//float modifiedX=randX*cos(aPos.x-time*speed)+aPos.x;
	//float modifiedY=randY*sin(modifiedX-time*speed);//amplitude*sin(x-speed*time)
	
	float modifiedX=rand(vec2(aPos.x,aPos.y))*randX*cos(aPos.x-time*speed)+aPos.x;
	float modifiedY=rand(vec2(aPos.z,aPos.y))*randY*sin(modifiedX-time*speed);//amplitude*sin(x-speed*time)
	
	vec4 finalPos=vec4(modifiedX,modifiedY,aPos.z,1.0f);
	
    gl_Position = projection * view * model * finalPos;
}