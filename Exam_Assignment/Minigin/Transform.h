#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)


namespace dae
{
	class Transform final
	{
		glm::vec3 m_Position;
		float m_Angle;
	public:
		const glm::vec3& GetPosition() const { return m_Position; }
		float GetAngle() { return m_Angle; }
		void SetPosition(float x, float y);
		void SetAngle(const float rotation);
	};
}
