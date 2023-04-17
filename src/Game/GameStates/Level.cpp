#include "Level.h"

#include "../../Resources/ResourceManager.h"
#include "../GameObjects/Grass.h"
#include "../GameObjects/Log.h"
#include "../GameObjects/Border.h"
#include "../GameObjects/Stone.h"
#include "../GameObjects/Empty.h"
#include "../GameObjects/Player.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <algorithm>
#include <cmath>

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

	case 'e':
		return std::make_shared<Empty>(ResourceManager::getSprite("empty_tile"), position, size, rotation, 0.f);

	case 'h':
		return std::make_shared<Stone>(ResourceManager::getSprite("stone"), position, size, rotation, 1.f);

	case 'T':
		return std::make_shared<Log>(ResourceManager::getSprite("log"), position, size, rotation, 1.f);

	case 'E':
		return std::make_shared<Grass>(ResourceManager::getSprite("middleGrass"), position, size, rotation, 0.f);
		// return nullptr;
	//case 'H':
	//	return std::make_shared<Home>(ResourceManager::getSprite("home"), position, glm::vec2(size.x * 4, size.y * 5), rotation, 1.f);
	//	// return nullptr;

	default:
		std::cerr << "Unknown GameObject description: " << description << std::endl;
	}
	return nullptr;
}

Level::Level(const std::vector<std::string>& levelDescription) {
	if (levelDescription.empty()) {
		std::cerr << "Empty level description" << std::endl;
	}

	m_widthBlocks = levelDescription[0].length();
	m_heightBlocks = levelDescription.size();

	m_widthPixels = static_cast<unsigned int>(m_widthBlocks * BLOCK_SIZE);
	m_heightPixels = static_cast<unsigned int>(m_heightBlocks * BLOCK_SIZE);

	m_playerRespawn = { (m_widthBlocks / 2 - 0.5f) * BLOCK_SIZE, BLOCK_SIZE * 2 };

	m_levelObjects.reserve(m_widthBlocks * m_heightBlocks + 4);
	m_bgObjects.reserve(m_widthBlocks * m_heightBlocks);
	unsigned int currentBottomOffset = static_cast<unsigned int>(BLOCK_SIZE * (m_heightBlocks - 1) + BLOCK_SIZE / 2.f);

	for (const std::string& currentRow : levelDescription) {
		unsigned int currentLeftOffset = BLOCK_SIZE / 2.f;

		for (const char currentElement : currentRow) {
			switch (currentElement)
			{
			case 'R':
				m_bgObjects.emplace_back(createGameObjectFromDescription('4',
					glm::vec2(currentLeftOffset, currentBottomOffset),
					glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 0.f));
				m_playerRespawn = { currentLeftOffset, currentBottomOffset };
				break;
			default:
				if (currentElement == '0' || currentElement == '1' || currentElement == '2' || currentElement == '3' ||
					currentElement == '4' || currentElement == '5' || currentElement == '6' || currentElement == '7' ||
					currentElement == '8' || currentElement == '9' || currentElement == 'a' || currentElement == 'b' ||
					currentElement == 'c') {
					m_bgObjects.emplace_back(createGameObjectFromDescription(
						currentElement,
						glm::vec2(currentLeftOffset, currentBottomOffset),
						glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 0.f));
					m_levelObjects.emplace_back(createGameObjectFromDescription('e',
						glm::vec2(currentLeftOffset, currentBottomOffset),
						glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 0.f));

				}
				else {
					m_bgObjects.emplace_back(createGameObjectFromDescription('4',
						glm::vec2(currentLeftOffset, currentBottomOffset),
						glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 0.f));
					m_levelObjects.emplace_back(createGameObjectFromDescription(
						currentElement,
						glm::vec2(currentLeftOffset, currentBottomOffset),
						glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 0.f));
				}

			}

			currentLeftOffset += BLOCK_SIZE;
		}

		currentBottomOffset -= BLOCK_SIZE;
	}

	// bottom border
	m_levelObjects.emplace_back(std::make_shared<Border>(
		glm::vec2(BLOCK_SIZE / 2.f, 0.f),
		glm::vec2(m_widthBlocks * BLOCK_SIZE, BLOCK_SIZE / 2),
		0.f, 0.f));

	// top border
	m_levelObjects.emplace_back(std::make_shared<Border>(
		glm::vec2(BLOCK_SIZE / 2.f, m_heightBlocks * BLOCK_SIZE + BLOCK_SIZE / 2.f),
		glm::vec2(m_widthBlocks * BLOCK_SIZE, BLOCK_SIZE / 2.f),
		0.f, 0.f));

	// left border
	m_levelObjects.emplace_back(std::make_shared<Border>(
		glm::vec2(0.f, 0.f),
		glm::vec2(BLOCK_SIZE / 2.f, (m_heightBlocks + 1) * BLOCK_SIZE),
		0.f, 0.f));

	// right border
	m_levelObjects.emplace_back(std::make_shared<Border>(
		glm::vec2(m_widthBlocks * BLOCK_SIZE + BLOCK_SIZE / 2.f, 0.f),
		glm::vec2(BLOCK_SIZE / 2.f, (m_heightBlocks + 1) * BLOCK_SIZE),
		0.f, 0.f));

}

