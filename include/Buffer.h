#pragma once

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace evolver
{
	template<typename VT>
	class Buffer
	{
	public:
		Buffer();
		~Buffer();

		void Set(VT* arr, unsigned int len, GLenum drawType = GL_STATIC_DRAW);
		void Set(std::vector<VT>& inputVector);

		void Bind(unsigned int slot);
		void Unbind(unsigned int slot);

		unsigned int GetBufferCount();
		unsigned int GetBufferID();

	protected:
		unsigned int bufferID, bufferCount;

	private:
		void SetAttribPointer(unsigned int s);
	};
}
