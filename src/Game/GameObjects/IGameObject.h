#pragma once

#include "glm/vec2.hpp"
#include <string>

#include "../../Physics/PhysicsEngine.h"

class IGameObject {
public:
	enum class EObjectType {
		Log,
		Grass,
		Stone,
		Border,
		Player,
		Bullet,
		Empty
	};

	enum class EToolBullet {
		Pickaxe,
		Axe,
		None,

		NoBullet
	};

	IGameObject(const EObjectType objectType, const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);
	virtual void render() const = 0;
	virtual void update(const double delta) = 0;
	virtual ~IGameObject();
	virtual glm::vec2& getCurrentPosition() { return m_position; }
	virtual glm::vec2& getCurrentDirection() { return m_direction; }
	virtual void setVelocity(const double velocity) { m_velocity = velocity; }
	virtual double getCurrentVelocity() { return m_velocity; }

	EObjectType getObjectType() const { return m_objectType; }
	virtual void onCollision() {}

	virtual EToolBullet getToolBullet() { return m_eToolBullet; }
	virtual void setToolBullet(EToolBullet eToolBullet) { m_eToolBullet = eToolBullet; }

	const glm::vec2& getSize() const { return m_size; }
	const std::vector<Physics::Collider>& getColliders() const { return m_colliders; }
	virtual bool collides(const EObjectType objectType) { return true; }

	virtual std::string getName() { return m_name; }
	virtual void setName(std::string name) { m_name = name; }

protected:
	glm::vec2 m_position;
	glm::vec2 m_size;
	float m_rotation;
	float m_layer;
	std::string m_name;
	EObjectType m_objectType;
	EToolBullet m_eToolBullet;

	glm::vec2 m_direction;
	double m_velocity;
	std::vector<Physics::Collider> m_colliders;


};