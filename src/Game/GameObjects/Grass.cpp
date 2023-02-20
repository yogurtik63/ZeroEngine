#include "Grass.h"

#include "../../Renderer/Sprite.h"

Grass::Grass(const std::shared_ptr<RenderEngine::Sprite> pSprite, glm::vec2& position, const glm::vec2& size, const float rotation) 
	: IGameObject(position, size, rotation)
	, m_pCurrentSprite(pSprite)
{

}

void Grass::render() const {
	m_pCurrentSprite->render(m_position, m_size, m_rotation);
}

void Grass::update(const uint64_t delta) {

}
