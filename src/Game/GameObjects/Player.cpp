#include "Player.h"

#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"

#include "Bullet.h"
#include "../../Physics/PhysicsEngine.h"

Player::Player(const double maxVelocity,
			   const glm::vec2& position,
			   const glm::vec2& size,
			   const float layer)
	: IGameObject(IGameObject::EObjectType::Player, position, size, 0.f, layer)
	, m_eOrientation(EOrintation::Top)
	, m_eUsingTool(EUsingTool::None)

	, m_pCurrentBullet(std::make_shared<Bullet>(0.01, m_position, m_size / 2.f))

	, m_pSprite_top(ResourceManager::getSprite("playerSprite_top"))
	, m_pSprite_bottom(ResourceManager::getSprite("playerSprite_bottom"))
	, m_pSprite_left(ResourceManager::getSprite("playerSprite_left"))
	, m_pSprite_right(ResourceManager::getSprite("playerSprite_right"))

	, m_spriteAnimator_top(m_pSprite_top)
	, m_spriteAnimator_bottom(m_pSprite_bottom)
	, m_spriteAnimator_left(m_pSprite_left)
	, m_spriteAnimator_right(m_pSprite_right)

	, m_pSprite_use_top(ResourceManager::getSprite("playerUseSprite_top"))
	, m_pSprite_use_bottom(ResourceManager::getSprite("playerUseSprite_bottom"))
	, m_pSprite_use_left(ResourceManager::getSprite("playerUseSprite_left"))
	, m_pSprite_use_right(ResourceManager::getSprite("playerUseSprite_right"))

	, m_spriteAnimator_use_top(m_pSprite_use_top)
	, m_spriteAnimator_use_bottom(m_pSprite_use_bottom)
	, m_spriteAnimator_use_left(m_pSprite_use_left)
	, m_spriteAnimator_use_right(m_pSprite_use_right)

	, m_pSprite_pickaxe_top(ResourceManager::getSprite("pickaxeUseSprite_top"))
	, m_pSprite_pickaxe_bottom(ResourceManager::getSprite("pickaxeUseSprite_bottom"))
	, m_pSprite_pickaxe_left(ResourceManager::getSprite("pickaxeUseSprite_left"))
	, m_pSprite_pickaxe_right(ResourceManager::getSprite("pickaxeUseSprite_right"))

	, m_spriteAnimator_pickaxe_top(m_pSprite_pickaxe_top)
	, m_spriteAnimator_pickaxe_bottom(m_pSprite_pickaxe_bottom)
	, m_spriteAnimator_pickaxe_left(m_pSprite_pickaxe_left)
	, m_spriteAnimator_pickaxe_right(m_pSprite_pickaxe_right)

	, m_pSprite_axe_top(ResourceManager::getSprite("axeUseSprite_top"))
	, m_pSprite_axe_bottom(ResourceManager::getSprite("axeUseSprite_bottom"))
	, m_pSprite_axe_left(ResourceManager::getSprite("axeUseSprite_left"))
	, m_pSprite_axe_right(ResourceManager::getSprite("axeUseSprite_right"))

	, m_spriteAnimator_axe_top(m_pSprite_axe_top)
	, m_spriteAnimator_axe_bottom(m_pSprite_axe_bottom)
	, m_spriteAnimator_axe_left(m_pSprite_axe_left)
	, m_spriteAnimator_axe_right(m_pSprite_axe_right)

	, m_isUsing(false)
	, m_maxVelocity(maxVelocity)

	, m_playerCollidedObject(false)
	, m_bulletCollidedObject(false)

	, m_sizeTool(glm::vec2(26.f, 22.f))
{
	m_useTimer.setCallBack([&]()
		{
			m_isUsing = false;
		}
	);

	m_colliders.emplace_back(glm::vec2(0), glm::vec2(16, 16));

	Physics::PhysicsEngine::addDynamicGameObject(m_pCurrentBullet);
	setName("player");
}

