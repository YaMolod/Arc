#pragma once

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Arc/ImGui/ImGuiLayer.h"
#include "LayerStack.h"
#include "Core.h"
#include "Window.h"

#include "Arc/Core/Timestep.h"

#include "Arc/Renderer/Shader.h"
#include "Arc/Renderer/Buffer.h"
#include "Arc/Renderer/VertexArray.h"
#include "Arc/Renderer/Renderer.h"
#include "Arc/Renderer/OrthographicCamera.h"

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
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		static Application* s_Instance;

		bool m_Running = true;
		bool m_Miniized = false;
		Scope<Window> m_Window;

		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;
	};

	// defined in CLIENT
	Application* CreateApplication();
}
