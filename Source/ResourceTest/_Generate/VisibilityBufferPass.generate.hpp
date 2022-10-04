#include "D:/Workspace/IlumEngine/Source/Runtime/Renderer/Private/BasePass/VisibilityBufferPass.hpp"
#include <rttr/registration.h>

namespace Ilum_6905955234282748467
{
RTTR_REGISTRATION
{
    
    rttr::registration::class_<Ilum::VisibilityBufferPass>("VisibilityBufferPass")(rttr::metadata("RenderPass", "Visibility Buffer Pass"), rttr::metadata("Category", "Base Pass"))
    
    
        .constructor<>()(rttr::policy::ctor::as_object)
        .method("CreateDesc", &Ilum::VisibilityBufferPass::CreateDesc)
        .method("Create", &Ilum::VisibilityBufferPass::Create)
    ;
}
}                                 