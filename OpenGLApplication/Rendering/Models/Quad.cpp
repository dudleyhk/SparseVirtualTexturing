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
	vertices.push_back(VertexFormat(glm::vec3( -.5f, .5f, 0.f),
									glm::vec4( 1.f , 1.f , 0.f , 1.f), 
									glm::vec2( 0.f , 1.f)));

	vertices.push_back(VertexFormat(glm::vec3( -.5f, -.5f, 0.f), 
									glm::vec4( 0.f ,  0.f , 1.f , 1.f), 
									glm::vec2( 0.f ,  0.f)));   

	vertices.push_back(VertexFormat(glm::vec3(.5f, .5f, 0.f),
									glm::vec4(1.f , 0.f , 0.f , 1.f), 
					                glm::vec2(1.f , 1.f)));

	
	vertices.push_back(VertexFormat(glm::vec3(.5f,   -.5f, 0.f),
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
	// TODO: This might be better encapsulated somewhere else.
	glm::mat4 view = glm::lookAt(
		glm::vec3(1.2f, 1.2f, 1.2f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 1.f));


	glm::mat4 trans = glm::mat4(1.0f); // create new mat and init to identity mat
	trans = glm::rotate(trans, glm::radians(180.f), glm::vec3(0.f, 0.f, 1.f)); // multiply rot of 180 degrees around z, by mat

	glm::vec4 result = trans * glm::vec4(1.f, 0.f, 0.f, 1.f);

	// TODO: Make this a debug.log system which can output the following easily. 
	//std::cout << "Rotation: (" << result.x << ", " << result.y << ", " << result.z << ") " << std::endl;


	GLuint uniTrans = glGetUniformLocation(program, "trans");
	glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

	GLint uniView = glGetUniformLocation(program, "view");
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

	//TODO: 800 / 600 ration should be in the InitGlut class
	glm::mat4 proj = glm::perspective(glm::radians(45.f), 800.f / 600.f, 1.f, 100.f);
	GLint uniProj = glGetUniformLocation(program, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));


	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}



void Quad::Update()
{

}
