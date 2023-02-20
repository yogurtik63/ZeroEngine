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

    auto pTextureAtlas = ResourceManager::getTexture("mapTextureAtlas");
    if (!pTextureAtlas) {
        std::cerr << "Can't find texture atlas" << "mapTextureAtlas" << std::endl;
        return false;
    }

    auto pPlayerTextureAtlas = ResourceManager::getTexture("playerTextureAtlas");
    if (!pPlayerTextureAtlas) {
        std::cerr << "Can't find texture atlas" << "playerTextureAtlas" << std::endl;
        return false;
    }

    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f);

    pSpriteShaderProgram->use();
    pSpriteShaderProgram->setInt("tex", 0);
    pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

    m_pPlayer = std::make_unique<Player>(
        ResourceManager::getSprite("playerSprite_top"),
        ResourceManager::getSprite("playerSprite_bottom"),
        ResourceManager::getSprite("playerSprite_left"),
        ResourceManager::getSprite("playerSprite_right"),
        0.00000005f, glm::vec2(16.f, 22.f), glm::vec2(16.f, 22.f));
    m_pLevel = std::make_unique<Level>(ResourceManager::getLevels()[0]);

    return true;
}