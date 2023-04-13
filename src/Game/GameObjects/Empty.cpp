#include "Empty.h"

#include "../../Renderer/Sprite.h"

Empty::Empty(const std::shared_ptr<RenderEngine::Sprite> pSprite, glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
	: IGameObject(position, size, rotation, layer)
{
	setName("empty");
}

void Empty::render() const {}

void Empty::update(const double delta) {}
