#include "yakrebpch.h"
#include "Yakreb/Core/Application.h"

#include <iostream>

namespace Yakreb {

	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {
		std::cout << "Yakreb game engine running!\n";
		while (true) { }
	}

}