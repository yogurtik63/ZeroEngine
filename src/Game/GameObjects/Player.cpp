#include "Player.h"

#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"

Player::Player(const float velocity,
			   const glm::vec2& position,
			   const glm::vec2& size,
				const float layer)
	: IGameObject(position, size, 0.f, layer)
	, m_eOrientation(EOrintation::Top)
	, m_pSprite_top(ResourceManager::getSprite("playerSprite_top"))
	, m_pSprite_bottom(ResourceManager::getSprite("playerSprite_bottom"))
	, m_pSprite_left(ResourceManager::getSprite("playerSprite_left"))
	, m_pSprite_right(ResourceManager::getSprite("playerSprite_right"))

	, m_spriteAnimator_top(m_pSprite_top)
	, m_spriteAnimator_bottom(m_pSprite_bottom)
	, m_spriteAnimator_left(m_pSprite_left)
	, m_spriteAnimator_right(m_pSprite_right)

	, m_move(false)
	, m_velocity(velocity)
	, m_moveOffset(glm::vec2(0.1f, 1.f))

	, m_position(position)
{
}

void Player::render() const {
	switch (m_eOrientation)
	{
	case Player::EOrintation::Top:
		m_pSprite_top->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_top.getCurrentFrame());
		break;
	case Player::EOrintation::Bottom:
		m_pSprite_bottom->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_bottom.getCurrentFrame());
		break;
	case Player::EOrintation::Left:
		m_pSprite_left->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_left.getCurrentFrame());
		break;
	case Player::EOrintation::Right:
		m_pSprite_right->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_right.getCurrentFrame());
		break;
	}
}

void Player::setOrientation(const EOrintation eOrintation) {
	if (m_eOrientation == eOrintation) {
		return;
	}

	m_eOrientation = eOrintation;
	switch (m_eOrientation)
	{
	case Player::EOrintation::Top:
		m_moveOffset.x = 0.f;
		m_moveOffset.y = 1.f;
		break;
	case Player::EOrintation::Bottom:
		m_moveOffset.x = 0.f;
		m_moveOffset.y = -1.f;
		break;
	case Player::EOrintation::Left:
		m_moveOffset.x = -1.f;
		m_moveOffset.y = 0.f;
		break;
	case Player::EOrintation::Right:
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

		switch (m_eOrientation)
		{
		case Player::EOrintation::Top:
			m_spriteAnimator_top.update(delta);
			break;
		case Player::EOrintation::Bottom:
			m_spriteAnimator_bottom.update(delta);
			break;
		case Player::EOrintation::Left:
			m_spriteAnimator_left.update(delta);
			break;
		case Player::EOrintation::Right:
			m_spriteAnimator_right.update(delta);
			break;
		}
	}
}