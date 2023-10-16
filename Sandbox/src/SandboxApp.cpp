#include <Yakreb.h>
#include <Yakreb/EntryPoint.h>

class Sandbox : public Yakreb::Application {
public:
	Sandbox() {
		
		YGE_FATAL("{}", "Example fatal error from client!");
		YGE_ERROR("{}", "Example error from client!");
		YGE_WARN("{}", "Example warning from client!");
		YGE_INFO("{}", "Example info from client!");
		YGE_TRACE("{}", "Example trace from client!");

		YGE_ASSERT(5 > 10, "5 is not greater than 10!");
		YGE_ASSERT(5 < 10, "5 is not less than 10!");

	}

	~Sandbox() {

	}
};

Yakreb::Application* Yakreb::CreateApplication() {
	return new Sandbox();
}
