#include "D:/Workspace/IlumEngine/Source/Runtime/Geometry/Public/Geometry/Bound/AABB.hpp"
#include <rttr/registration.h>

namespace Ilum_522277660429096422
{
RTTR_REGISTRATION
{
    
    rttr::registration::class_<Ilum::AABB>("AABB")
        .property("min", &Ilum::AABB::min)
        .property("max", &Ilum::AABB::max)
        .constructor<>()(rttr::policy::ctor::as_object)
        .constructor<const int &, const int &>()(rttr::policy::ctor::as_object)
    
        .method("Merge", rttr::select_overload<void(const int &)>(&Ilum::AABB::Merge))
        .method("Merge", rttr::select_overload<void(const int &)>(&Ilum::AABB::Merge))
        .method("Merge", rttr::select_overload<void(const Ilum::AABB &)>(&Ilum::AABB::Merge))
        .method("Transform", &Ilum::AABB::Transform)
        .method("Center", &Ilum::AABB::Center)
        .method("Scale", &Ilum::AABB::Scale)
    ;
}
}                                 