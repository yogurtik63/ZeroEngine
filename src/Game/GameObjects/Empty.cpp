#include "Empty.h"

#include "../../Renderer/Sprite.h"

Empty::Empty(const std::shared_ptr<RenderEngine::Sprite> pSprite, glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
	: IGameObject(IGameObject::EObjectType::Empty, position, size, rotation, layer)
{
}

void Empty::render() const {}

void Empty::update(const double delta) {}
