#include "Camera/PerspectiveCamera.hpp"
#include "Transform.hpp"

#include <SceneGraph/Node.hpp>

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>

namespace Ilum
{
namespace Cmpt
{
PerspectiveCamera::PerspectiveCamera(Node *node) :
    Camera("Perspective Camera", node)
{
	Update();
}

void PerspectiveCamera::OnImGui()
{
	m_dirty |= ImGui::DragFloat("Aspect", &m_aspect, 0.01f, 0.f, std::numeric_limits<float>::max(), "%.3f");
	m_dirty |= ImGui::DragFloat("Fov", &m_fov, 0.01f, 0.f, 90.f, "%.3f");
	m_dirty |= ImGui::DragFloat("Near Plane", &m_near, 0.01f, 0.f, std::numeric_limits<float>::max(), "%.3f");
	m_dirty |= ImGui::DragFloat("Far Plane", &m_far, 0.01f, 0.f, std::numeric_limits<float>::max(), "%.3f");
}

std::type_index PerspectiveCamera::GetType() const
{
	return typeid(PerspectiveCamera);
}

void PerspectiveCamera::SetFov(float fov)
{
	m_dirty |= (m_fov != fov);
	m_fov = fov;
}

float PerspectiveCamera::GetFov() const
{
	return m_fov;
}

void PerspectiveCamera::Update()
{
	if (m_dirty)
	{
		auto *transform = p_node->GetComponent<Cmpt::Transform>();

		m_view                = glm::inverse(transform->GetWorldTransform());
		m_projection          = glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
		m_view_projection     = m_projection * m_view;
		m_inv_view            = transform->GetWorldTransform();
		m_inv_projection      = glm::inverse(m_projection);
		m_inv_view_projection = glm::inverse(m_view_projection);

		m_dirty = false;
	}
}
}        // namespace Cmpt
}        // namespace Ilum