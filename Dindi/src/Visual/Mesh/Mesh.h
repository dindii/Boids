#pragma once
#include "Rendering/Object/Renderable.h"
#include "Math/vec2.h"
#include "Rendering/Texture/Texture2D.h"
#include "Visual/Material/Material.h"

namespace Dindi
{
	//#NOTE: Model will have many meshes support, but each mesh will have its own texture.
	
	class Mesh : public Renderable
	{
	public:
		Mesh(std::string vertexPath = DEFAULT_VERTEX_SHADER, std::string fragmentPath = DEFAULT_FRAGMENT_SHADER);
		Mesh(std::vector<vec3>&& vertices, std::string vertexPath = DEFAULT_VERTEX_SHADER, std::string fragmentPath = DEFAULT_FRAGMENT_SHADER) noexcept;
		Mesh(Material* material);
		
		~Mesh();

		inline uint32_t GetVertexCount() const { return (uint32_t)m_VertexPositions.size(); }

		void SetVertexPositionData(std::vector<vec3>&& vertexPosData)    noexcept { m_VertexPositions = vertexPosData; }
		void SetNormalData        (std::vector<vec3>&& normalData)       noexcept { m_Normal = normalData; }
		void SetTextureCoordData  (std::vector<vec2>&& textureCoordData) noexcept { m_TextureCoord = textureCoordData; }

		inline Material* GetMaterial() { return m_Material; }

		inline void SetMaterial(Material* mat) { m_Material = mat; }

		void RegisterData();
	private:
		std::vector<uint32_t> m_Indices;
		std::vector<vec3>     m_VertexPositions;
		std::vector<vec3>     m_Normal;
		std::vector<vec2>     m_TextureCoord;

		Material* m_Material;
	};
}
