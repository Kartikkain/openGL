#include"shaderClass.h"

std::string get_file_content(const char* filename)
{
	std::ifstream in (filename, std::ios::binary);
	if (in)
	{
		std::string content;
		in.seekg(0,std::ios::end);
		content.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&content[0], content.size());
		in.close();
		return (content);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragementFile)
{
	std::string vertexCode = get_file_content(vertexFile);
	std::string fragementCode = get_file_content(fragementFile);


	const char* vertexSource = vertexCode.c_str();
	const char* fragementSource = fragementCode.c_str();

	
	// Creating vertex shader and compiling into assembly language

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	// Creating fragement shader and compiling into assembly language

	GLuint fragementShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragementShader, 1, &fragementSource, NULL);
	glCompileShader(fragementShader);

	// Creating a programme

	ID = glCreateProgram();

	// Attaching vertex shader to programme

	glAttachShader(ID, vertexShader);

	// Attaching fragement shader to programme

	glAttachShader(ID, fragementShader);

	// Linking all the shader together

	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragementShader);

}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader:: Delete()
{
	glDeleteProgram(ID);
}