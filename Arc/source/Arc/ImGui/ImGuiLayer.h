#pragma once
#include "Arc/Core/Layer.h"
#include "Arc/Events/MouseEvent.h"
#include "Arc/Events/KeyEvent.h"
#include "Arc/Events/ApplicationEvent.h"

namespace ARC 
{

	class ARC_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}

