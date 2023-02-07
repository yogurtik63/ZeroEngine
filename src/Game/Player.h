#pragma once

#include <glm/vec2.hpp>
#include <memory>

namespace Renderer {
	class AnimatedSprite;
}

class Player {
public:
	enum class EOrintation {
		Top,
		Bottom,
		Left,
		Right
	};

	Player(std::shared_ptr<Renderer::AnimatedSprite> pSprite, const float velocity, const glm::vec2& position);

	void render() const;
	void setOrientation(const EOrintation eOrintation);
	void move(const bool move);
	void update(const uint64_t delta);

private:
	EOrintation m_eOrientation;
	std::shared_ptr<Renderer::AnimatedSprite> m_pSprite;
	bool m_move;
	float m_velocity;
	glm::vec2 m_position;
	glm::vec2 m_moveOffset;
};