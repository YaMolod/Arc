#pragma once


#ifdef ARC_PLATFORM_WINDOWS

extern ARC::Application* ARC::CreateApplication();

int main(int argc, char** argv)
{
	ARC::Log::Init();
	ARC_CORE_WARN("Initialized Log!");
	ARC_INFO("Hello!");


	auto app = ARC::CreateApplication();
	app->Run();
	delete app;
}

#endif
