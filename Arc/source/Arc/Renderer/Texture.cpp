#include "arcpch.h"
#include "Texture.h"

#include "Arc/Platform/OpenGL/OpenGLTexture.h"
#include "Renderer.h"
namespace ARC
{

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:		ARC_CORE_ASSERT(false, "RendererAPI::NONE is not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLTexture2D>(path);
		}

		ARC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}