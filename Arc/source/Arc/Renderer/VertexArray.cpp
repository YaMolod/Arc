#include "arcpch.h"
#include "VertexArray.h"

#include "Arc/Platform/OpenGL/OpenGLVertexArray.h"
#include "Renderer.h"

namespace ARC
{

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:		ARC_CORE_ASSERT(false, "RendererAPI::NONE is not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:		return std::make_shared <OpenGLVertexArray>();
		}

		ARC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}