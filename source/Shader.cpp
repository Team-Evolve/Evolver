#include "../include/Shader.h"

namespace evolver
{
	Shader::Shader() : programID(0) {}

	Shader::~Shader() { glDeleteProgram(programID); }

	Shader::Shader(std::vector<std::string> files)
	{
		LinkProgram(files);
	}

	void Shader::Load() { glUseProgram(programID); }
	void Shader::Unload() { glUseProgram(0); }

	void Shader::Reset()
	{
		glDeleteProgram(programID);

		programID = 0;
	}

	// ----------------------------------------------------------------------------------------------------------------
	// -- Creating & Compiling Shader

	GLenum Shader::GetShaderType(std::string file)
	{
		if (std::strstr(file.c_str(), ".vert"))
			return GL_VERTEX_SHADER;
		else if (std::strstr(file.c_str(), ".tecs"))
			return GL_TESS_CONTROL_SHADER;
		else if (std::strstr(file.c_str(), ".teval"))
			return GL_TESS_EVALUATION_SHADER;
		else if (std::strstr(file.c_str(), ".geom"))
			return GL_GEOMETRY_SHADER;
		else if (std::strstr(file.c_str(), ".frag"))
			return GL_FRAGMENT_SHADER;
	}

	std::string Shader::GetShaderString(std::string file)
	{
		std::ifstream reader;
		reader.exceptions(std::ifstream::failbit | std::ifstream::badbit);

#if _DEBUG
		if(!reader.is_open())
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

	void Shader::LinkProgram(std::vector<std::string> shaderFiles)
	{
		programID = glCreateProgram();

#if _DEBUG
		if (programID == 0)
		{
			std::cout << "Cant create program\n";
			exit(EXIT_FAILURE);
		}
#endif

		std::vector<GLuint> shaders;
		shaders.resize(shaderFiles.size());

		for (int i = 0; i < shaderFiles.size(); i++)
		{
			GLuint tempShader = CompileShader(shaderFiles[i], GetShaderType(shaderFiles[i]));
			glAttachShader(programID, tempShader);
			shaders.push_back(tempShader);
		}

		glLinkProgram(programID);

		for (int i = 0; i < shaders.size(); i++)
		{
			glDetachShader(programID, shaders[i]);
			glDeleteShader(shaders[i]);
		}
	}

	GLuint Shader::CompileShader(std::string file, GLenum shaderType)
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

	// ----------------------------------------------------------------------------------------------------------------
	// -- Set Uniform

	GLint Shader::GetUniformLocation(const std::string& name)
	{
		if (uniformMap.find(name) != uniformMap.end())
		{
			return uniformMap[name];
		}

		uniformMap[name] = glGetUniformLocation(programID, name.c_str());
		return uniformMap[name];
	}

	void Shader::SetBool(const std::string& name, bool value) { glUniform1i(GetUniformLocation(name), (int)value); }
	void Shader::SetInt(const std::string& name, int value) { glUniform1i(GetUniformLocation(name), value); }
	void Shader::SetFloat(const std::string& name, float value) { glUniform1f(GetUniformLocation(name), value); }
	void Shader::SetVec2(const std::string& name, glm::vec2 value) { glUniform2fv(GetUniformLocation(name), 1, glm::value_ptr(value)); }
	void Shader::SetVec3(const std::string& name, glm::vec3 value) { glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(value)); }
	void Shader::SetVec4(const std::string& name, glm::vec4 value) { glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(value)); }
	void Shader::SetMat3(const std::string& name, glm::mat3 value) { glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)); }
	void Shader::SetMat4(const std::string& name, glm::mat4 value) { glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)); }
}