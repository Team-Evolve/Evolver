#pragma once

#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace evolver
{
	class Shader
	{
	public:
		Shader();
		Shader(std::vector<std::string> files);
		~Shader();

		void Load();
		void Unload();

		void Reset();

	private:
		GLenum GetShaderType(std::string file);
		GLuint CompileShader(std::string file, GLenum shaderType);
		void LinkProgram(std::vector<std::string> shaderFiles);
		std::string GetShaderString(std::string file);

		GLint GetUniformLocation(const std::string& name);

		// -- Uniform Functions
		void SetBool(const std::string& name, bool value);
		void SetInt(const std::string& name, int value);
		void SetFloat(const std::string& name, float value);
		void SetVec2(const std::string& name, glm::vec2 value);
		void SetVec3(const std::string& name, glm::vec3 value);
		void SetVec4(const std::string& name, glm::vec4 value);
		void SetMat3(const std::string& name, glm::mat3 value);
		void SetMat4(const std::string& name, glm::mat4 value);

	private:
		std::unordered_map<std::string, GLint> uniformMap;
		unsigned int programID;
	};
}