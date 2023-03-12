#include "Game.h"

#include "../Resources/ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"

#include "GameObjects/Player.h"
#include "Level.h"

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

void Game::update(const uint64_t delta) {
    if (m_pLevel) {
        m_pLevel->update(delta);
    }

    if (m_pPlayer) {
        if (m_keys[GLFW_KEY_W]) {
            m_pPlayer->setOrientation(Player::EOrintation::Top);
            m_pPlayer->move(true);
        }
        else if (m_keys[GLFW_KEY_A]) {
            m_pPlayer->setOrientation(Player::EOrintation::Left);
            m_pPlayer->move(true);
        }
        else if (m_keys[GLFW_KEY_D]) {
            m_pPlayer->setOrientation(Player::EOrintation::Right);
            m_pPlayer->move(true);
        }
        else if (m_keys[GLFW_KEY_S]) {
            m_pPlayer->setOrientation(Player::EOrintation::Bottom);
            m_pPlayer->move(true);
        }
        else {
            m_pPlayer->move(false);
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

    m_pLevel = std::make_unique<Level>(ResourceManager::getLevels()[0]);
    m_windowSize.x = static_cast<int>(m_pLevel->getLevelWidth());
    m_windowSize.y = static_cast<int>(m_pLevel->getLevelHeight());

    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f);

    pSpriteShaderProgram->use();
    pSpriteShaderProgram->setInt("tex", 0);
    pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

    m_pPlayer = std::make_unique<Player>(0.00000005f, m_pLevel->getPlayerRespawn(), glm::vec2(Level::BLOCK_SIZE, Level::BLOCK_SIZE + 6), 1.f);
    return true;
}

size_t Game::getCurrentLevelWidth() const {
    return m_pLevel->getLevelWidth();
}

size_t Game::getCurrentLevelHeight() const {
    return m_pLevel->getLevelHeight();
}