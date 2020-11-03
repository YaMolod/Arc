#pragma once

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Arc/ImGui/ImGuiLayer.h"
#include "LayerStack.h"
#include "Core.h"
#include "Window.h"

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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		static Application* s_Instance;
	};

	// defined in CLIENT
	Application* CreateApplication();
}
