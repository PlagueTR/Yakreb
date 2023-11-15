#pragma once

namespace Yakreb {

	class GameTime {
		public:
			inline static float GetTimeScale() { return s_TimeScale; }
			inline static void SetTimeScale(float timeScale) { s_TimeScaleNext = std::max(0.0f, timeScale); }

			inline static float GetSeconds() { return s_RealTime; }
			inline static float GetMilliseconds() { return s_RealTime * 1000.0f; }

			inline static float GetDeltaTime() { return s_DeltaTime; }
			inline static float GetScaledDeltaTime() { return s_ScaledDeltaTime; }

		protected:

			static float s_RealTime;
			static float s_ScaledTime;

			static float s_TimeScale;
			static float s_TimeScaleNext;

			static float s_DeltaTime;
			static float s_ScaledDeltaTime;

	};

}