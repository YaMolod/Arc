#include "Sandbox2D.h"

#include "imgui.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Arc/Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

// Load textures here

void Sandbox2D::OnAttach()
{
	ARC_PROFILE_FUNCTION();

	m_Texture = ARC::Texture2D::Create("assets/textures/Checkerboard.jpg");
}

void Sandbox2D::OnDetach()
{
}

// Render here

void Sandbox2D::OnUpdate(ARC::Timestep ts)
{
	ARC_PROFILE_FUNCTION();

	m_CameraController.OnUpdate(ts);

	ARC::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
	ARC::RenderCommand::Clear();

	{
		ARC_PROFILE_SCOPE("Renderer Draw");
		ARC::Renderer2D::BeginScene(m_CameraController.GetCamera());
		ARC::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		ARC::Renderer2D::DrawQuad({ 1.0f, 1.0f }, { 0.7f, 0.7f }, m_SquareColor);
		ARC::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_Texture, 10.f, glm::vec4(1.0f, 0.9f, 0.9f, 1.0f));
		ARC::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	ARC_PROFILE_FUNCTION();

	ImGui::Begin("Color settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(ARC::Event& e)
{
	m_CameraController.OnEvent(e);
}
