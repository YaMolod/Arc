#include "Application.h"

#include "Arc/Events/ApplicationEvent.h"
#include "Log.h"

namespace ARC
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		ARC_TRACE(e);

		while (true);
	}
}
