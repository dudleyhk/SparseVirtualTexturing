/*



*/
#include "Triangle.h"


using namespace Rendering;
using namespace Models;



Triangle::Triangle()
{}

Triangle::~Triangle()
{
	
}

void Triangle::Create()
{
	GLuint vao;
	GLuint vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);

	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3(0.5f, 0.f, 0.f),
									glm::vec4(1, 0, 0, 1), 
									glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-0.f, -0.f, 0.f),
									glm::vec4(0, 1, 0, 1),
									glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(0.5f, 0.5f, 0.f),
									glm::vec4(0, 0, 1, 1),
									glm::vec2(0, 0)));


	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 3, &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::colour)));


	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (GLvoid*)(offsetof(VertexFormat, VertexFormat::uv)));

	glBindVertexArray(0);

	this->vao = vao;
	this->vbos.push_back(vbo);

}

void Triangle::Update()
{
	
}

void Triangle::Draw()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}