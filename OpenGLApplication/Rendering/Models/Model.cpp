/*



*/
#include "Model.h"


using namespace Rendering;
using namespace Models;


Model::~Model()
{
	Destroy();
}

void Model::Draw()
{
	//this will be again overridden
}

void Model::Update()
{
	//this will be again overridden
}

void Model::SetProgram(GLuint program)
{
	this->program = program;
}

GLuint Model::GetVao() const
{
	return vao;
}

const std::vector<GLuint>& Model::GetVbos() const
{
	return vbos;
}

void Model::Destroy()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(vbos.size(), &vbos[0]);
	vbos.clear();
}