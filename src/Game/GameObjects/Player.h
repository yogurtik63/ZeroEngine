#pragma once

#include <glm/vec2.hpp>
#include <memory>

#include "IGameObject.h"
#include "../../Renderer/SpriteAnimator.h"

#include "../../System/Timer.h"

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

	enum class EUsingTool {
		Axe,
		Pickaxe,
		Hoe,
		None
	};

	Player(const double maxVelocity, 
		const glm::vec2& position, 
		const glm::vec2& size,
		const float layer);

	void render() const override;

	void setOrientation(const EOrintation eOrintation);
	void setUsingTool(const EUsingTool eUsingTool);
	void setUsingToolB(bool use) { m_isUsing = use; }
	void startTimer(double delta) { m_useTimer.start(delta); }

	void setVelocity(const double velocity) override;

	void update(const double delta) override;
	double getMaxVelocity() const { return m_maxVelocity; }

private:
	EOrintation m_eOrientation;
	EUsingTool m_eUsingTool;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_top;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_bottom;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_left;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_right;

	RenderEngine::SpriteAnimator m_spriteAnimator_top;
	RenderEngine::SpriteAnimator m_spriteAnimator_bottom;
	RenderEngine::SpriteAnimator m_spriteAnimator_left;
	RenderEngine::SpriteAnimator m_spriteAnimator_right;

	std::shared_ptr<RenderEngine::Sprite> m_pSprite_use_top;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_use_bottom;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_use_left;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_use_right;

	RenderEngine::SpriteAnimator m_spriteAnimator_use_top;
	RenderEngine::SpriteAnimator m_spriteAnimator_use_bottom;
	RenderEngine::SpriteAnimator m_spriteAnimator_use_left;
	RenderEngine::SpriteAnimator m_spriteAnimator_use_right;

	std::shared_ptr<RenderEngine::Sprite> m_pSprite_pickaxe_top;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_pickaxe_bottom;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_pickaxe_left;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_pickaxe_right;

	RenderEngine::SpriteAnimator m_spriteAnimator_pickaxe_top;
	RenderEngine::SpriteAnimator m_spriteAnimator_pickaxe_bottom;
	RenderEngine::SpriteAnimator m_spriteAnimator_pickaxe_left;
	RenderEngine::SpriteAnimator m_spriteAnimator_pickaxe_right;

	std::shared_ptr<RenderEngine::Sprite> m_pSprite_axe_top;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_axe_bottom;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_axe_left;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_axe_right;

	RenderEngine::SpriteAnimator m_spriteAnimator_axe_top;
	RenderEngine::SpriteAnimator m_spriteAnimator_axe_bottom;
	RenderEngine::SpriteAnimator m_spriteAnimator_axe_left;
	RenderEngine::SpriteAnimator m_spriteAnimator_axe_right;

	Timer m_useTimer;

	double m_maxVelocity;
	bool m_isUsing;
	glm::vec2 m_sizeTool;
};