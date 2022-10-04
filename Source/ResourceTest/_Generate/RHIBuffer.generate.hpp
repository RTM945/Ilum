#include "D:/Workspace/IlumEngine/Source/Runtime/RHI/Public/RHI/RHIBuffer.hpp"
#include <rttr/registration.h>

namespace Ilum_11197827010425330880
{
RTTR_REGISTRATION
{
    
    rttr::registration::class_<Ilum::BufferDesc>("BufferDesc")
        .property("name", &Ilum::BufferDesc::name)
        .property("usage", &Ilum::BufferDesc::usage)
        .property("memory", &Ilum::BufferDesc::memory)
        .property("size", &Ilum::BufferDesc::size)
        .property("stride", &Ilum::BufferDesc::stride)
        .property("count", &Ilum::BufferDesc::count)
    
        .constructor<>()(rttr::policy::ctor::as_object)
    
    ;
}
}                                 