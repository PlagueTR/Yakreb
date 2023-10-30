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

			Yakreb::VertexBuffer *vertexBuffer = Yakreb::VertexBuffer::Create(vertices, sizeof(vertices));
			Yakreb::BufferLayout layout = {
				{Yakreb::ShaderDataType::Float3, "a_Position"},
				{Yakreb::ShaderDataType::Float4, "a_Color"}
			};
			vertexBuffer->SetLayout(layout);
			m_VertexArray->AddVertexBuffer(vertexBuffer);

			uint32_t indices[3] = { 0, 1, 2 };

			Yakreb::IndexBuffer* indexBuffer = Yakreb::IndexBuffer::Create(indices, 3);
			m_VertexArray->SetIndexBuffer(indexBuffer);

			std::string vertexSrc = R"(
				#version 330 core
			
				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec4 a_Color;

				uniform mat4 u_ViewProjection;
				uniform mat4 u_Transform;

				out vec4 v_Color;

				void main(){
					v_Color = a_Color;
					gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
				}
			)";

			std::string fragmentSrc = R"(
				#version 330 core
		
				layout(location = 0) out vec4 color;

				in vec4 v_Color;

				void main(){
					color = v_Color;
				}
			)";

			m_SquareVA = Yakreb::VertexArray::Create();
			float squareVertices[3 * 4] = {
				-0.75f, -0.75f, 0.0f,
				 0.75f, -0.75f, 0.0f,
				 0.75f,  0.75f, 0.0f,
				-0.75f,  0.75f, 0.0f
			};

			Yakreb::VertexBuffer *squareVB = Yakreb::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
			squareVB->SetLayout({
				{ Yakreb::ShaderDataType::Float3, "a_Position" }
				});

			m_SquareVA->AddVertexBuffer(squareVB);
			uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
			Yakreb::IndexBuffer *squareIB = Yakreb::IndexBuffer::Create(squareIndices, 6);
			m_SquareVA->SetIndexBuffer(squareIB);

			std::string blueShaderVertexSrc = R"(
				#version 330 core

				layout (location = 0) in vec3 a_Position;

				uniform mat4 u_ViewProjection;
				uniform mat4 u_Transform;

				void main(){
					gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
				}
			)";

			std::string blueShaderFragmentSrc = R"(
				#version 330 core

				layout (location = 0) out vec4 color;

				void main(){
					color = vec4(0.1, 0.1, 0.9, 1.0);
				}
			)";

			m_Shader = Yakreb::Shader::Create("Shader", vertexSrc, fragmentSrc);

			m_BlueShader = Yakreb::Shader::Create("BlueShader", blueShaderVertexSrc, blueShaderFragmentSrc);

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

			Yakreb::RenderCommand::SetClearColor({ m_rgb, m_rgb, m_rgb, 1 });
			Yakreb::RenderCommand::Clear();

			Yakreb::Renderer::BeginScene(m_OrthoCamera);

			Yakreb::Renderer::Submit(m_BlueShader, m_SquareVA,
				glm::rotate(glm::translate(glm::mat4(1.0f), m_SquarePosition), glm::radians(m_SquareRotation), glm::vec3(0.0f, 0.0f, 1.0f))
				* glm::scale(glm::mat4(1.0f), glm::vec3(0.7f)));

			Yakreb::Renderer::Submit(m_Shader, m_VertexArray);

			Yakreb::Renderer::EndScene();

		}

		void OnImGuiRender() override {
			
		}

		void OnEvent(Yakreb::Event& event) override {
			
		}

	private:
		float m_rgb = 30.0f / 255.0f;

		Yakreb::Shader* m_Shader;
		Yakreb::VertexArray* m_VertexArray;

		glm::vec3 m_SquarePosition = glm::vec3(0.0f);
		float m_SquareRotation = 0.0f;
		float m_SquareMoveSpeed = 1.0f;
		float m_SquareRotateSpeed = 30.0f;

		Yakreb::Shader* m_BlueShader;
		Yakreb::VertexArray* m_SquareVA;

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