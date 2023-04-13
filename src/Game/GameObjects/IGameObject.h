#pragma once

#include "glm/vec2.hpp"
#include <string>

#include "../../Physics/PhysicsEngine.h"

class IGameObject {
public:
	IGameObject(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);
	virtual void render() const = 0;
	virtual void update(const double delta) = 0;
	virtual ~IGameObject();
	virtual glm::vec2& getCurrentPosition() { return m_position; }
	virtual glm::vec2& getCurrentDirection() { return m_direction; }
	virtual void setVelocity(const double velocity) { m_velocity = velocity; }
	virtual double getCurrentVelocity() { return m_velocity; }
	virtual std::string getName() { return m_name; }
	virtual void setName(std::string name) { m_name = name; }

	const glm::vec2& getSize() const { return m_size; }
	const std::vector<Physics::AABB>& getColliders() const { return m_colliders; }

protected:
	glm::vec2 m_position;
	glm::vec2 m_size;
	float m_rotation;
	float m_layer;
	std::string m_name;

	glm::vec2 m_direction;
	double m_velocity;
	std::vector<Physics::AABB> m_colliders;
};