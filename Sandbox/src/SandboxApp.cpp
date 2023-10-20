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
			YGE_TRACE("{0}::Update", GetName());
			YGE_TRACE("Total time: {0:.4f}s, delta time: {1:.2f}ms", Yakreb::GameTime::GetSeconds(), Yakreb::GameTime::GetDeltaTime() * 1000.0f);
		}

		void OnImGuiRender() override {
			static bool show = true;
			ImGui::ShowDemoWindow(&show);
			ImGui::Begin("Test Window");
				ImGui::Text("Hello from test window!");
			ImGui::End();
		}

		void OnEvent(Yakreb::Event& event) override {
			YGE_TRACE("{0} -> {1}", GetName(), event);
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