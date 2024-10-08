#pragma once

#include "IGameObject.h"

#include <array>
#include <memory>

namespace RenderEngine {
	class Sprite;
}

class Tree : public IGameObject {
public:
	enum class ETreeState {
		Live,
		Destroyed
	};

	Tree(const std::shared_ptr<RenderEngine::Sprite> pSprite, glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);
	virtual void render() const override;
	virtual void update(const double delta) override;

private:
	ETreeState m_currentTreeState;
	const std::shared_ptr<RenderEngine::Sprite> m_pCurrentSprite;
};