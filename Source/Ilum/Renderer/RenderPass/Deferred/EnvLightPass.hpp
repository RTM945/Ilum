#pragma once

#include "Graphics/Pipeline/PipelineState.hpp"

#include "Renderer/RenderGraph/RenderPass.hpp"

namespace Ilum::pass
{
class EnvLightPass : public TRenderPass<EnvLightPass>
{
  public:
	EnvLightPass();

	virtual void setupPipeline(PipelineState &state) override;

	virtual void resolveResources(ResolveState &resolve) override;

	virtual void render(RenderPassState &state) override;

  private:
	Buffer m_vertex_buffer;
};
}        // namespace Ilum::pass