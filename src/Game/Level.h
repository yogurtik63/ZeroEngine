#pragma once

#include <string>
#include <vector>
#include <memory>

#include "glm/vec2.hpp"

class IGameObject;

class Level {
public:
	Level(const std::vector<std::string>& levelDescription);
	void render() const;
	void update(const uint64_t delta);
	std::shared_ptr<IGameObject> createGameObjectFromDescription(const char description, glm::vec2& position, const glm::vec2& size, const float rotation);

private:
	size_t m_width;
	size_t m_height;

	std::vector<std::shared_ptr<IGameObject>> m_mapObjects;
};