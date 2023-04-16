#include "Log.h"

#include "../../Renderer/Sprite.h"

Log::Log(const std::shared_ptr<RenderEngine::Sprite> pSprite, glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
	: IGameObject(IGameObject::EObjectType::Log, position, size, rotation, layer)
	, m_pCurrentSprite(pSprite)
	, m_eCurrentLogState(Log::ELogState::Live)
{
	auto onCollisionCallback = [&](const IGameObject& object, const Physics::ECollisionDirection)
	{
		m_eCurrentLogState = Log::ELogState::Destroyed;
	};

	m_colliders.emplace_back(glm::vec2(0), m_size, onCollisionCallback);

	setName("log");
}

void Log::onCollisionCallback(const IGameObject& object, const Physics::ECollisionDirection direction)
{
	m_colliders[0].isActive = false;
};

void Log::render() const {
	if (m_eCurrentLogState != Log::ELogState::Destroyed)
	{
		m_pCurrentSprite->render(m_position, m_size, m_rotation, m_layer);
	}
}

void Log::update(const double delta) {

}

bool Log::collides(const EObjectType objectType)
{
	if (m_eCurrentLogState != Log::ELogState::Destroyed)
	{
		if (objectType != IGameObject::EObjectType::Stone && objectType != IGameObject::EObjectType::Log)
		{
			return true;
		}
		return false;
	}
	return false;
}