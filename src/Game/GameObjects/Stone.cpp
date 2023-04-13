#include "Stone.h"

#include "../../Renderer/Sprite.h"

Stone::Stone(const std::shared_ptr<RenderEngine::Sprite> pSprite, glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
	: IGameObject(position, size, rotation, layer)
	, m_pCurrentSprite(pSprite)
{
	m_colliders.emplace_back(glm::vec2(0), glm::vec2(m_size.x, m_size.y));
	setName("stone");
}

void Stone::render() const {
	m_pCurrentSprite->render(m_position, m_size, m_rotation, m_layer);
}

void Stone::update(const double delta) {

}
