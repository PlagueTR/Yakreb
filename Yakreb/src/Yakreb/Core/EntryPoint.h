#pragma once

extern Yakreb::Application* Yakreb::CreateApplication();

int main(int argc, char** argv) {

	auto app = Yakreb::CreateApplication();

	app->Run();

	delete app;

}