#include "D:/Workspace/IlumEngine/Source/Runtime/Scene/Public/Scene/Component/TagComponent.hpp"
#include <rttr/registration.h>

namespace Ilum_2842031511319089340
{
RTTR_REGISTRATION
{
    
    rttr::registration::class_<Ilum::TagComponent>("TagComponent")
        .property("tag", &Ilum::TagComponent::tag)
    
        .constructor<>()(rttr::policy::ctor::as_object)
    
    ;
}
}                                 