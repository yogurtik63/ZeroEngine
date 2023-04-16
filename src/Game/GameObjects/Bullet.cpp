#include "Bullet.h"

#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"

#include <iostream>

Bullet::Bullet(const double velocity, const glm::vec2& position, const glm::vec2& size)
    : IGameObject(IGameObject::EObjectType::Bullet, position, size, 0.f, 3.f)
    , m_eOrientation(EOrientation::Top)
    , m_maxVelocity(velocity)
    , m_isActive(false)
    , m_toolBullet(IGameObject::EToolBullet::None)
    , m_sprite(ResourceManager::getSprite("fruit"))
{
    auto onCollisionCallback = [&](const IGameObject& object, const Physics::ECollisionDirection)
    {
        setVelocity(0);
        std::cout << "Bullet shot" << std::endl;
        m_isActive = false;
    };

    setVelocity(velocity);
    m_colliders.emplace_back(glm::vec2(0), m_size, onCollisionCallback); // + ", onCollisionCallback"
    setName("bullet");

    m_useTimer.setCallBack([&]()
        {
            m_isActive = false;
            setVelocity(0);
        }
    );

    setVelocity(0);
}

void Bullet::render() const {
    m_sprite->render(m_position, m_size, m_rotation, m_layer); // FOR DEBUG
}

void Bullet::update(const double delta)
{
    m_useTimer.update(delta);
}

void Bullet::fire(const glm::vec2& position, const glm::vec2& direction)
{
    m_isActive = true;
    startTimer(1500);
    m_position = position;
    m_direction = direction;
    if (m_direction.x == 0.f)
    {
        m_eOrientation = (m_direction.y < 0) ? EOrientation::Bottom : EOrientation::Top;
    }
    else
    {
        m_eOrientation = (m_direction.x < 0) ? EOrientation::Left : EOrientation::Right;
    }
    setVelocity(m_maxVelocity);
}

bool Bullet::collides(const EObjectType objectType)
{
    return objectType != IGameObject::EObjectType::Border;
}