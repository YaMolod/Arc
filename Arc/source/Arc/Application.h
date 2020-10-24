#pragma once

#include "Events/Event.h"
#include "Arc/Events/ApplicationEvent.h"
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
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// defined in CLIENT
	Application* CreateApplication();
}
