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
		ARC_TRACE("{0}", event);
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