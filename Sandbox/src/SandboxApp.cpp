#include <Yakreb.h>
#include <Yakreb/EntryPoint.h>

#include <imgui.h>

class MyLayer : public Yakreb::Layer {
	public:

		MyLayer(const std::string& name) : Layer(name) {

			YGE_INFO("Creating layer: {0}", name);

			m_OrthoCamera = Yakreb::OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f);

			m_VertexArray = Yakreb::VertexArray::Create();

			float vertices[3 * 7] = {
				-0.5f, -0.5f, 0.0f, 0.1f, 0.9f, 0.1f, 1.0f,
				 0.5f, -0.5f, 0.0f, 0.1f, 0.1f, 0.9f, 1.0f,
				 0.0f,  0.5f, 0.0f, 0.9f, 0.1f, 0.1f, 1.0f
			};

			Yakreb::Ref<Yakreb::VertexBuffer> vertexBuffer = Yakreb::VertexBuffer::Create(vertices, sizeof(vertices));
			Yakreb::BufferLayout layout = {
				{Yakreb::ShaderDataType::Float3, "a_Position"},
				{Yakreb::ShaderDataType::Float4, "a_Color"}
			};
			vertexBuffer->SetLayout(layout);
			m_VertexArray->AddVertexBuffer(vertexBuffer);

			uint32_t indices[3] = { 0, 1, 2 };

			Yakreb::Ref<Yakreb::IndexBuffer> indexBuffer = Yakreb::IndexBuffer::Create(indices, 3);
			m_VertexArray->SetIndexBuffer(indexBuffer);

			m_SquareVA = Yakreb::VertexArray::Create();
			float squareVertices[3 * 4] = {
				-0.5f, -0.5f, 0.0f,
				 0.5f, -0.5f, 0.0f,
				 0.5f,  0.5f, 0.0f,
				-0.5f,  0.5f, 0.0f
			};

			Yakreb::Ref<Yakreb::VertexBuffer> squareVB = Yakreb::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
			squareVB->SetLayout({
				{ Yakreb::ShaderDataType::Float3, "a_Position" }
				});

			m_SquareVA->AddVertexBuffer(squareVB);
			uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
			Yakreb::Ref<Yakreb::IndexBuffer> squareIB = Yakreb::IndexBuffer::Create(squareIndices, 6);
			m_SquareVA->SetIndexBuffer(squareIB);

			m_Shader = Yakreb::Shader::Create("Resources/Shaders/ColorShader.glsl");

			m_BlueShader = Yakreb::Shader::Create("Resources/Shaders/BlueShader.glsl");

