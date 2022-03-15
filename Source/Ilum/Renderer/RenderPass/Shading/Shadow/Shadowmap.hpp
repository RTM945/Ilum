#pragma once

#include "Graphics/Pipeline/PipelineState.hpp"

#include "Renderer/RenderGraph/RenderPass.hpp"

#include <glm/glm.hpp>

namespace Ilum::pass
{
class ShadowmapPass : public TRenderPass<ShadowmapPass>
{
  public:
	ShadowmapPass() = default;

	virtual void setupPipeline(PipelineState &state) override;

	virtual void resolveResources(ResolveState &resolve) override;

	virtual void render(RenderPassState &state) override;

	virtual void onImGui() override;

  private:
	struct
	{
		glm::mat4 transform = {};
		uint32_t  dynamic   = {};
		uint32_t  layer     = {};
	} m_push_block;

	int32_t m_current_layer = 0;

	VkExtent2D m_resolution = {2048, 2048};

	float m_depth_bias_constant = 4.f;
	float m_depth_bias_slope    = 1.75f;
};
}        // namespace Ilum::pass