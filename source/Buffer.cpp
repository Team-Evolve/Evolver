#include "../include/Buffer.h"

template<typename VT>
evolver::Buffer<VT>::Buffer() : bufferCount(0)
{
	glGenBuffers(1, &bufferID);
}

template<typename VT>
evolver::Buffer<VT>::~Buffer()
{
	glDeleteBuffers(1, &bufferID);
}

template<typename VT>
void evolver::Buffer<VT>::Set(VT* arr, unsigned int len, GLenum drawType)
{
	bufferCount = len;
	unsigned int sizeofVariable = sizeof(VT);

	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeofVariable * bufferCount, arr, drawType);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template<typename VT>
void evolver::Buffer<VT>::Set(std::vector<VT>& inputVector)
{
	Set(&inputVector[0], (unsigned int)inputVector.size());
}

template<typename VT>
void evolver::Buffer<VT>::Bind(unsigned int slot)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glEnableVertexAttribArray(slot);
	SetAttribPointer(slot);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template<typename VT>
void evolver::Buffer<VT>::Unbind(unsigned int slot)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glDisableVertexAttribArray(slot);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template<typename VT>
unsigned int evolver::Buffer<VT>::GetBufferCount() { return bufferCount; }

template<typename VT>
unsigned int evolver::Buffer<VT>::GetBufferID() { return bufferID; }

template<>
void evolver::Buffer<int>::SetAttribPointer(unsigned int s)
{
	glVertexAttribIPointer(s, 1, GL_INT, 0, (void*)0);
}

template<>
void evolver::Buffer<glm::ivec4>::SetAttribPointer(unsigned int s)
{
	glVertexAttribIPointer(s, 4, GL_INT, 0, (void*)0);
}

void evolver::Buffer<float>::SetAttribPointer(unsigned int s)
{
	glVertexAttribPointer(s, 1, GL_FLOAT, GL_FALSE, 0, 0);
}

template<>
void evolver::Buffer<glm::vec2>::SetAttribPointer(unsigned int s)
{
	glVertexAttribPointer(s, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

template<>
void evolver::Buffer<glm::vec3>::SetAttribPointer(unsigned int s)
{
	glVertexAttribPointer(s, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

template<>
void evolver::Buffer<glm::vec4>::SetAttribPointer(unsigned int s)
{
	glVertexAttribPointer(s, 4, GL_FLOAT, GL_FALSE, 0, 0);
}