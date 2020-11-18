#include "arcpch.h"

#include "Shader.h"
#include "Arc/Platform/OpenGL/OpenGLShader.h"
#include "Renderer.h"

namespace ARC
{
	Shader* Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::NONE:		ARC_CORE_ASSERT(false, "RendererAPI::NONE is not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:		return new OpenGLShader(filepath);
		}

		ARC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::NONE:		ARC_CORE_ASSERT(false, "RendererAPI::NONE is not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:		return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		ARC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}