void Level::initPhysics()
{
	m_pPlayer = std::make_shared<Player>(0.05, getPlayerRespawn(), glm::vec2(Level::BLOCK_SIZE, Level::BLOCK_SIZE + 6), 1.2f);
	Physics::PhysicsEngine::addDynamicGameObject(m_pPlayer);
}

void Level::render() const {
	for (const auto& currentMapObject : m_bgObjects) {
		if (currentMapObject) {
			currentMapObject->render();
		}
	}

	for (const auto& currentMapObject : m_levelObjects) {
		if (currentMapObject) {
			currentMapObject->render();
		}
	}

	m_pPlayer->render();
}

void Level::update(const double delta) {
	for (const auto& currentMapObject : m_bgObjects) {
		if (currentMapObject) {
			currentMapObject->update(delta);
		}
	}

	for (const auto& currentMapObject : m_levelObjects) {
		if (currentMapObject) {
			currentMapObject->update(delta);
		}
	}

	m_pPlayer->update(delta);
}

void Level::processInput(std::array<bool, 349>& keys)
{
	if (keys[GLFW_KEY_W]) {
		m_pPlayer->setOrientation(Player::EOrintation::Top);
		m_pPlayer->setVelocity(m_pPlayer->getMaxVelocity());
	}
	else if (keys[GLFW_KEY_A]) {
		m_pPlayer->setOrientation(Player::EOrintation::Left);
		m_pPlayer->setVelocity(m_pPlayer->getMaxVelocity());
	}
	else if (keys[GLFW_KEY_D]) {
		m_pPlayer->setOrientation(Player::EOrintation::Right);
		m_pPlayer->setVelocity(m_pPlayer->getMaxVelocity());
	}
	else if (keys[GLFW_KEY_S]) {
		m_pPlayer->setOrientation(Player::EOrintation::Bottom);
		m_pPlayer->setVelocity(m_pPlayer->getMaxVelocity());
	}
	else if (keys[GLFW_KEY_E]) {
		m_pPlayer->setUsingTool(Player::EUsingTool::Pickaxe);
		m_pPlayer->setUsingToolB(true);
		m_pPlayer->startTimer(750);
		m_pPlayer->fire(Player::EUsingTool::Pickaxe);
	}
	else if (keys[GLFW_KEY_R]) {
		m_pPlayer->setUsingTool(Player::EUsingTool::Axe);
		m_pPlayer->setUsingToolB(true);
		m_pPlayer->startTimer(750);
		m_pPlayer->fire(Player::EUsingTool::Axe);
	}
	else {
		m_pPlayer->setVelocity(0);
	}
}

unsigned int Level::getStateWidth() const {
	return static_cast<unsigned int>((m_widthBlocks + 1) * BLOCK_SIZE);
}

unsigned int Level::getStateHeight() const {
	return static_cast<unsigned int>((m_heightBlocks + 1) * BLOCK_SIZE);
}

std::vector<std::shared_ptr<IGameObject>> Level::getObjectsInArea(const glm::vec2& bottomLeft, const glm::vec2& topRight) {

	std::vector<std::shared_ptr<IGameObject>> output;
	output.reserve(9);

	glm::vec2 bottomLeft_converted(std::clamp(bottomLeft.x - BLOCK_SIZE / 2, 0.f, static_cast<float>(m_widthPixels)),
		std::clamp(m_heightPixels - bottomLeft.y + BLOCK_SIZE / 2, 0.f, static_cast<float>(m_heightPixels)));
	glm::vec2 topRight_converted(std::clamp(topRight.x - BLOCK_SIZE / 2, 0.f, static_cast<float>(m_widthPixels)),
		std::clamp(m_heightPixels - topRight.y + BLOCK_SIZE / 2, 0.f, static_cast<float>(m_heightPixels)));

	size_t startX = static_cast<size_t>(floor(bottomLeft_converted.x / BLOCK_SIZE));
	size_t endX = static_cast<size_t>(ceil(topRight_converted.x / BLOCK_SIZE));

	size_t startY = static_cast<size_t>(floor(topRight_converted.y / BLOCK_SIZE));
	size_t endY = static_cast<size_t>(ceil(bottomLeft_converted.y / BLOCK_SIZE));

	for (size_t currentColumn = startX; currentColumn < endX; ++currentColumn)
	{
		for (size_t currentRow = startY; currentRow < endY; ++currentRow)
		{
			auto& currentObject = m_levelObjects[currentRow * m_widthBlocks + currentColumn];
			if (currentObject && currentObject->getObjectType() != IGameObject::EObjectType::Grass && currentObject->getObjectType() != IGameObject::EObjectType::Empty)
			{
				output.push_back(currentObject);
			}
		}
	}

	if (endX >= m_widthBlocks)
	{
		output.push_back(m_levelObjects[m_levelObjects.size() - 1]);
	}
	if (startX <= 1)
	{
		output.push_back(m_levelObjects[m_levelObjects.size() - 2]);
	}
	if (startY <= 1)
	{
		output.push_back(m_levelObjects[m_levelObjects.size() - 3]);
	}
	if (endY >= m_heightBlocks)
	{
		output.push_back(m_levelObjects[m_levelObjects.size() - 4]);
	}

	return output;
}
