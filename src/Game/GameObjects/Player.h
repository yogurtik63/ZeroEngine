#pragma once

#include <glm/vec2.hpp>
#include <memory>

#include "IGameObject.h"
#include "../../Renderer/SpriteAnimator.h"

namespace RenderEngine {
	class Sprite;
}

class Player : public IGameObject {
public:
	enum class EOrintation {
		Top,
		Bottom,
		Left,
		Right
	};

	Player(const float velocity, 
		const glm::vec2& position, 
		const glm::vec2& size);

	void render() const override;
	void setOrientation(const EOrintation eOrintation);
	void move(const bool move);
	void update(const uint64_t delta) override;

private:
	EOrintation m_eOrientation;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_top;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_bottom;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_left;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_right;

	RenderEngine::SpriteAnimator m_spriteAnimator_top;
	RenderEngine::SpriteAnimator m_spriteAnimator_bottom;
	RenderEngine::SpriteAnimator m_spriteAnimator_left;
	RenderEngine::SpriteAnimator m_spriteAnimator_right;

	bool m_move;
	float m_velocity;
	glm::vec2 m_moveOffset;
	
};