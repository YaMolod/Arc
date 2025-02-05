#pragma once

#include "Arc/Renderer/RendererAPI.h"

namespace ARC
{

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray)override;
		virtual void Init() override;

		virtual void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
	};
}
