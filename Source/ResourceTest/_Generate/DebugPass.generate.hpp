#include "D:/Workspace/IlumEngine/Source/Runtime/Renderer/Private/BasePass/DebugPass.hpp"
#include <rttr/registration.h>

namespace Ilum_5048986834888425366
{
RTTR_REGISTRATION
{
    
    rttr::registration::class_<Ilum::DebugPass>("DebugPass")(rttr::metadata("RenderPass", "Debug Pass"), rttr::metadata("Category", "Base Pass"))
    
    
        .constructor<>()(rttr::policy::ctor::as_object)
        .method("CreateDesc", &Ilum::DebugPass::CreateDesc)
        .method("Create", &Ilum::DebugPass::Create)
    ;
}
}                                 