#pragma once

#include "IGameObject.h"

#include <array>
#include <memory>

#include "../../System/Timer.h"
#include "Player.h"

namespace RenderEngine {
    class Sprite;
}

class Bullet : public IGameObject {
public:
    enum class EOrientation : uint8_t {
        Top,
        Bottom,
        Left,
        Right
    };

    Bullet(const double velocity, const glm::vec2& position, const glm::vec2& size);
    virtual void render() const override;
    virtual void update(const double delta) override;
    bool isActive() const { return m_isActive; }
    void fire(const glm::vec2& position, const glm::vec2& direction);
    virtual bool collides(const EObjectType objectType);

    void setToolBullet(const IGameObject::EToolBullet eUsingTool) { m_toolBullet = eUsingTool; }
    IGameObject::EToolBullet getToolBullet() { return m_toolBullet; }

    void startTimer(double delta) { m_useTimer.start(delta); }

private:
    EOrientation m_eOrientation;
    double m_maxVelocity;
    bool m_isActive;
    std::shared_ptr<RenderEngine::Sprite> m_sprite; // FOR DEBUG
    IGameObject::EToolBullet m_toolBullet;

    Timer m_useTimer;
};