#include "Stone.h"

#include "../../Renderer/Sprite.h"
#include <iostream>

Stone::Stone(const std::shared_ptr<RenderEngine::Sprite> pSprite, glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
	: IGameObject(IGameObject::EObjectType::Stone, position, size, rotation, layer)
	, m_pCurrentSprite(pSprite)
	, m_eCurrentStoneState(Stone::EStoneState::Live)
{
	auto onCollisionCallback = [&](const IGameObject& object, const Physics::ECollisionDirection)
	{
		m_eCurrentStoneState = Stone::EStoneState::Destroyed;
	};

	m_colliders.emplace_back(glm::vec2(0), m_size, onCollisionCallback);

	setName("stone");
}

void Stone::onCollisionCallback(const IGameObject& object, const Physics::ECollisionDirection direction)
{
	std::cout << "onCollisionCallback" << std::endl;
	m_colliders[0].isActive = false;
};

void Stone::render() const {
	if (m_eCurrentStoneState != Stone::EStoneState::Destroyed) 
	{
		m_pCurrentSprite->render(m_position, m_size, m_rotation, m_layer);
	}
}

void Stone::update(const double delta) {

}

bool Stone::collides(const EObjectType objectType)
{
	if (m_eCurrentStoneState != Stone::EStoneState::Destroyed)
	{
		if (objectType != IGameObject::EObjectType::Stone && objectType != IGameObject::EObjectType::Log)
		{
			return true;
		}
		return false;
	} 
	return false;
}