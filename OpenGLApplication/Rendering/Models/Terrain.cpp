/*



*/
#include "Terrain.h"

#include "../../Dependencies/ASSIMP/PostProcess.h"
#include "../../Dependencies/ASSIMP/scene.h"
#include "../../Dependencies/ASSIMP/Importer.hpp"

using namespace Rendering::Models;

// TODO: in terrain constructor reserve height vec space.

void Terrain::Create()
{
	//Assimp::Importer importer;
	//auto scene = importer.ReadFile("../Resources/Model.obj", aiProcessPreset_TargetRealtime_Quality);



	//height.resize(width * depth, 0.f);
	//GLuint vertices_width = width;
	//GLuint vertices_depth = depth;

	//GLuint num_indices = (vertices_width - 1) * (vertices_depth * 2) + (vertices_width - 2) + (vertices_depth - 2);
	//indices.resize(num_indices, 0.f);

	//GLuint index = 0;
	//for(auto vx = 0; vx < (vertices_width - 1); vx++)
	//{
	//	for(auto vz = 0; vz < (vertices_depth - 1); vz++)
	//	{
	//		auto vy = GetHeight(vx, vz);
	//		auto v0 = glm::vec3(vx * step, vy, -vz * step);
	//		auto n0 = CalculateNormal(vx, vz);

	//		glm::vec3 v = glm::vec3(v0.x, v0.y, v0.z);
	//		glm::vec3 n = glm::vec3(n0.x, n0.y, n0.z);
	//		vertices.push_back(v);
	//		normals.push_back(n);
	//		indices.push_back(index++); // This may be wrong.
	//	}
	//}





}

float Terrain::GetHeight(const GLuint w, const GLuint d)
{
	return height[w * width + d]; // height[w * depth + d];
}



void Terrain::Draw()
{
	
}



void Terrain::Update()
{

}



const glm::vec3 Terrain::CalculateNormal(GLuint x, GLuint z)
{
	if(x == 0) x = 1;
	if(z == 0) z = 1;

	float hl = GetHeight(x - 1, z);
	float hr = GetHeight(x + 1, z);
	float hd = GetHeight(x, z + 1); /* Terrain expands towards -Z */
	float hu = GetHeight(x, z - 1);
	glm::vec3 n = glm::vec3(hl - hr, 2.0f, hd - hu);


	//ter_util_vec3_normalize(&n);
	//float m = ter_util_vec3_module(*p, 1, 1, 1);
	float m = sqrtf(n.x * n.x * 1 + n.y * n.y * 1 + n.z * n.z * 1);
	if(m > 0)
	{
		n.x /= m;
		n.y /= m;
		n.z /= m;
	}
	return n;
}



/*
// TODO: USe for streaming textures.
void
ter_terrain_set_heights_from_texture(TerTerrain *t, int texture,
float offset, float scale)
{
TerTextureManager *tex_mgr =
(TerTextureManager *) ter_cache_get("textures/manager");

SDL_Surface *image = ter_texture_manager_get_image(tex_mgr, texture);
uint8_t *pixels = (uint8_t *) image->pixels;
float scale_x = ((float) image->w) / (t->width - 1);
float scale_z = ((float) image->h) / (t->depth - 1);

for (int x = 0; x < t->width; x++) {
for (int z = 0; z < t->depth; z++) {
int img_x = (int) truncf(x * scale_x);
int img_y = (int) truncf(z * scale_z);
float h = pixels[img_y * image->pitch + img_x * 4];

// Normalize height to [-1, 1] 
h = h / 127.5 - 1.0f;

// Apply scale 
h *= scale;

//Apply height offset 
h += offset;

ter_terrain_set_height(t, x, z, h);
	  }
   }
}


*/