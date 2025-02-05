#pragma once

#include "RenderCommand.h"
#include "Renderer2D.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace ARC
{
	
	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray,
			const glm::mat4& transform = glm::mat4(1.0f));
		static void Init();
		static void OnWindowResize(uint32_t width, uint32_t height);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> m_SceneData;
	};
}