void Player::render() const {
	/*m_pCurrentBullet->render();*/

	if (m_isUsing) {
		switch (m_eOrientation)
		{
		case Player::EOrintation::Top:
			m_pSprite_use_top->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_use_top.getCurrentFrame());
			switch (m_eUsingTool)
			{
			case Player::EUsingTool::Axe:
				m_pSprite_axe_top->render(m_position, m_sizeTool, m_rotation, m_layer + 0.1f, m_spriteAnimator_axe_top.getCurrentFrame());
				break;
			case Player::EUsingTool::Pickaxe:
				m_pSprite_pickaxe_top->render(m_position, m_sizeTool, m_rotation, m_layer + 0.1f, m_spriteAnimator_pickaxe_top.getCurrentFrame());
				break;
			case Player::EUsingTool::None:
				break;
			default:
				break;
			}
			break;
		case Player::EOrintation::Bottom:
			m_pSprite_use_bottom->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_use_bottom.getCurrentFrame());
			switch (m_eUsingTool)
			{
			case Player::EUsingTool::Axe:
				m_pSprite_axe_bottom->render(m_position, m_sizeTool, m_rotation, m_layer + 0.1f, m_spriteAnimator_axe_bottom.getCurrentFrame());
				break;
			case Player::EUsingTool::Pickaxe:
				m_pSprite_pickaxe_bottom->render(m_position, m_sizeTool, m_rotation, m_layer + 0.1f, m_spriteAnimator_pickaxe_bottom.getCurrentFrame());
				break;
			case Player::EUsingTool::None:
				break;
			default:
				break;
			}
			break;
		case Player::EOrintation::Left:
			m_pSprite_use_left->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_use_left.getCurrentFrame());
			switch (m_eUsingTool)
			{
			case Player::EUsingTool::Axe:
				m_pSprite_axe_left->render(m_position, m_sizeTool, m_rotation, m_layer + 0.1f, m_spriteAnimator_axe_left.getCurrentFrame());
				break;
			case Player::EUsingTool::Pickaxe:
				m_pSprite_pickaxe_left->render(m_position, m_sizeTool, m_rotation, m_layer + 0.1f, m_spriteAnimator_pickaxe_left.getCurrentFrame());
				break;
			case Player::EUsingTool::None:
				break;
			default:
				break;
			}
			break;
		case Player::EOrintation::Right:
			m_pSprite_use_right->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_use_right.getCurrentFrame());
			switch (m_eUsingTool)
			{
			case Player::EUsingTool::Axe:
				m_pSprite_axe_right->render(m_position, m_sizeTool, m_rotation, m_layer + 0.1f, m_spriteAnimator_axe_right.getCurrentFrame());
				break;
			case Player::EUsingTool::Pickaxe:
				m_pSprite_pickaxe_right->render(m_position, m_sizeTool, m_rotation, m_layer + 0.1f, m_spriteAnimator_pickaxe_right.getCurrentFrame());
				break;
			case Player::EUsingTool::None:
				break;
			default:
				break;
			}
			break;
		}
	}
	else {
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
}

void Player::update(const double delta) {
	m_pCurrentBullet->update(delta);

	if (m_isUsing) {
		m_useTimer.update(delta);
		switch (m_eOrientation)
		{
		case Player::EOrintation::Top:
			m_spriteAnimator_use_top.update(delta);
			switch (m_eUsingTool)
			{
			case Player::EUsingTool::Axe:
				m_spriteAnimator_axe_top.update(delta);
				break;
			case Player::EUsingTool::Pickaxe:
				m_spriteAnimator_pickaxe_top.update(delta);
				break;
			case Player::EUsingTool::None:
				break;
			default:
				break;
			}
			break;
		case Player::EOrintation::Bottom:
			m_spriteAnimator_use_bottom.update(delta);
			switch (m_eUsingTool)
			{
			case Player::EUsingTool::Axe:
				m_spriteAnimator_axe_bottom.update(delta);
				break;
			case Player::EUsingTool::Pickaxe:
				m_spriteAnimator_pickaxe_bottom.update(delta);
				break;
			case Player::EUsingTool::None:
				break;
			default:
				break;
			}
			break;
		case Player::EOrintation::Left:
			m_spriteAnimator_use_left.update(delta);
			switch (m_eUsingTool)
			{
			case Player::EUsingTool::Axe:
				m_spriteAnimator_axe_left.update(delta);
				break;
			case Player::EUsingTool::Pickaxe:
				m_spriteAnimator_pickaxe_left.update(delta);
				break;
			case Player::EUsingTool::None:
				break;
			default:
				break;
			}
			break;
		case Player::EOrintation::Right:
			m_spriteAnimator_use_right.update(delta);
			switch (m_eUsingTool)
			{
			case Player::EUsingTool::Axe:
				m_spriteAnimator_axe_right.update(delta);
				break;
			case Player::EUsingTool::Pickaxe:
				m_spriteAnimator_pickaxe_right.update(delta);
				break;
			case Player::EUsingTool::None:
				break;
			default:
				break;
			}
			break;
		}
	}
	else {
		if (m_velocity > 0) {

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
}


void Player::setOrientation(const EOrintation eOrintation) {
	if (m_eOrientation == eOrintation) {
		return;
	}

	m_eOrientation = eOrintation;
	switch (m_eOrientation)
	{
	case Player::EOrintation::Top:
		m_direction.x = 0.f;
		m_direction.y = 1.f;
		break;
	case Player::EOrintation::Bottom:
		m_direction.x = 0.f;
		m_direction.y = -1.f;
		break;
	case Player::EOrintation::Left:
		m_direction.x = -1.f;
		m_direction.y = 0.f;
		break;
	case Player::EOrintation::Right:
		m_direction.x = 1.f;
		m_direction.y = 0.f;
		break;
	default:
		break;
	}
}

void Player::setUsingTool(const EUsingTool eUsingTool) {
	if (m_eUsingTool == eUsingTool) {
		return;
	}

	m_eUsingTool = eUsingTool;
}

void Player::setVelocity(const double velocity) {
	if (!m_isUsing) {
		m_velocity = velocity;
	}
}

void Player::onCollision() {

}

void Player::fire(const EUsingTool eUsingTool) {
	if (!m_pCurrentBullet->isActive() && m_isUsing)
	{
		switch (eUsingTool)
		{
		case EUsingTool::Axe:
			m_pCurrentBullet->setToolBullet(IGameObject::EToolBullet::Axe);
			break;
		case EUsingTool::Pickaxe:
			m_pCurrentBullet->setToolBullet(IGameObject::EToolBullet::Pickaxe);
			break;
		default:
			break;
		}
		m_pCurrentBullet->fire(m_position + m_size / 8.f - m_size * m_direction / 8.f, m_direction);
	}
}