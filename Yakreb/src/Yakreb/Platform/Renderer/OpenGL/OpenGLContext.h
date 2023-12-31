#pragma once

#include "Yakreb/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Yakreb {

	class OpenGLContext : public GraphicsContext {
		public:
			OpenGLContext(GLFWwindow* windowHandle);
			virtual ~OpenGLContext();

			virtual void Init() override;
			virtual void SwapBuffers() override;

		private:
			GLFWwindow *m_WindowHandle;

	};

}