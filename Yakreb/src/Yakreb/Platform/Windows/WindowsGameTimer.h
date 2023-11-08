#pragma once
#include "Yakreb/Core/GameTimer.h"

namespace Yakreb {

	class WindowsGameTimer : public GameTimer {
		public:
			WindowsGameTimer();
		protected:
			inline virtual void UpdateGameTimeImpl() override;

	};

}