			Yakreb::Renderer::SetClearColor({ m_rgb, m_rgb, m_rgb, 1 });

		}

		~MyLayer() {
		
		}

		void OnUpdate() override {

			float deltaTime = Yakreb::GameTime::GetDeltaTime();

			// Camera Movement
			if (Yakreb::Input::IsKeyPressed(Yakreb::Key::W))
				m_OrthoCamera.SetPosition(m_OrthoCamera.GetPosition() + glm::vec3(0.0f, m_CameraMoveSpeed * deltaTime, 0.0f));
			if (Yakreb::Input::IsKeyPressed(Yakreb::Key::S))
				m_OrthoCamera.SetPosition(m_OrthoCamera.GetPosition() - glm::vec3(0.0f, m_CameraMoveSpeed * deltaTime, 0.0f));

			if (Yakreb::Input::IsKeyPressed(Yakreb::Key::A))
				m_OrthoCamera.SetPosition(m_OrthoCamera.GetPosition() - glm::vec3(m_CameraMoveSpeed * deltaTime, 0.0f, 0.0f));
			if (Yakreb::Input::IsKeyPressed(Yakreb::Key::D))
				m_OrthoCamera.SetPosition(m_OrthoCamera.GetPosition() + glm::vec3(m_CameraMoveSpeed * deltaTime, 0.0f, 0.0f));

			// Camera Rotation
			if (Yakreb::Input::IsKeyPressed(Yakreb::Key::Q))
				m_OrthoCamera.SetRotation(m_OrthoCamera.GetRotation() + m_CameraRotateSpeed * deltaTime);
			if (Yakreb::Input::IsKeyPressed(Yakreb::Key::E))
				m_OrthoCamera.SetRotation(m_OrthoCamera.GetRotation() - m_CameraRotateSpeed * deltaTime);

			// Camera Zoom
			if (Yakreb::Input::IsKeyPressed(Yakreb::Key::KPSubtract))
				m_OrthoCamera.SetZoom(m_OrthoCamera.GetZoom() + m_CameraZoomSpeed * deltaTime);
			if (Yakreb::Input::IsKeyPressed(Yakreb::Key::KPAdd))
				m_OrthoCamera.SetZoom(m_OrthoCamera.GetZoom() - m_CameraZoomSpeed * deltaTime);

			// Square Movement
			if (Yakreb::Input::IsKeyPressed(Yakreb::Key::Up))
				m_SquarePosition.y += m_SquareMoveSpeed * deltaTime;
			if (Yakreb::Input::IsKeyPressed(Yakreb::Key::Down))
				m_SquarePosition.y -= m_SquareMoveSpeed * deltaTime;

			if (Yakreb::Input::IsKeyPressed(Yakreb::Key::Left))
				m_SquarePosition.x -= m_SquareMoveSpeed * deltaTime;
			if (Yakreb::Input::IsKeyPressed(Yakreb::Key::Right))
				m_SquarePosition.x += m_SquareMoveSpeed * deltaTime;

			// Square Rotation
			if (Yakreb::Input::IsKeyPressed(Yakreb::Key::Z))
				m_SquareRotation += m_SquareRotateSpeed * deltaTime;
			if (Yakreb::Input::IsKeyPressed(Yakreb::Key::X))
				m_SquareRotation -= m_SquareRotateSpeed * deltaTime;

			m_SquareTransform = glm::rotate(glm::translate(glm::mat4(1.0f), m_SquarePosition), glm::radians(m_SquareRotation), glm::vec3(0.0f, 0.0f, 1.0f));

			Yakreb::Renderer::Clear();

			Yakreb::Renderer::BeginScene(m_OrthoCamera);

			Yakreb::Renderer::Draw(m_BlueShader, m_SquareVA, m_SquareTransform);

			Yakreb::Renderer::Draw(m_Shader, m_VertexArray);

			Yakreb::Renderer::EndScene();

		}

		void OnImGuiRender() override {
			Yakreb::AllocationStats globalMemoryStats = Yakreb::Allocator::GetGlobalAllocationStats();
			Yakreb::AllocationStatsVec memoryStatsByCategories = Yakreb::Allocator::GetAllocationStatsVec();
			ImGui::Begin("Memory Statistics");
			ImGui::Text("Total allocated: %lu bytes", globalMemoryStats.TotalAllocated);
			ImGui::Text("Total freed: %lu bytes", globalMemoryStats.TotalFreed);
			ImGui::Text("In use: %lu bytes", globalMemoryStats.TotalAllocated - globalMemoryStats.TotalFreed);
			if (memoryStatsByCategories.size()) {
				ImGui::Separator();
				ImGui::Text("Memory Usage by Categories");
				for (auto& [category, stats] : memoryStatsByCategories) {
					ImGui::Text("");
					ImGui::Text("%s", category);
					ImGui::Text("  Active instances: %u", stats.Instances);
					ImGui::Text("  Total allocated: %lu bytes", stats.TotalAllocated);
					ImGui::Text("  Total freed: %lu bytes", stats.TotalFreed);
					ImGui::Text("  In use: %lu bytes", stats.TotalAllocated - stats.TotalFreed);
				}
			}
			ImGui::End();
		}

		void OnEvent(Yakreb::Event& event) override {
			
		}

	private:
		float m_rgb = 30.0f / 255.0f;

		Yakreb::Ref<Yakreb::Shader> m_Shader;
		Yakreb::Ref<Yakreb::VertexArray> m_VertexArray;

		glm::vec3 m_SquarePosition = glm::vec3(0.0f);
		float m_SquareRotation = 0.0f;
		float m_SquareMoveSpeed = 1.0f;
		float m_SquareRotateSpeed = 30.0f;
		glm::mat4 m_SquareTransform;

		Yakreb::Ref<Yakreb::Shader> m_BlueShader;
		Yakreb::Ref<Yakreb::VertexArray> m_SquareVA;

		Yakreb::OrthographicCamera m_OrthoCamera;
		float m_CameraMoveSpeed = 2.0f;
		float m_CameraRotateSpeed = 45.0f;
		float m_CameraZoomSpeed = 1.0f;

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