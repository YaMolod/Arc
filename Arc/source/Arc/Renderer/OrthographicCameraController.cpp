#include "arcpch.h"
#include "OrthographicCameraController.h"

#include "Arc/Core/Input.h"
#include "Arc/Core/KeyCodes.h"

namespace ARC
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IskeyPressed(ARC_KEY_LEFT))
			m_CameraPosition.x -= m_CameraTreanslationSpeed * ts;
		else if (Input::IskeyPressed(ARC_KEY_RIGHT))
			m_CameraPosition.x += m_CameraTreanslationSpeed * ts;

		if (Input::IskeyPressed(ARC_KEY_UP))
			m_CameraPosition.y += m_CameraTreanslationSpeed * ts;
		else if (Input::IskeyPressed(ARC_KEY_DOWN))
			m_CameraPosition.y -= m_CameraTreanslationSpeed * ts;

		if (m_Rotation)
		{
			if (Input::IskeyPressed(ARC_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			else if (Input::IskeyPressed(ARC_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(ARC_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(ARC_BIND_EVENT_FN(OrthographicCameraController::OnWIndowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}

	bool OrthographicCameraController::OnWIndowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}
}