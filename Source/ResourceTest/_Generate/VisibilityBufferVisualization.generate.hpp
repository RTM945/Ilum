#include "D:/Workspace/IlumEngine/Source/Runtime/Renderer/Private/BasePass/VisibilityBufferVisualization.hpp"
#include <rttr/registration.h>

namespace Ilum_4684384344593563646
{
RTTR_REGISTRATION
{
    
    rttr::registration::class_<Ilum::VisibilityBufferVisualization>("VisibilityBufferVisualization")(rttr::metadata("RenderPass", "Visibility Buffer Visualization"), rttr::metadata("Category", "Visualization"))
    
    
        .constructor<>()(rttr::policy::ctor::as_object)
        .method("CreateDesc", &Ilum::VisibilityBufferVisualization::CreateDesc)
        .method("Create", &Ilum::VisibilityBufferVisualization::Create)
    ;
}
}                                 