#pragma once

#include <string>
#include <vector>
#include <memory>

#include "glm/vec2.hpp"

class IGameObject;

class Level {
public:
	static constexpr unsigned int BLOCK_SIZE = 16;

	Level(const std::vector<std::string>& levelDescription);
	void render() const;
	void update(const double delta);
	size_t getLevelWidth() const;
	size_t getLevelHeight() const;

	const glm::ivec2& getPlayerRespawn() const { return m_playerRespawn; }
	std::shared_ptr<IGameObject> createGameObjectFromDescription(const char description, glm::vec2& position, const glm::vec2& size, const float rotation);

	std::vector<std::shared_ptr<IGameObject>> getObjectsInArea(const glm::vec2& bottomLeft, const glm::vec2& topRight);

private:
	size_t m_widthBlocks = 0;
	size_t m_heightBlocks = 0;

	unsigned int m_widthPixels = 0;
	unsigned int m_heightPixels = 0;

	glm::ivec2 m_playerRespawn;

	std::vector<std::shared_ptr<IGameObject>> m_levelObjects;
	std::vector<std::shared_ptr<IGameObject>> m_bgObjects;
};