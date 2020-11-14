#include "Arc.h"

class TestLayer : public ARC::Layer
{
public:
	TestLayer()
		: Layer("Test"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{

		m_VertexArray.reset(ARC::VertexArray::Create());

		float vertices[3 * 7] =
		{
			 -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			  0.0f,  0.5f, 0.0f, 0.6f, 0.3f, 1.0f, 1.0f
		};

		std::shared_ptr<ARC::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(ARC::VertexBuffer::Create(vertices, sizeof(vertices)));

		vertexBuffer->SetLayout(
			{
				{ ARC::ShaderDataType::Float3, "a_Position"},
				{ ARC::ShaderDataType::Float4, "a_Color"}
			});
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };

		std::shared_ptr<ARC::IndexBuffer> indexBuffer;
		indexBuffer.reset(ARC::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			
			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0f);
				color = v_Color;
			}
		)";

		m_Shader.reset(new ARC::Shader(vertexSrc, fragmentSrc));

		float square[3 * 4] =
		{
			 -0.75f, -0.75f, 0.0f,
			  0.75f, -0.75f, 0.0f,
			  0.75f,  0.75f, 0.0f,
			 -0.75f,  0.75f, 0.0f

		};

		m_SquareVA.reset(ARC::VertexArray::Create());
		std::shared_ptr<ARC::VertexBuffer> squareVB;
		squareVB.reset(ARC::VertexBuffer::Create(square, sizeof(square)));

		squareVB->SetLayout(
			{
				{ ARC::ShaderDataType::Float3, "a_Position"}
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		std::shared_ptr<ARC::IndexBuffer> squareIB;
		squareIB.reset(ARC::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSquareSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			
			out vec3 v_Position;
			
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);
			}
		)";

		std::string fragmentSquareSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.4f, 0.2f, 0.6f, 1.0f);
			}
		)";

		m_SquareShader.reset(new ARC::Shader(vertexSquareSrc, fragmentSquareSrc));
	}

	void OnUpdate() override
	{
		if (ARC::Input::IskeyPressed(ARC_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed;
		else if (ARC::Input::IskeyPressed(ARC_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed;

		if (ARC::Input::IskeyPressed(ARC_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed;
		else if (ARC::Input::IskeyPressed(ARC_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed;

		if (ARC::Input::IskeyPressed(ARC_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed;
		if (ARC::Input::IskeyPressed(ARC_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed;

		ARC::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
		ARC::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		ARC::Renderer::BeginScene(m_Camera);

		ARC::Renderer::Submit(m_SquareShader, m_SquareVA);
		ARC::Renderer::Submit(m_Shader, m_VertexArray);

		ARC::Renderer::EndScene();

	}

	void OnEvent(ARC::Event& event) override
	{
		
	}

private:

	std::shared_ptr<ARC::Shader> m_Shader;
	std::shared_ptr<ARC::VertexArray> m_VertexArray;

	std::shared_ptr<ARC::VertexArray> m_SquareVA;
	std::shared_ptr<ARC::Shader> m_SquareShader;

	ARC::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.1f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 0.8f;

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