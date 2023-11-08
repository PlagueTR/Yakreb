#pragma once
#include "Yakreb/Core/GameTimer.h"

namespace Yakreb {

	class LinuxGameTimer : public GameTimer {
		public:
			LinuxGameTimer();
		protected:
			inline virtual void UpdateGameTimeImpl() override;

	};

}