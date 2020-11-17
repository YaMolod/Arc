#include "Arc.h"

#include "Arc/Platform/OpenGL/OpenGLShader.h"

#include "imgui.h"

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

		ARC::Ref<ARC::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(ARC::VertexBuffer::Create(vertices, sizeof(vertices)));

		vertexBuffer->SetLayout(
			{
				{ ARC::ShaderDataType::Float3, "a_Position"},
				{ ARC::ShaderDataType::Float4, "a_Color"}
			});
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };

		ARC::Ref<ARC::IndexBuffer> indexBuffer;
		indexBuffer.reset(ARC::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(ARC::Shader::Create(vertexSrc, fragmentSrc));

		float square[5 * 4] =
		{
			 -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			  0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			 -0.5f,  0.5f, 0.0f, 0.0f, 1.0f

		};

		m_SquareVA.reset(ARC::VertexArray::Create());
		ARC::Ref<ARC::VertexBuffer> squareVB;
		squareVB.reset(ARC::VertexBuffer::Create(square, sizeof(square)));

		squareVB->SetLayout(
			{
				{ ARC::ShaderDataType::Float3, "a_Position"},
				{ ARC::ShaderDataType::Float2, "a_TexCoord"}
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		ARC::Ref<ARC::IndexBuffer> squareIB;
		squareIB.reset(ARC::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSquareSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
			}
		)";

		std::string fragmentSquareSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			uniform vec3 u_Color;
			
			void main()
			{
				color = vec4(u_Color, 1.0f);
			}
		)";

		m_SquareShader.reset(ARC::Shader::Create(vertexSquareSrc, fragmentSquareSrc));

		std::string vertexTextureSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TextureCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			out vec2 v_TextureCoord;

			void main()
			{
				v_TextureCoord = a_TextureCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
			}
		)";

		std::string fragmentTextureSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec2 v_TextureCoord;

			uniform sampler2D u_Texture;
			
			void main()
			{
				color = texture(u_Texture, v_TextureCoord);
			}
		)";

		m_TextureShader.reset(ARC::Shader::Create(vertexTextureSrc, fragmentTextureSrc));
		
		m_Texture = ARC::Texture2D::Create("assets/textures/shrek_PNG2.png");

		std::dynamic_pointer_cast<ARC::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<ARC::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);

	}

	void OnUpdate(ARC::Timestep ts) override
	{
		if (ARC::Input::IskeyPressed(ARC_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (ARC::Input::IskeyPressed(ARC_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (ARC::Input::IskeyPressed(ARC_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (ARC::Input::IskeyPressed(ARC_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (ARC::Input::IskeyPressed(ARC_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (ARC::Input::IskeyPressed(ARC_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		ARC::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
		ARC::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		ARC::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<ARC::OpenGLShader>(m_SquareShader)->Bind();
		std::dynamic_pointer_cast<ARC::OpenGLShader>(m_SquareShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++) 
		{

			for (int x = 0; x < 20; x++)
			{
				glm::vec3 position(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * scale;
				
				ARC::Renderer::Submit(m_SquareShader, m_SquareVA, transform);
			}
		}

		m_Texture->Bind();

		ARC::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		//ARC::Renderer::Submit(m_Shader, m_VertexArray);

		ARC::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	virtual void OnEvent(ARC::Event& event) override
	{
		
	}

private:

	ARC::Ref<ARC::Shader> m_Shader;
	ARC::Ref<ARC::VertexArray> m_VertexArray;

	ARC::Ref<ARC::VertexArray> m_SquareVA;
	ARC::Ref<ARC::Shader> m_SquareShader, m_TextureShader;

	ARC::Ref<ARC::Texture2D> m_Texture;

	ARC::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
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