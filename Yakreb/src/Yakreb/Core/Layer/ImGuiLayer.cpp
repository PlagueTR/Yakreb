#include "yakrebpch.h"
#include "ImGuiLayer.h"

#include "Yakreb/Renderer/RendererAPI.h"

#include "Yakreb/Platform/Renderer/OpenGL/OpenGLImGuiLayer.h"

namespace Yakreb {

    ImGuiLayer* ImGuiLayer::Create(const std::string& name) {
        
        switch (RendererAPI::GetAPI()) {
            default:
                YGE_CORE_ASSERT(false, CoreError::Renderer::YGE_NONE_RENDERER_API);
                RendererAPI::SetAPI(RendererAPI::API::OpenGL);
                [[fallthrough]];
            case RendererAPI::API::OpenGL:
                return new OpenGLImGuiLayer(name);
        }

    }

}