#include "Arc.h"

class Sandbox : public ARC::Application
{
public:
	Sandbox() {}
	~Sandbox() {}
};

ARC::Application* ARC::CreateApplication()
{
	return new Sandbox();
}