#pragma once

#include <string>
#include <vector>
#include <memory>

#include "glm/vec2.hpp"

#include "IGameState.h"

class IGameObject;
class Player;

class Level : public IGameState {
public:
	static constexpr unsigned int BLOCK_SIZE = 16;

	Level(const std::vector<std::string>& levelDescription);
	virtual void render() const override;
	virtual void update(const double delta) override;
	virtual unsigned int getStateWidth() const override;
	virtual unsigned int getStateHeight() const override;
	virtual void processInput(std::array<bool, 349>& keys) override;

	const glm::ivec2& getPlayerRespawn() const { return m_playerRespawn; }
	std::shared_ptr<IGameObject> createGameObjectFromDescription(const char description, glm::vec2& position, const glm::vec2& size, const float rotation);

	std::vector<std::shared_ptr<IGameObject>> getObjectsInArea(const glm::vec2& bottomLeft, const glm::vec2& topRight);
	void initPhysics();

private:
	size_t m_widthBlocks = 0;
	size_t m_heightBlocks = 0;

	unsigned int m_widthPixels = 0;
	unsigned int m_heightPixels = 0;

	glm::ivec2 m_playerRespawn;

	std::vector<std::shared_ptr<IGameObject>> m_levelObjects;
	std::vector<std::shared_ptr<IGameObject>> m_bgObjects;
	std::shared_ptr<Player> m_pPlayer;
};