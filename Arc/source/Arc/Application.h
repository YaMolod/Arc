#pragma once

#include "Core.h"

namespace Arc 
{
	class  ARC_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
