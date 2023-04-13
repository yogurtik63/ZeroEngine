#include "Grass.h"

#include "../../Renderer/Sprite.h"

Grass::Grass(const std::shared_ptr<RenderEngine::Sprite> pSprite, glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
	: IGameObject(position, size, rotation, layer)
	, m_pCurrentSprite(pSprite)
{
	setName("grass");
}

void Grass::render() const {
	m_pCurrentSprite->render(m_position, m_size, m_rotation, m_layer);
}

void Grass::update(const double delta) {

}
