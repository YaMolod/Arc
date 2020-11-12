#include "arcpch.h"
#include "RenderCommand.h"

#include "Arc/Platform/OpenGL/OpenGLRendererAPI.h"

namespace ARC
{

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}