#include "arcpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Arc/Platform/OpenGL/OpenGLBuffer.h"

namespace ARC
{

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:		ARC_CORE_ASSERT(false, "RendererAPI::NONE is not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:		return new OpenGLVertexBuffer(vertices, size);
		}

		ARC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:		ARC_CORE_ASSERT(false, "RendererAPI::NONE is not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:		return new OpenGLIndexBuffer(indices, size);
		}

		ARC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}