#pragma once

#include "Arc.h"

#include <chrono>


class Sandbox2D : public ARC::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(ARC::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(ARC::Event& e) override;

private:
	ARC::OrthographicCameraController m_CameraController;
	ARC::Ref<ARC::Shader> m_Shader;
	ARC::Ref<ARC::VertexArray> m_SquareVA;
	ARC::Ref<ARC::Texture2D> m_Texture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

};

