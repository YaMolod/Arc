#include "arcpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace ARC
{

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ARC::ShaderDataType::Float:	return GL_FLOAT;
		case ARC::ShaderDataType::Float2:	return GL_FLOAT;
		case ARC::ShaderDataType::Float3:	return GL_FLOAT;
		case ARC::ShaderDataType::Float4:	return GL_FLOAT;
		case ARC::ShaderDataType::Mat3:		return GL_FLOAT;
		case ARC::ShaderDataType::Mat4:		return GL_FLOAT;
		case ARC::ShaderDataType::Int:		return GL_INT;
		case ARC::ShaderDataType::Int2:		return GL_INT;
		case ARC::ShaderDataType::Int3:		return GL_INT;
		case ARC::ShaderDataType::Int4:		return GL_INT;
		case ARC::ShaderDataType::Bool:		return GL_INT;
		}

		ARC_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		ARC_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		ARC_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);
	}

	void ARC::OpenGLVertexArray::Bind() const
	{
		ARC_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
	}

	void ARC::OpenGLVertexArray::Unbind() const
	{
		ARC_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void ARC::OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) 
	{
		ARC_PROFILE_FUNCTION();

		ARC_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
		
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(), (const void*)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void ARC::OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) 
	{
		ARC_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}