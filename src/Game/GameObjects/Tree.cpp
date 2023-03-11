#include "Tree.h"

#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"

Tree::Tree(const std::shared_ptr<RenderEngine::Sprite> pSprite, glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
	: IGameObject(position, glm::vec2(32, 32), rotation, layer)
	, m_currentTreeState(ETreeState::Live)
	, m_pCurrentSprite(pSprite)
{

}

void Tree::render() const {
	m_pCurrentSprite->render(m_position, m_size, m_rotation, m_layer);
}

void Tree::update(const uint64_t delta) {

}
