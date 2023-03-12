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
	void update(const uint64_t delta);
	size_t getLevelWidth() const;
	size_t getLevelHeight() const;

	const glm::ivec2& getPlayerRespawn() const { return m_playerRespawn; }

	std::shared_ptr<IGameObject> createGameObjectFromDescription(const char description, glm::vec2& position, const glm::vec2& size, const float rotation);


private:
	size_t m_width = 0;
	size_t m_height = 0;

	glm::ivec2 m_playerRespawn;

	std::vector<std::shared_ptr<IGameObject>> m_mapObjects;
};