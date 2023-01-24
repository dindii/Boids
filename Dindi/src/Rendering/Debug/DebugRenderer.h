#pragma once
#include "Math/vec3.h"
#include "Visual/Model/Model.h"

//#IMPORTANT: - Use it only for debugging purposes!
//This debug renderer is not meant to be fast but flexible and immediate. It will issue a draw call everytime you call "Draw()"
//as well as upload some uniforms. Keep in mind that this must be only used in debug mode and it will be stripped in other build types.

namespace Dindi
{
	namespace Debug
	{
		enum EDebugShape
		{
			NONE = -1,
			
			CUBE,
			LINE,

			MAX
		};

		enum EDebugRenderFlags : uint32_t
		{
			DEFAULT          = BIT(0),
			WIREFRAME        = BIT(1),
			NO_DEPTH_TESTING = BIT(2)
		};

		class DebugRenderer
		{
		public:
			static void Init();
#ifdef DINDI_DEBUG
			/*
			* @briefing: Draws a shape in the desired position, with the desired color.
			* @param - The desired shape to draw (CUBEs, LINEs etc)
			* @param - Position of the shape
			* @param [OPTIONAL] - This is used for LINES only, it is the end of the line. Ignore if you are not using LINE as the shape.
			* @param - Color of the shape
			* @param - Size of the shape. If the shape is a LINE, it will be the line thickness
			* @param - Flags to render. You can have WIREFRAME mode and NO DEPTH TESTING that will always pass the depth test (it will be in front of everything).
			*/
			static void DrawShape(EDebugShape shape, const vec3& pos, const vec3& secondPos, const vec3& color, float size, uint32_t flags = EDebugRenderFlags::DEFAULT);
#else
			static void DrawShape(EDebugShape shape, const vec3& pos, const vec3& secondPos, const vec3& color, float size, uint32_t flags = EDebugRenderFlags::DEFAULT) {};
#endif
		private:
			static Model* m_DebugShapes[Debug::EDebugShape::MAX];
		};
	}

}