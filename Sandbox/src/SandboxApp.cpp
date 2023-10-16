#include <Yakreb.h>
#include <Yakreb/EntryPoint.h>

class Sandbox : public Yakreb::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

Yakreb::Application* Yakreb::CreateApplication() {
	return new Sandbox();
}
