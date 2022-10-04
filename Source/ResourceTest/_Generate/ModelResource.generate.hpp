#include "D:/Workspace/IlumEngine/Source/Runtime/Resource/Public/Resource/Resource/ModelResource.hpp"
#include <rttr/registration.h>

namespace Ilum_2748784985670380527
{
RTTR_REGISTRATION
{
    
    rttr::registration::class_<Ilum::Meshlet::Bound>("Bound")
        .property("center", &Ilum::Meshlet::Bound::center)
        .property("radius", &Ilum::Meshlet::Bound::radius)
        .property("cone_axis", &Ilum::Meshlet::Bound::cone_axis)
        .property("cone_cutoff", &Ilum::Meshlet::Bound::cone_cutoff)
    
        .constructor<>()(rttr::policy::ctor::as_object)
    
    ;
    rttr::registration::class_<Ilum::Meshlet>("Meshlet")
        .property("bound", &Ilum::Meshlet::bound)
        .property("indices_offset", &Ilum::Meshlet::indices_offset)
        .property("indices_count", &Ilum::Meshlet::indices_count)
        .property("vertices_offset", &Ilum::Meshlet::vertices_offset)
        .property("vertices_count", &Ilum::Meshlet::vertices_count)
        .property("meshlet_vertices_offset", &Ilum::Meshlet::meshlet_vertices_offset)
        .property("meshlet_primitive_offset", &Ilum::Meshlet::meshlet_primitive_offset)
    
        .constructor<>()(rttr::policy::ctor::as_object)
    
    ;
    rttr::registration::class_<Ilum::Submesh>("Submesh")
        .property("name", &Ilum::Submesh::name)
        .property("index", &Ilum::Submesh::index)
        .property("pre_transform", &Ilum::Submesh::pre_transform)
        .property("aabb", &Ilum::Submesh::aabb)
        .property("vertices_count", &Ilum::Submesh::vertices_count)
        .property("vertices_offset", &Ilum::Submesh::vertices_offset)
        .property("indices_count", &Ilum::Submesh::indices_count)
        .property("indices_offset", &Ilum::Submesh::indices_offset)
        .property("meshlet_count", &Ilum::Submesh::meshlet_count)
        .property("meshlet_offset", &Ilum::Submesh::meshlet_offset)
    
        .constructor<>()(rttr::policy::ctor::as_object)
    
    ;
}
}                                 