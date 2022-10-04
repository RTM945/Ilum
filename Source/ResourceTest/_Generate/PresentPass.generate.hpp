#include "D:/Workspace/IlumEngine/Source/Runtime/Renderer/Private/BasePass/PresentPass.hpp"
#include <rttr/registration.h>

namespace Ilum_14991761520804769406
{
RTTR_REGISTRATION
{
    
    rttr::registration::class_<Ilum::PresentPass>("PresentPass")(rttr::metadata("RenderPass", "Present Pass"), rttr::metadata("Category", "Base Pass"))
    
    
        .constructor<>()(rttr::policy::ctor::as_object)
        .method("CreateDesc", &Ilum::PresentPass::CreateDesc)
        .method("Create", &Ilum::PresentPass::Create)
    ;
}
}                                 