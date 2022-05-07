#include "Dindipch.h"
#include "Model.h"
#include "Utils/ModelLoader.h"

namespace Dindi
{
	//I will not take meshPath by reference because we can just use the root asset path macro with the actual asset file easier this way.
	//No difference between RESOURCES_PATH + std::string(path) and  RESOURCES_PATH path, the later we can have more simplicity.
	Model::Model(std::string meshPath, std::string vertexPath /*= DEFAULT_VERTEX_SHADER*/, std::string fragmentPath /*= DEFAULT_FRAGMENT_SHADER*/)
	{
		m_Mesh = new Mesh();
		m_Material = new Material(vertexPath, fragmentPath);
		ModelLoader::Load(meshPath, *this);
		
		//Register loaded data layout. (Vertex positions, normals, texture coords etc on the shader.
		m_Mesh->RegisterData();
	}

	Model::~Model()
	{
		delete m_Mesh;
		delete m_Material;
	}

}