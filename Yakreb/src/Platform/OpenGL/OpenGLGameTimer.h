#pragma once
#include "Yakreb/Core/GameTimer.h"

namespace Yakreb {

	class OpenGLGameTimer : public GameTimer {
		public:
			OpenGLGameTimer();

		protected:
			inline virtual void UpdateGameTimeImpl() override;

	};


}