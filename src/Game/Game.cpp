#include "Game.h"

#include "../Resources/ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"

#include "GameObjects/Player.h"
#include "Level.h"
#include "../Physics/PhysicsEngine.h"

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <memory>

Game::Game(const glm::ivec2& windowSize)
	: m_eCurrentGameState(EGameState::Active)
    , m_windowSize(windowSize)
{
	m_keys.fill(false);
}
Game::~Game() {

}

void Game::render() {
    if (m_pLevel) {
        m_pLevel->render();
    }

    if (m_pPlayer) {
        m_pPlayer->render();
    }
}

void Game::update(const double delta) {
    if (m_pLevel) {
        m_pLevel->update(delta);
    }

    if (m_pPlayer) {
        if (m_keys[GLFW_KEY_W]) {
            m_pPlayer->setOrientation(Player::EOrintation::Top);
            m_pPlayer->setVelocity(m_pPlayer->getMaxVelocity());
        }
        else if (m_keys[GLFW_KEY_A]) {
            m_pPlayer->setOrientation(Player::EOrintation::Left);
            m_pPlayer->setVelocity(m_pPlayer->getMaxVelocity());
        }
        else if (m_keys[GLFW_KEY_D]) {
            m_pPlayer->setOrientation(Player::EOrintation::Right);
            m_pPlayer->setVelocity(m_pPlayer->getMaxVelocity());
        }
        else if (m_keys[GLFW_KEY_S]) {
            m_pPlayer->setOrientation(Player::EOrintation::Bottom);
            m_pPlayer->setVelocity(m_pPlayer->getMaxVelocity());
        }
        else if (m_keys[GLFW_KEY_E]) {
            m_pPlayer->setUsingTool(Player::EUsingTool::Pickaxe);
            m_pPlayer->setUsingToolB(true);
            m_pPlayer->startTimer(750);
        }
        else if (m_keys[GLFW_KEY_R]) {
            m_pPlayer->setUsingTool(Player::EUsingTool::Axe);
            m_pPlayer->setUsingToolB(true);
            m_pPlayer->startTimer(750);
        }
        else {
            m_pPlayer->setVelocity(0);
        }

        m_pPlayer->update(delta);
    }
}

void Game::setKey(const int key, const int action) {
	m_keys[key] = action;
}

bool Game::init() {
    ResourceManager::loadJSONResources("res/resources.json");

    auto pSpriteShaderProgram = ResourceManager::getShaderProgram("spriteShader");
    if (!pSpriteShaderProgram) {
        std::cerr << "Can't find shader program" << "spriteShader" << std::endl;
        return false;
    }

    m_pLevel = std::make_shared<Level>(ResourceManager::getLevels()[3]);
    m_windowSize.x = static_cast<int>(m_pLevel->getLevelWidth());
    m_windowSize.y = static_cast<int>(m_pLevel->getLevelHeight());
    Physics::PhysicsEngine::setCurrentLevel(m_pLevel);

    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f);

    pSpriteShaderProgram->use();
    pSpriteShaderProgram->setInt("tex", 0);
    pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

    m_pPlayer = std::make_shared<Player>(0.05, m_pLevel->getPlayerRespawn(), glm::vec2(Level::BLOCK_SIZE, Level::BLOCK_SIZE + 6), 1.2f);
    Physics::PhysicsEngine::addDynamicGameObject(m_pPlayer);
    return true;
}

size_t Game::getCurrentLevelWidth() const {
    return m_pLevel->getLevelWidth();
}

size_t Game::getCurrentLevelHeight() const {
    return m_pLevel->getLevelHeight();
}