#pragma once

#include "IGameObject.h"

#include <memory>

namespace RenderEngine {
	class Sprite;
}

class Grass : public IGameObject {
public:
	Grass(const std::shared_ptr<RenderEngine::Sprite> pSprite, glm::vec2& position, const glm::vec2& size, const float rotation);
	virtual void render() const override;
	virtual void update(const uint64_t delta) override;

private:
	const std::shared_ptr<RenderEngine::Sprite> m_pCurrentSprite;
};