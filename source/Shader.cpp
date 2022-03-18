#include "../include/Shader.h"

evolver::Shader::Shader() : programID(0) {}

evolver::Shader::~Shader() { glDeleteProgram(programID); }

void evolver::Shader::Reset()
{
	glDeleteProgram(programID);

	programID = 0;
}

void evolver::Shader::DeleteShader(unsigned int shader) { glDeleteShader(shader); }

std::string evolver::Shader::GetShaderString(std::string file)
{
	std::ifstream reader;
	reader.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	#if _DEBUG
	std::cout << "Can't read from " << file << " \n";
	#endif

	try
	{
		reader.open(file);

		std::stringstream stream;

		stream << reader.rdbuf();

		reader.close();

		return stream.str();
	}
	catch (std::ifstream::failure e)
	{
		if (reader.is_open())
			reader.close();

		#if _DEBUG
		std::cout << "::ERROR:: Read from " << file << " \n";
		#endif

		return std::string();
	}
}

void evolver::Shader::LinkProgram(unsigned int comp, unsigned int vertex, unsigned int tesEval, unsigned int tesCos, unsigned int geometry, unsigned int fragment)
{
	programID = glCreateProgram();

	#if _DEBUG
	if (programID == 0)
	{
		std::cout << "Cant create program\n";
		exit(EXIT_FAILURE);
	}
	#endif

	if (comp > 0)
		glAttachShader(programID, comp);
	if (vertex > 0)
		glAttachShader(programID, vertex);
	if (tesEval > 0)
		glAttachShader(programID, tesEval);
	if (tesCos > 0)
		glAttachShader(programID, tesCos);
	if (geometry > 0)
		glAttachShader(programID, geometry);
	if (fragment > 0)
		glAttachShader(programID, fragment);

	glLinkProgram(programID);

	if (comp > 0)
	{
		glDetachShader(programID, comp);
		glDeleteShader(comp);
	}
	if (vertex > 0)
	{
		glDetachShader(programID, vertex);
		glDeleteShader(vertex);
	}
	if (tesEval > 0)
	{
		glDetachShader(programID, tesEval);
		glDeleteShader(tesEval);
	}
	if (tesCos > 0)
	{
		glDetachShader(programID, tesCos);
		glDeleteShader(tesCos);
	}
	if (geometry > 0)
	{
		glDetachShader(programID, geometry);
		glDeleteShader(geometry);
	}
	if (fragment > 0)
	{
		glDetachShader(programID, fragment);
		glDeleteShader(fragment);
	}
}

GLuint evolver::Shader::CompileShader(std::string file, EV_ShaderType shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	#if _DEBUG
	if (shader == 0)
	{
		std::cout << "Can't Create Shader " << file << "\n";
		exit(EXIT_FAILURE);
	}
	#endif

	std::string code = GetShaderString(file);
	const GLchar* codeArr[] = { code.c_str() };

	glShaderSource(shader, 1, codeArr, NULL);

	glCompileShader(shader);

	return shader;
}