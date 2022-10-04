#include "D:/Workspace/IlumEngine/Source/Runtime/Scene/Public/Scene/Component/TransformComponent.hpp"
#include <rttr/registration.h>

namespace Ilum_3101569802041024508
{
RTTR_REGISTRATION
{
    
    rttr::registration::class_<Ilum::TransformComponent>("TransformComponent")
        .property("translation", &Ilum::TransformComponent::translation)
        .property("rotation", &Ilum::TransformComponent::rotation)
        .property("scale", &Ilum::TransformComponent::scale)
        .property("local_transform", &Ilum::TransformComponent::local_transform)
        .property("world_transform", &Ilum::TransformComponent::world_transform)
    
        .constructor<>()(rttr::policy::ctor::as_object)
    
    ;
}
}                                 