#pragma once

#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <glad/glad.h>

enum EV_ShaderType
{
	EV_ST_COMPUTE = GL_COMPUTE_SHADER,
	EV_ST_VERTEX = GL_VERTEX_SHADER,
	EV_ST_TESS_CONT = GL_TESS_CONTROL_SHADER,
	EV_ST_TESS_EVAL = GL_TESS_EVALUATION_SHADER,
	EV_ST_GEOMETRY = GL_GEOMETRY_SHADER,
	EV_ST_FRAGMENT = GL_FRAGMENT_SHADER
};

namespace evolver
{
	class Shader
	{
	public:
		Shader();
		~Shader();

		void Reset();

	private:
		GLuint CompileShader(std::string file, EV_ShaderType shaderType);
		void LinkProgram(unsigned int comp = 0, unsigned int vertex = 0, unsigned int tesEval = 0, unsigned int tesCos = 0, unsigned int geometry = 0, unsigned int fragment = 0);

		std::string GetShaderString(std::string file);
		void DeleteShader(unsigned int shader);

	private:
		unsigned int programID;
	};
}
