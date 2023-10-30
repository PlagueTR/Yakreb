#pragma once
#include "Yakreb/Core/Input/Input.h"

namespace Yakreb {

	class LinuxInput : public Input {
		public:
			LinuxInput();

		protected:
			inline virtual bool IsKeyPressedImpl(Key key) override;
			inline virtual bool IsMouseButtonPressedImpl(Button button) override;

			inline virtual glm::vec2 GetMousePositionImpl() override;

	};

}