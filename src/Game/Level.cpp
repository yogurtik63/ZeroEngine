#include "Level.h"

#include "../Resources/ResourceManager.h"
#include "GameObjects/Grass.h"
#include "GameObjects/Tree.h"

#include <iostream>

const unsigned int BLOCK_SIZE = 16;

std::shared_ptr<IGameObject> Level::createGameObjectFromDescription(const char description, glm::vec2& position, const glm::vec2& size, const float rotation) {
	switch (description)
	{
	case '0':
		return std::make_shared<Grass>(ResourceManager::getSprite("leftTopGrass"), position, size, rotation, 0.f);
	case '1':
		return std::make_shared<Grass>(ResourceManager::getSprite("middleTopGrass"), position, size, rotation, 0.f);
	case '2':
		return std::make_shared<Grass>(ResourceManager::getSprite("rightTopGrass"), position, size, rotation, 0.f);
	case '3':
		return std::make_shared<Grass>(ResourceManager::getSprite("leftGrass"), position, size, rotation, 0.f);
	case '4':
		return std::make_shared<Grass>(ResourceManager::getSprite("middleGrass"), position, size, rotation, 0.f);
	case '5':
		return std::make_shared<Grass>(ResourceManager::getSprite("rightGrass"), position, size, rotation, 0.f);
	case '6':
		return std::make_shared<Grass>(ResourceManager::getSprite("leftDownGrass"), position, size, rotation, 0.f);
	case '7':
		return std::make_shared<Grass>(ResourceManager::getSprite("middleDownGrass"), position, size, rotation, 0.f);
	case '8':
		return std::make_shared<Grass>(ResourceManager::getSprite("rightDownGrass"), position, size, rotation, 0.f);

	case '9':
		return std::make_shared<Grass>(ResourceManager::getSprite("rightDownDirt"), position, size, rotation, 0.f);
	case 'a':
		return std::make_shared<Grass>(ResourceManager::getSprite("leftDownDirt"), position, size, rotation, 0.f);
	case 'b':
		return std::make_shared<Grass>(ResourceManager::getSprite("rightUpGrass"), position, size, rotation, 0.f);
	case 'c':
		return std::make_shared<Grass>(ResourceManager::getSprite("leftUpDirt"), position, size, rotation, 0.f);

	case 'T':
		m_mapObjects.emplace_back(createGameObjectFromDescription('4', position, size, rotation));
		return std::make_shared<Tree>(ResourceManager::getSprite("tree1"), position, size, rotation, 2.f);

	case 'E':
		return std::make_shared<Grass>(ResourceManager::getSprite("middleGrass"), position, size, rotation, 0.f);
		// return nullptr;
	case 'H':
		return std::make_shared<Grass>(ResourceManager::getSprite("middleGrass"), position, size, rotation, 0.f);
		// return nullptr;

	default:
		std::cerr << "Unknown GameObject description: " << description << std::endl;
	}
	return nullptr;
}

Level::Level(const std::vector<std::string>& levelDescription) {
	if (levelDescription.empty()) {
		std::cerr << "Empty level description" << std::endl;
	}

	m_width = levelDescription[0].length();
	m_height = levelDescription.size();

	m_mapObjects.reserve(m_width * m_height);
	unsigned int currentBottomOffset = static_cast<unsigned int>(BLOCK_SIZE * (m_height - 1));

	for (const std::string& currentRow : levelDescription) {
		unsigned int currentLeftOffset = 0;

		for (const char currentElement : currentRow) {
			m_mapObjects.emplace_back(createGameObjectFromDescription(
				currentElement, 
				glm::vec2(currentLeftOffset, currentBottomOffset), 
				glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 0.f));

			currentLeftOffset += BLOCK_SIZE;
		}

		currentBottomOffset -= BLOCK_SIZE;
	}
}

void Level::render() const {
	for (const auto& currentMapObject : m_mapObjects) {
		if (currentMapObject) {
			currentMapObject->render();
		}
	}
}

void Level::update(const uint64_t delta) {
	for (const auto& currentMapObject : m_mapObjects) {
		if (currentMapObject) {
			currentMapObject->update(delta);
		}
	}
}