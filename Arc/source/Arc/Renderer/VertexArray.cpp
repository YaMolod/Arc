#include "arcpch.h"

#include "VertexArray.h"
#include "Arc/Platform/OpenGL/OpenGLVertexArray.h"
#include "Renderer.h"

namespace ARC
{

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::NONE:		ARC_CORE_ASSERT(false, "RendererAPI::NONE is not supported!"); return nullptr;
		case RendererAPI::OpenGL:	return new OpenGLVertexArray();
		}

		ARC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}