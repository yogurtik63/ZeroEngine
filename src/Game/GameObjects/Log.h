#pragma once

#include "IGameObject.h"

#include <memory>

namespace RenderEngine {
	class Sprite;
}

class Log : public IGameObject {
public:
	enum class ELogState : uint8_t {
		Live,
		Destroyed
	};

	Log(const std::shared_ptr<RenderEngine::Sprite> pSprite, glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);
	virtual void render() const override;
	virtual void update(const double delta) override;
	virtual bool collides(const EObjectType objectType);

private:
	void onCollisionCallback(const IGameObject& object, const Physics::ECollisionDirection direction);

	const std::shared_ptr<RenderEngine::Sprite> m_pCurrentSprite;
	ELogState m_eCurrentLogState;
};