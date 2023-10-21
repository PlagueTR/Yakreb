#pragma once

#include "Yakreb/Core/GameTime.h"

namespace Yakreb {

	class GameTimer : public GameTime {
		public:
			inline static void UpdateGameTime() { s_Instance->UpdateGameTimeImpl(); }

		protected:
			inline virtual void UpdateGameTimeImpl() = 0;

			static GameTimer* s_Instance;
	};

}