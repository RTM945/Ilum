#pragma once
#include <rttr/registration.h>
#include "E:/Workspace/Ilum/Source/Ilum/Resource/ResourceMeta.hpp"
// This code is generated by meta generator
namespace NAMESPACE_9683295102319015798
{
RTTR_REGISTRATION
{
using namespace Ilum;

rttr::registration::enumeration<Ilum::ResourceType>("Ilum::ResourceType")
(
	rttr::value("Unknown", Ilum::ResourceType::Unknown),
	rttr::value("Texture", Ilum::ResourceType::Texture),
	rttr::value("Model", Ilum::ResourceType::Model),
	rttr::value("Scene", Ilum::ResourceType::Scene),
	rttr::value("RenderGraph", Ilum::ResourceType::RenderGraph)
);

rttr::registration::class_<Ilum::Meshlet::Bound>("Ilum::Meshlet::Bound")
	.property("center", &Ilum::Meshlet::Bound::center)
	.property("radius", &Ilum::Meshlet::Bound::radius)
	.property("cone_axis", &Ilum::Meshlet::Bound::cone_axis)
	.property("cone_cutoff", &Ilum::Meshlet::Bound::cone_cutoff)
	.constructor<>()(rttr::policy::ctor::as_object);

rttr::registration::class_<Ilum::Meshlet>("Ilum::Meshlet")
	.property("bound", &Ilum::Meshlet::bound)
	.property("indices_offset", &Ilum::Meshlet::indices_offset)
	.property("indices_count", &Ilum::Meshlet::indices_count)
	.property("vertices_offset", &Ilum::Meshlet::vertices_offset)
	.property("vertices_count", &Ilum::Meshlet::vertices_count)
	.property("meshlet_vertices_offset", &Ilum::Meshlet::meshlet_vertices_offset)
	.property("meshlet_primitive_offset", &Ilum::Meshlet::meshlet_primitive_offset)
	.constructor<>()(rttr::policy::ctor::as_object);

rttr::registration::class_<Ilum::Submesh>("Ilum::Submesh")
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
	.constructor<>()(rttr::policy::ctor::as_object);

SERIALIZER_REGISTER_TYPE(decltype(Ilum::Meshlet::Bound::center))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::Meshlet::Bound::radius))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::Meshlet::Bound::cone_axis))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::Meshlet::Bound::cone_cutoff))
SERIALIZER_REGISTER_TYPE(Ilum::Meshlet::Bound)
SERIALIZER_REGISTER_TYPE(decltype(Ilum::Meshlet::bound))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::Meshlet::indices_offset))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::Meshlet::indices_count))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::Meshlet::vertices_offset))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::Meshlet::vertices_count))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::Meshlet::meshlet_vertices_offset))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::Meshlet::meshlet_primitive_offset))
SERIALIZER_REGISTER_TYPE(Ilum::Meshlet)
SERIALIZER_REGISTER_TYPE(decltype(Ilum::Submesh::name))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::Submesh::index))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::Submesh::pre_transform))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::Submesh::aabb))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::Submesh::vertices_count))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::Submesh::vertices_offset))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::Submesh::indices_count))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::Submesh::indices_offset))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::Submesh::meshlet_count))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::Submesh::meshlet_offset))
SERIALIZER_REGISTER_TYPE(Ilum::Submesh)
}
}

//Generate for Serialization

namespace cereal
{
template <class Archive>
void serialize(Archive& archive, Ilum::Meshlet::Bound& v)
{
	archive(v.center, v.radius, v.cone_axis, v.cone_cutoff);
}

template <class Archive>
void serialize(Archive& archive, Ilum::Meshlet& v)
{
	archive(v.bound, v.indices_offset, v.indices_count, v.vertices_offset, v.vertices_count, v.meshlet_vertices_offset, v.meshlet_primitive_offset);
}

template <class Archive>
void serialize(Archive& archive, Ilum::Submesh& v)
{
	archive(v.name, v.index, v.pre_transform, v.aabb, v.vertices_count, v.vertices_offset, v.indices_count, v.indices_offset, v.meshlet_count, v.meshlet_offset);
}


}
