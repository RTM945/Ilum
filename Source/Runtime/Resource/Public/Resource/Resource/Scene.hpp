#pragma once

#include "../Resource.hpp"

#include <RHI/RHIContext.hpp>

namespace Ilum
{
class Scene;

template <>
class EXPORT_API Resource<ResourceType::Scene> final : public IResource
{
  public:
	Resource(RHIContext *rhi_context, const std::string &name);

	Resource(RHIContext *rhi_context, const std::string &name, Scene *scene);

	virtual ~Resource() override = default;

	void Update(Scene *scene);

	void Save(Scene *scene);
};
}        // namespace Ilum