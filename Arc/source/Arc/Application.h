#pragma once

#include "Events/Event.h"
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
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
