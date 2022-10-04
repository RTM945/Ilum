#include "D:/Workspace/IlumEngine/Source/Runtime/Resource/Public/Resource/Resource.hpp"
#include <rttr/registration.h>

namespace Ilum_13350109207677449565
{
RTTR_REGISTRATION
{
    rttr::registration::enumeration<Ilum::ResourceType>("ResourceType")
    (
        rttr::value("None", Ilum::ResourceType::None),
        rttr::value("Model", Ilum::ResourceType::Model),
        rttr::value("Texture", Ilum::ResourceType::Texture),
        rttr::value("Scene", Ilum::ResourceType::Scene),
        rttr::value("RenderGraph", Ilum::ResourceType::RenderGraph)
    );
    
}
}                                 