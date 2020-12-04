#include "Sandbox2D.h"

#include "imgui.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Arc/Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{

}

void Sandbox2D::OnAttach()
{
	
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(ARC::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	ARC::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
	ARC::RenderCommand::Clear();

	ARC::Renderer2D::BeginScene(m_CameraController.GetCamera());
	ARC::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	ARC::Renderer2D::DrawQuad({ 1.0f, 1.0f }, { 0.7f, 0.7f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	ARC::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Color settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(ARC::Event& e)
{
	m_CameraController.OnEvent(e);
}
