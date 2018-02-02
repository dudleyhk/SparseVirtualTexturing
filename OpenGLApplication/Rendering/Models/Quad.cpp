/*



*/
#include "Quad.h"

using namespace Rendering::Models;


void Quad::Create()
{
	GLuint vao;
	GLuint vbo;
	GLuint ebo;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);


	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3( -3.f, 0.2f, 0.f),
									glm::vec4( 1.f , 1.f , 0.f , 1.f), 
									glm::vec2( 0.f , 1.f)));

	vertices.push_back(VertexFormat(glm::vec3( -3.f, -0.2f, 0.f), 
									glm::vec4( 0.f ,  0.f , 1.f , 1.f), 
									glm::vec2( 0.f ,  0.f)));   

	vertices.push_back(VertexFormat(glm::vec3(3.f, 0.2f, 0.f),
									glm::vec4(1.f , 0.f , 0.f , 1.f), 
					                glm::vec2(1.f , 1.f)));

	
	vertices.push_back(VertexFormat(glm::vec3(3.f,   -0.2f, 0.f),
									glm::vec4(0.f ,  1.f , 0.f , 1.f),
									glm::vec2(1.f ,  0.f)));

	GLuint indices[] = 
	{ 
		0, 1, 2, 
		1, 2, 3
	};
	
	glBindVertexArray(vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, &vertices[0], GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// position attributes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (GLvoid*)0);
	
	// Colour attribue
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (GLvoid*)(offsetof(VertexFormat, VertexFormat::colour)));

	// UV attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	this->vao = vao;
	this->vbos.push_back(vbo);

}

void Quad::Draw()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}



void Quad::Update()
{

}
