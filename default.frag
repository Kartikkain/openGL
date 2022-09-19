#version 330 core
out vec4 FragColor;

in vec3 crntpos;
in vec3 normal;
in vec3 color;
in vec2 texcoord;
uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform vec4 lightcolor;
uniform vec3 lightpos;
uniform float ambient;
uniform vec3 campos;
uniform float a;
uniform float b;
uniform bool isSpot;
uniform float OuterCone;
uniform float InnerCone;


vec4 PointLight()
{
	vec3 lightVec = lightpos - crntpos;
	float dist = length(lightVec);
	float intensity = 1.0f / ( a * dist * dist + b * dist + 1.0f);

	vec3 Normal = normalize(normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(Normal,lightDirection),0.0f);
	float Ambient = ambient;
	float Specularlight = 0.5f;
	vec3 ViewDirection = normalize(campos - crntpos);
	vec3 reflectionDirection = reflect(-lightDirection,Normal);
	vec3 halfwayvector = normalize(ViewDirection + lightDirection);
	float specularAmount = pow(max(dot(Normal,halfwayvector),0.0f),16);
	float Specular = Specularlight * specularAmount;

	return (texture(diffuse0, texcoord)  * (diffuse * intensity + Ambient) + texture(specular0, texcoord).r * Specular * intensity) * lightcolor;
}

vec4 DirectionalLight()
{
	
	vec3 Normal = normalize(normal);
	vec3 lightDirection = normalize(vec3(1.0f,1.0f,0.0f));
	float diffuse = max(dot(Normal,lightDirection),0.0f);
	float Ambient = ambient;
	float Specularlight = 0.5f;
	vec3 ViewDirection = normalize(campos - crntpos);
	vec3 reflectionDirection = reflect(-lightDirection,Normal);
	float specularAmount = pow(max(dot(ViewDirection,reflectionDirection),0.0f),16);
	float Specular = Specularlight * specularAmount;

	return (texture(diffuse0, texcoord)  * (diffuse + Ambient) + texture(specular0, texcoord).r * Specular ) * lightcolor;
}


vec4 SpotLight()
{	
	
	vec3 Normal = normalize(normal);
	vec3 lightDirection = normalize(lightpos - crntpos);
	float diffuse = max(dot(Normal,lightDirection),0.0f);
	float Ambient = ambient;
	float Specularlight = 0.5f;
	vec3 ViewDirection = normalize(campos - crntpos);
	vec3 reflectionDirection = reflect(-lightDirection,Normal);
	float specularAmount = pow(max(dot(ViewDirection,reflectionDirection),0.0f),16);
	float Specular = Specularlight * specularAmount;

	float angle = dot(vec3(0.0f,-1.0f,0.0f), -lightDirection);
	float intensity = clamp((angle - OuterCone) / (InnerCone - OuterCone),0.0f,1.0f);

	return (texture(diffuse0, texcoord)  * (diffuse * intensity + Ambient) + texture(specular0, texcoord).r * Specular * intensity) * lightcolor;
}

float near = 0.1f;
float far = 100.0f;

float linearizeDepth(float depth)
{
	return (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));
}

float logisticDepth(float depth)
{
	float steepness = 0.5f;
	float offset = 5.0f;
	float zval = linearizeDepth(depth);
	return (1/(1 + exp(- steepness * (zval - offset))));
}

void main()
{

	//float depth = logisticDepth(gl_FragCoord.z);
	//FragColor = DirectionalLight() * (1.0f - depth) + vec4(depth * vec3(0.85f,0.85f,0.90f),1.0f);
	FragColor = (isSpot) ? SpotLight(): PointLight();
}