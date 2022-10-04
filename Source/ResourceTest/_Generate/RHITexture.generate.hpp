#include "D:/Workspace/IlumEngine/Source/Runtime/RHI/Public/RHI/RHITexture.hpp"
#include <rttr/registration.h>

namespace Ilum_7125488288686408945
{
RTTR_REGISTRATION
{
    
    rttr::registration::class_<Ilum::TextureDesc>("TextureDesc")
        .property("name", &Ilum::TextureDesc::name)
        .property("width", &Ilum::TextureDesc::width)
        .property("height", &Ilum::TextureDesc::height)
        .property("depth", &Ilum::TextureDesc::depth)
        .property("mips", &Ilum::TextureDesc::mips)
        .property("layers", &Ilum::TextureDesc::layers)
        .property("samples", &Ilum::TextureDesc::samples)
        .property("format", &Ilum::TextureDesc::format)
        .property("usage", &Ilum::TextureDesc::usage)
        .property("external", &Ilum::TextureDesc::external)
    
        .constructor<>()(rttr::policy::ctor::as_object)
    
    ;
}
}                                 