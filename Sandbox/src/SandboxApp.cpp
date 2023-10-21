#include <Yakreb.h>
#include <Yakreb/EntryPoint.h>

#include <imgui.h>

class MyLayer : public Yakreb::Layer {
	public:
		MyLayer(const std::string& name) : Layer(name) {
			YGE_INFO("Creating layer: {0}", name);
		}

		~MyLayer() {
		
		}

		void OnUpdate() override {
			if (Yakreb::Input::IsKeyPressed(Yakreb::Key::Space)) {
 				YGE_TRACE("{}", "Space key is held down!");
			}
		}

		void OnImGuiRender() override {
			static bool show = true;
			ImGui::ShowDemoWindow(&show);
			ImGui::Begin("Test Window");
				ImGui::Text("Hello from test window!");
			ImGui::End();
		}

		void OnEvent(Yakreb::Event& event) override {
			
		}
};

class Sandbox : public Yakreb::Application {
	public:
		Sandbox() {

			MyLayer* layer = new MyLayer("Test Layer");
			PushLayer(layer);

		}

		~Sandbox() {

		}
};

Yakreb::Application* Yakreb::CreateApplication() {
	return new Sandbox();
}