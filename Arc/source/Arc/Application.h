#pragma once

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Arc/ImGui/ImGuiLayer.h"
#include "LayerStack.h"
#include "Core.h"
#include "Window.h"

#include "Arc/Renderer/Shader.h"
#include "Arc/Renderer/Buffer.h"

namespace ARC
{
	class  ARC_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
		bool OnWindowClose(WindowCloseEvent& e);
	private:

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		static Application* s_Instance;

		unsigned int m_VertexArray;

		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;

	};

	// defined in CLIENT
	Application* CreateApplication();
}
