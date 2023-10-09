#include <Yakreb.h>

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
