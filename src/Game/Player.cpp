#include "Player.h"
#include "../Renderer/AnimatedSprite.h"

Player::Player(std::shared_ptr<Renderer::AnimatedSprite> pSprite, const float velocity, const glm::vec2& position)
	: m_eOrientation(EOrintation::Top)
	, m_pSprite(std::move(pSprite))
	, m_move(false)
	, m_velocity(velocity)
	, m_position(position)
	, m_moveOffset(glm::vec2(0.1f, 1.f))
{
	m_pSprite->setPosition(position);
}

void Player::render() const {
	m_pSprite->render();
}

void Player::setOrientation(const EOrintation eOrintation) {
	if (m_eOrientation == eOrintation) {
		return;
	}

	m_eOrientation = eOrintation;
	switch (m_eOrientation)
	{
	case Player::EOrintation::Top:
		m_pSprite->setState("playerRightState");
		m_moveOffset.x = 0.f;
		m_moveOffset.y = 1.f;
		break;
	case Player::EOrintation::Bottom:
		m_pSprite->setState("playerRightState");
		m_moveOffset.x = 0.f;
		m_moveOffset.y = -1.f;
		break;
	case Player::EOrintation::Left:
		m_pSprite->setState("playerLeftState");
		m_moveOffset.x = -1.f;
		m_moveOffset.y = 0.f;
		break;
	case Player::EOrintation::Right:
		m_pSprite->setState("playerRightState");
		m_moveOffset.x = 1.f;
		m_moveOffset.y = 0.f;
		break;
	default:
		break;
	}
}

void Player::move(const bool move) {
	m_move = move;
}

void Player::update(const uint64_t delta) {
	if (m_move) {
		m_position += delta * m_velocity * m_moveOffset;
		m_pSprite->setPosition(m_position);
		m_pSprite->update(delta);
	}
}