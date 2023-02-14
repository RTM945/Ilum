#include "Resource/SkinnedMesh.hpp"

#include <RHI/RHIContext.hpp>

namespace Ilum
{
struct Resource<ResourceType::SkinnedMesh>::Impl
{
	size_t vertex_count  = 0;
	size_t index_count   = 0;
	size_t meshlet_count = 0;
	size_t bone_count    = 0;

	std::unique_ptr<RHIBuffer> vertex_buffer       = nullptr;
	std::unique_ptr<RHIBuffer> index_buffer        = nullptr;
	std::unique_ptr<RHIBuffer> meshlet_buffer      = nullptr;
	std::unique_ptr<RHIBuffer> meshlet_data_buffer = nullptr;
};

Resource<ResourceType::SkinnedMesh>::Resource(RHIContext *rhi_context, const std::string &name) :
    IResource(rhi_context, name, ResourceType::SkinnedMesh)
{
}

Resource<ResourceType::SkinnedMesh>::Resource(RHIContext *rhi_context, const std::string &name, std::vector<SkinnedVertex> &&vertices, std::vector<uint32_t> &&indices, std::vector<Meshlet> &&meshlets, std::vector<uint32_t> &&meshletdata) :
    IResource(name)
{
	m_impl = new Impl;
	Update(rhi_context, std::move(vertices), std::move(indices), std::move(meshlets), std::move(meshletdata));
}

Resource<ResourceType::SkinnedMesh>::~Resource()
{
	delete m_impl;
}

bool Resource<ResourceType::SkinnedMesh>::Validate() const
{
	return m_impl != nullptr;
}

void Resource<ResourceType::SkinnedMesh>::Load(RHIContext *rhi_context)
{
	m_impl = new Impl;

	std::vector<uint8_t>       thumbnail_data;
	std::vector<SkinnedVertex> vertices;
	std::vector<uint32_t>      indices;
	std::vector<Meshlet>       meshlets;
	std::vector<uint32_t>      meshlet_data;

	DESERIALIZE(fmt::format("Asset/Meta/{}.{}.asset", m_name, (uint32_t) ResourceType::SkinnedMesh), thumbnail_data, vertices, indices, meshlets, meshlet_data);

	Update(rhi_context, std::move(vertices), std::move(indices), std::move(meshlets), std::move(meshlet_data));
}

RHIBuffer *Resource<ResourceType::SkinnedMesh>::GetVertexBuffer() const
{
	return m_impl->vertex_buffer.get();
}

RHIBuffer *Resource<ResourceType::SkinnedMesh>::GetIndexBuffer() const
{
	return m_impl->index_buffer.get();
}

RHIBuffer *Resource<ResourceType::SkinnedMesh>::GetMeshletBuffer() const
{
	return m_impl->meshlet_buffer.get();
}

RHIBuffer *Resource<ResourceType::SkinnedMesh>::GetMeshletDataBuffer() const
{
	return m_impl->meshlet_data_buffer.get();
}

size_t Resource<ResourceType::SkinnedMesh>::GetVertexCount() const
{
	return m_impl->vertex_count;
}

size_t Resource<ResourceType::SkinnedMesh>::GetIndexCount() const
{
	return m_impl->index_count;
}

size_t Resource<ResourceType::SkinnedMesh>::GetMeshletCount() const
{
	return m_impl->meshlet_count;
}

size_t Resource<ResourceType::SkinnedMesh>::GetBoneCount() const
{
	return m_impl->bone_count;
}

void Resource<ResourceType::SkinnedMesh>::Update(RHIContext *rhi_context, std::vector<Resource<ResourceType::SkinnedMesh>::SkinnedVertex> &&vertices, std::vector<uint32_t> &&indices, std::vector<Meshlet> &&meshlets, std::vector<uint32_t> &&meshletdata)
{
	m_impl->vertex_count  = vertices.size();
	m_impl->index_count   = indices.size();
	m_impl->meshlet_count = meshlets.size();

	std::unordered_set<int32_t> bone_set;
	for (auto &v : vertices)
	{
		for (uint32_t i = 0; i < 4; i++)
		{
			if (v.bones[i] != -1)
			{
				bone_set.insert(v.bones[i]);
			}
		}
	}
	m_impl->bone_count = bone_set.size();

	m_impl->vertex_buffer       = rhi_context->CreateBuffer<SkinnedVertex>(vertices.size(), RHIBufferUsage::Vertex | RHIBufferUsage::UnorderedAccess | RHIBufferUsage::Transfer, RHIMemoryUsage::GPU_Only);
	m_impl->index_buffer        = rhi_context->CreateBuffer<uint32_t>(indices.size(), RHIBufferUsage::Index | RHIBufferUsage::UnorderedAccess | RHIBufferUsage::Transfer, RHIMemoryUsage::GPU_Only);
	m_impl->meshlet_data_buffer = rhi_context->CreateBuffer<uint32_t>(meshletdata.size(), RHIBufferUsage::UnorderedAccess | RHIBufferUsage::Transfer, RHIMemoryUsage::GPU_Only);
	m_impl->meshlet_buffer      = rhi_context->CreateBuffer<Meshlet>(meshlets.size(), RHIBufferUsage::UnorderedAccess | RHIBufferUsage::Transfer, RHIMemoryUsage::GPU_Only);

	m_impl->vertex_buffer->CopyToDevice(vertices.data(), vertices.size() * sizeof(SkinnedVertex));
	m_impl->index_buffer->CopyToDevice(indices.data(), indices.size() * sizeof(uint32_t));
	m_impl->meshlet_data_buffer->CopyToDevice(meshletdata.data(), meshletdata.size() * sizeof(uint32_t));
	m_impl->meshlet_buffer->CopyToDevice(meshlets.data(), meshlets.size() * sizeof(Meshlet));

	glm::vec3 min_bound = glm::vec3(std::numeric_limits<float>::max());
	glm::vec3 max_bound = glm::vec3(-std::numeric_limits<float>::max());
	for (const auto &v : vertices)
	{
		min_bound = glm::min(min_bound, v.position);
		max_bound = glm::max(max_bound, v.position);
	}

	glm::vec3 center = (max_bound + min_bound) * 0.5f;
	float     radius = glm::length(max_bound - min_bound);

	std::vector<uint8_t> thumbnail_data = RenderPreview(rhi_context, center, radius);
	SERIALIZE(fmt::format("Asset/Meta/{}.{}.asset", m_name, (uint32_t) ResourceType::SkinnedMesh), thumbnail_data, vertices, indices, meshlets, meshletdata);
}

std::vector<uint8_t> Resource<ResourceType::SkinnedMesh>::RenderPreview(RHIContext *rhi_context, const glm::vec3 &center, float radius)
{
	/*{
	    std::vector<uint8_t> raw_shader;
	    Path::GetInstance().Read("./Source/Shaders/Preview/Mesh.hlsl", raw_shader);

	    std::string shader_source;
	    shader_source.resize(raw_shader.size());
	    std::memcpy(shader_source.data(), raw_shader.data(), raw_shader.size());
	    shader_source += "\n";

	    ShaderDesc vertex_shader_desc  = {};
		vertex_shader_desc.path="./Source/Shaders/Preview/Mesh.hlsl";
	    vertex_shader_desc.entry_point = "VSmain";
	    vertex_shader_desc.stage       = RHIShaderStage::Vertex;
	    vertex_shader_desc.source      = ShaderSource::HLSL;
	    vertex_shader_desc.target      = ShaderTarget::SPIRV;
	    vertex_shader_desc.code        = shader_source;

	    ShaderDesc fragment_shader_desc  = {};
	    fragment_shader_desc.path="./Source/Shaders/Preview/Mesh.hlsl";
	    fragment_shader_desc.entry_point = "PSmain";
	    fragment_shader_desc.stage       = RHIShaderStage::Fragment;
	    fragment_shader_desc.source      = ShaderSource::HLSL;
	    fragment_shader_desc.target      = ShaderTarget::SPIRV;
	    fragment_shader_desc.code        = shader_source;

	    ShaderMeta vertex_meta   = {};
	    ShaderMeta fragment_meta = {};

	    auto vertex_shader_spirv   = ShaderCompiler::GetInstance().Compile(vertex_shader_desc, vertex_meta);
	    auto fragment_shader_spirv = ShaderCompiler::GetInstance().Compile(fragment_shader_desc, fragment_meta);

	    auto m_vertex_shader   = rhi_context->CreateShader("VSmain", vertex_shader_spirv);
	    auto m_fragment_shader = rhi_context->CreateShader("PSmain", fragment_shader_spirv);

	    ShaderMeta shader_meta = vertex_meta;
	    shader_meta += fragment_meta;

	    SERIALIZE("Asset/BuildIn/mesh.preview.asset", vertex_shader_spirv, fragment_shader_spirv, shader_meta);
	}*/

	ShaderMeta           shader_meta;
	std::vector<uint8_t> vertex_shader_spirv;
	std::vector<uint8_t> fragment_shader_spirv;
	DESERIALIZE("Asset/BuildIn/mesh.preview.asset", vertex_shader_spirv, fragment_shader_spirv, shader_meta);

	BlendState blend_state = {};
	blend_state.attachment_states.resize(1);

	DepthStencilState depth_stencil_state  = {};
	depth_stencil_state.depth_test_enable  = true;
	depth_stencil_state.depth_write_enable = true;

	if (!m_thumbnail)
	{
		m_thumbnail = rhi_context->CreateTexture2D(128, 128, RHIFormat::R8G8B8A8_UNORM, RHITextureUsage::ShaderResource | RHITextureUsage::Transfer | RHITextureUsage::RenderTarget, false);
	}

	auto depth_buffer    = rhi_context->CreateTexture2D(128, 128, RHIFormat::D32_FLOAT, RHITextureUsage::RenderTarget, false);
	auto uniform_buffer  = rhi_context->CreateBuffer<glm::mat4>(1, RHIBufferUsage::ConstantBuffer, RHIMemoryUsage::CPU_TO_GPU);
	auto staging_buffer  = rhi_context->CreateBuffer(128ull * 128ull * 4ull * sizeof(uint8_t), RHIBufferUsage::Transfer, RHIMemoryUsage::GPU_TO_CPU);
	auto render_target   = rhi_context->CreateRenderTarget();
	auto pipeline_state  = rhi_context->CreatePipelineState();
	auto vertex_shader   = rhi_context->CreateShader("VSmain", vertex_shader_spirv);
	auto fragment_shader = rhi_context->CreateShader("PSmain", fragment_shader_spirv);
	pipeline_state->SetBlendState(blend_state);
	pipeline_state->SetDepthStencilState(depth_stencil_state);
	pipeline_state->SetShader(RHIShaderStage::Vertex, vertex_shader.get());
	pipeline_state->SetShader(RHIShaderStage::Fragment, fragment_shader.get());
	pipeline_state->SetVertexInputState(VertexInputState{
	    {
	        VertexInputState::InputAttribute{RHIVertexSemantics::Position, 0, 0, RHIFormat::R32G32B32_FLOAT, offsetof(Resource<ResourceType::SkinnedMesh>::SkinnedVertex, position)},
	        VertexInputState::InputAttribute{RHIVertexSemantics::Normal, 1, 0, RHIFormat::R32G32B32_FLOAT, offsetof(Resource<ResourceType::SkinnedMesh>::SkinnedVertex, normal)},
	    },
	    {
	        VertexInputState::InputBinding{0, sizeof(Resource<ResourceType::SkinnedMesh>::SkinnedVertex), RHIVertexInputRate::Vertex},
	    }});

	{
		glm::vec3 position  = center + radius * glm::vec3(0.f, 0.f, 1.f);
		glm::vec3 direction = glm::normalize(center - position);
		glm::vec3 right     = glm::normalize(glm::cross(direction, glm::vec3{0.f, 1.f, 0.f}));
		glm::vec3 up        = glm::normalize(glm::cross(right, direction));
		glm::mat4 transform = glm::perspective(glm::radians(45.f), 1.f, 0.01f, 1000.f) * glm::lookAt(position, center, up);
		uniform_buffer->CopyToDevice(glm::value_ptr(transform), sizeof(transform));
	}

	auto descriptor = rhi_context->CreateDescriptor(shader_meta);
	descriptor->BindBuffer("UniformBuffer", uniform_buffer.get());

	render_target->Set(0, m_thumbnail.get(), TextureRange{}, ColorAttachment{RHILoadAction::Clear, RHIStoreAction::Store, {0.1f, 0.1f, 0.1f, 1.f}});
	render_target->Set(depth_buffer.get(), TextureRange{}, DepthStencilAttachment{});

	auto *cmd_buffer = rhi_context->CreateCommand(RHIQueueFamily::Graphics);
	cmd_buffer->Begin();
	cmd_buffer->ResourceStateTransition({
	                                        TextureStateTransition{m_thumbnail.get(), RHIResourceState::Undefined, RHIResourceState::RenderTarget},
	                                        TextureStateTransition{depth_buffer.get(), RHIResourceState::Undefined, RHIResourceState::DepthWrite},
	                                    },
	                                    {});
	cmd_buffer->BeginRenderPass(render_target.get());
	cmd_buffer->SetViewport(128, 128);
	cmd_buffer->SetScissor(128, 128);
	cmd_buffer->BindDescriptor(descriptor);
	cmd_buffer->BindPipelineState(pipeline_state.get());
	cmd_buffer->BindVertexBuffer(0, m_impl->vertex_buffer.get());
	cmd_buffer->BindIndexBuffer(m_impl->index_buffer.get());
	cmd_buffer->DrawIndexed(static_cast<uint32_t>(m_impl->index_count));
	cmd_buffer->EndRenderPass();
	cmd_buffer->ResourceStateTransition({
	                                        TextureStateTransition{m_thumbnail.get(), RHIResourceState::RenderTarget, RHIResourceState::TransferSource},
	                                    },
	                                    {});
	cmd_buffer->CopyTextureToBuffer(m_thumbnail.get(), staging_buffer.get(), 0, 0, 1);
	cmd_buffer->End();
	rhi_context->Execute(cmd_buffer);

	std::vector<uint8_t> staging_data(staging_buffer->GetDesc().size);
	staging_buffer->CopyToHost(staging_data.data(), staging_buffer->GetDesc().size);

	return staging_data;
}
}        // namespace Ilum