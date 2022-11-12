#include "../include/Shader.h"

namespace evolver
{
	Shader::Shader() : programID(0) {}

	Shader::~Shader() { glDeleteProgram(programID); }

	Shader::Shader(std::vector<std::string> files, std::string name, bool overwrite)
	{
		if (!std::filesystem::exists("shaders/cache"))
		{
			std::filesystem::create_directory("shaders/cache");
		}

		shaderFile = "shaders/cache/";
		shaderFile += name;

		if (std::strstr(shaderFile.c_str(), ".cache"))
		{
			shaderFile += ".cache";
		}

		GLint formats = 0;
		glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &formats);

		if (formats > 0)
		{
			if (overwrite && std::filesystem::exists(shaderFile))
			{
				std::filesystem::remove(shaderFile);
			}

			if (std::filesystem::exists(shaderFile))
			{
				LoadCompiledShader();
			}
			else
			{
				LinkProgram(files);
				SaveCompiledShader();
			}			
		}
		else
		{
			LinkProgram(files);
		}
	}

	void Shader::Load() { glUseProgram(programID); }
	void Shader::Unload() { glUseProgram(0); }

	void Shader::Reset()
	{
		glDeleteProgram(programID);

		uniformMap.clear();
		programID = 0;
	}

	// ----------------------------------------------------------------------------------------------------------------
	// -- Creating & Compiling Shader

	void Shader::SaveCompiledShader()
	{
		GLint length = 0;
		glGetProgramiv(programID, GL_PROGRAM_BINARY_LENGTH, &length);

		std::vector<GLubyte> buffer(length);
		glGetProgramBinary(programID, length, NULL, &binaryFormat, buffer.data());

		std::ofstream formatFile("shaders/cache/format.txt");
		formatFile << binaryFormat;
		formatFile.close();

		std::ofstream out(shaderFile.c_str(), std::ios::binary);
		out.write(reinterpret_cast<char*>(buffer.data()), length);
		out.close();
	}

	void Shader::LoadCompiledShader()
	{
		programID = glCreateProgram();

		if (!std::filesystem::exists("shaders/cache/format.txt"))
		{
			return;
		}

		std::ifstream formatFile("shaders/cache/format.txt");
		formatFile >> binaryFormat;
		formatFile.close();

		std::ifstream inputStream(shaderFile.c_str(), std::ios::binary);
		std::istreambuf_iterator<char> startIt(inputStream), endIt;
		std::vector<char> buffer(startIt, endIt);
		inputStream.close();

		glProgramBinary(programID, binaryFormat, buffer.data(), buffer.size());
		CheckShaderProgram(programID);
	}

	void Shader::CheckShaderProgram(unsigned int program)
	{
		int success;
		char infoLog[512];
		glGetProgramiv(program, GL_LINK_STATUS, &success);

		if (success)
		{
			return;
		}

		LOG_ERROR("Program Cant Loaded Successfully");
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "::Program ERROR::\n" << infoLog << "\n";
	}

	void Shader::CheckShader(unsigned int shader)
	{
		int success;
		char infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (success)
		{
			return;
		}

		LOG_ERROR("Shader Cant Loaded Successfully");
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "::Shader ERROR::\n" << infoLog << "\n";
	}

	GLenum Shader::GetShaderType(const std::string& file)
	{
		if (std::strstr(file.c_str(), ".vert"))			return GL_VERTEX_SHADER;
		else if (std::strstr(file.c_str(), ".tecs"))		return GL_TESS_CONTROL_SHADER;
		else if (std::strstr(file.c_str(), ".teval"))	return GL_TESS_EVALUATION_SHADER;
		else if (std::strstr(file.c_str(), ".geom"))		return GL_GEOMETRY_SHADER;
		else if (std::strstr(file.c_str(), ".frag"))		return GL_FRAGMENT_SHADER;
		else if (std::strstr(file.c_str(), ".comp"))		return GL_COMPUTE_SHADER;
	}

	std::string Shader::GetShaderString(const std::string& file)
	{
		std::ifstream reader;
		reader.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			reader.open(file);

			if (!reader.is_open())
			{
				LOG_ERROR("Can't read from " + file);
			}

			std::stringstream stream;
			stream << reader.rdbuf();
			reader.close();

			if (strstr(stream.str().c_str(), "#include") == 0)
			{
				return stream.str();
			}

			return LookForInclude(stream);
		}
		catch (std::ifstream::failure e)
		{
			if (reader.is_open())
			{
				reader.close();
			}

			LOG_ERROR("Read from " + file);

			return std::string();
		}
	}

	std::string Shader::LookForInclude(std::stringstream& realStream)
	{
		std::ifstream reader;
		reader.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		std::string shaderString;
		std::stringstream includeStream;
		std::string tempStr;
		std::string includeFile;

		size_t firstTime, lastTime;

		while (std::getline(realStream, tempStr, '\n'))
		{
			if (strstr(tempStr.c_str(), "#include"))
			{
				firstTime = tempStr.find_first_of('"') + 1;
				lastTime = tempStr.find_last_of('"');
				includeFile = tempStr.substr(firstTime, lastTime - firstTime);
				includeFile = "shaders/" + includeFile;

				reader.open(includeFile);

				if (!reader.is_open())
				{
					LOG_ERROR("Cannot open " + includeFile + " in shader");
					return std::string();
				}

				includeStream << reader.rdbuf();
				reader.close();

				shaderString += (includeStream.str() + "\n\n");
				
				includeStream.str("");
				includeStream.clear();
			}
			else
			{
				if (strcmp(tempStr.c_str(), "") != 0)
				{
					shaderString += (tempStr + "\n\n");
				}
			}
		}

		return shaderString;
	}

	void Shader::LinkProgram(std::vector<std::string>& shaderFiles)
	{
		programID = glCreateProgram();

		if (programID == 0)
		{
			LOG_ERROR("Cant create program");
		}

		std::vector<GLuint> shaders;
		shaders.resize(shaderFiles.size());

		for (int i = 0; i < shaderFiles.size(); i++)
		{
			GLuint tempShader = CompileShader(shaderFiles[i], GetShaderType(shaderFiles[i]));
			glAttachShader(programID, tempShader);
			shaders[i] = tempShader;
		}

		glLinkProgram(programID);
		CheckShaderProgram(programID);

		for (int i = 0; i < shaders.size(); i++)
		{
			glDetachShader(programID, shaders[i]);
			glDeleteShader(shaders[i]);
		}
	}

	GLuint Shader::CompileShader(const std::string& file, GLenum shaderType)
	{
		GLuint shader = glCreateShader(shaderType);

		if (shader == 0)
		{
			LOG_ERROR("Can't Create Shader " + file);
		}

		std::string code = GetShaderString(file);
		const GLchar* codeArr[] = { code.c_str() };

		glShaderSource(shader, 1, codeArr, NULL);

		glCompileShader(shader);

		CheckShader(shader);

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

	void Shader::SetBool(const std::string& name, bool value)		{ glUniform1i(GetUniformLocation(name), (int)value); }
	void Shader::SetInt(const std::string& name, int value)			{ glUniform1i(GetUniformLocation(name), value); }
	void Shader::SetFloat(const std::string& name, float value)		{ glUniform1f(GetUniformLocation(name), value); }
	void Shader::SetVec2(const std::string& name, glm::vec2 value)	{ glUniform2fv(GetUniformLocation(name), 1, glm::value_ptr(value)); }
	void Shader::SetVec3(const std::string& name, glm::vec3 value)	{ glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(value)); }
	void Shader::SetVec4(const std::string& name, glm::vec4 value)	{ glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(value)); }
	void Shader::SetMat3(const std::string& name, glm::mat3 value)	{ glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)); }
	void Shader::SetMat4(const std::string& name, glm::mat4 value)	{ glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)); }
}