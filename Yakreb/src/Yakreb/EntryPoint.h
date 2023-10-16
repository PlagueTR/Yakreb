#pragma once

extern Yakreb::Application* Yakreb::CreateApplication();

int main(int argc, char** argv) {

	Yakreb::InitializeCore();

	auto app = Yakreb::CreateApplication();

	app->Run();

	delete app;

	Yakreb::ShutdownCore();

}