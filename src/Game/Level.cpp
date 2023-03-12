#include "Level.h"

#include "../Resources/ResourceManager.h"
#include "GameObjects/Grass.h"
#include "GameObjects/Tree.h"
#include "GameObjects/Border.h"

#include <iostream>


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

	m_playerRespawn = { (m_width / 2 - 0.5f) * BLOCK_SIZE, BLOCK_SIZE * 2 };

	m_mapObjects.reserve(m_width * m_height + 4);
	unsigned int currentBottomOffset = static_cast<unsigned int>(BLOCK_SIZE * (m_height - 1) + BLOCK_SIZE);

	for (const std::string& currentRow : levelDescription) {
		unsigned int currentLeftOffset = BLOCK_SIZE / 2.f;

		for (const char currentElement : currentRow) {
			switch (currentElement)
			{
			case 'R':
				m_mapObjects.emplace_back(createGameObjectFromDescription('4', 
					glm::vec2(currentLeftOffset, currentBottomOffset),
					glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 0.f));
				m_playerRespawn = { currentLeftOffset, currentBottomOffset };
				break;
			default:
				m_mapObjects.emplace_back(createGameObjectFromDescription(
					currentElement,
					glm::vec2(currentLeftOffset, currentBottomOffset),
					glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 0.f));
			}

			currentLeftOffset += BLOCK_SIZE;
		}

		currentBottomOffset -= BLOCK_SIZE;
	}

	// bottom border
	m_mapObjects.emplace_back(std::make_shared<Border>(
		glm::vec2(BLOCK_SIZE / 2.f, 0.f),
		glm::vec2(m_width * BLOCK_SIZE, BLOCK_SIZE * 2.f), 
		0.f, 0.f));

	// top border
	m_mapObjects.emplace_back(std::make_shared<Border>(
		glm::vec2(0.f, m_height * BLOCK_SIZE + BLOCK_SIZE),
		glm::vec2((m_width + 1) * BLOCK_SIZE, BLOCK_SIZE / 2.f),
		0.f, 0.f));

	// left border
	m_mapObjects.emplace_back(std::make_shared<Border>(
		glm::vec2(0.f, 0.f),
		glm::vec2(BLOCK_SIZE / 2.f, (m_height + 1) * BLOCK_SIZE), 
		0.f, 0.f));

	// right border
	m_mapObjects.emplace_back(std::make_shared<Border>(
		glm::vec2(m_width * BLOCK_SIZE + BLOCK_SIZE / 2.f, 0.f),
		glm::vec2(BLOCK_SIZE / 2.f, (m_height + 1) * BLOCK_SIZE), 
		0.f, 0.f));
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

size_t Level::getLevelWidth() const {
	return (m_width + 1) * BLOCK_SIZE;
}

size_t Level::getLevelHeight() const {
	return (m_height + 1.5f) * BLOCK_SIZE;
}