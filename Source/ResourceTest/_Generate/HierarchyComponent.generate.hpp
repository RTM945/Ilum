#include "D:/Workspace/IlumEngine/Source/Runtime/Scene/Public/Scene/Component/HierarchyComponent.hpp"
#include <rttr/registration.h>

namespace Ilum_18430940071621980477
{
RTTR_REGISTRATION
{
    
    rttr::registration::class_<Ilum::HierarchyComponent>("HierarchyComponent")
        .property("parent", &Ilum::HierarchyComponent::parent)
        .property("first", &Ilum::HierarchyComponent::first)
        .property("next", &Ilum::HierarchyComponent::next)
        .property("prev", &Ilum::HierarchyComponent::prev)
    
        .constructor<>()(rttr::policy::ctor::as_object)
    
    ;
}
}                                 