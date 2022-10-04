#include "D:/Workspace/IlumEngine/Source/Runtime/Scene/Public/Scene/Component/StaticMeshComponent.hpp"
#include <rttr/registration.h>

namespace Ilum_14106886677369500199
{
RTTR_REGISTRATION
{
    
    rttr::registration::class_<Ilum::StaticMeshComponent>("StaticMeshComponent")
        .property("uuid", &Ilum::StaticMeshComponent::uuid)
        .property("materials", &Ilum::StaticMeshComponent::materials)
    
        .constructor<>()(rttr::policy::ctor::as_object)
    
    ;
}
}                                 