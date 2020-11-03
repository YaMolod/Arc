#include "Arc.h"

class TestLayer : public ARC::Layer
{
public:
	TestLayer()
		: Layer("Test")
	{
	}

	void OnUpdate() override
	{
		ARC_INFO("TestLayer::Update");
	}

	void OnEvent(ARC::Event& event) override
	{
		if (event.GetEventType() == ARC::EventType::KeyPressed)
		{
			ARC::KeyPressedEvent& e = (ARC::KeyPressedEvent&)event;
			ARC_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public ARC::Application
{
public:
	Sandbox()
	{
		PushLayer(new TestLayer());
	}
	~Sandbox() {}
};

ARC::Application* ARC::CreateApplication()
{
	return new Sandbox();
}