#include "Game.h"

#include "../Resources/ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/AnimatedSprite.h"

#include "Player.h"

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
    if (m_pPlayer) {
        m_pPlayer->render();
    }
}

void Game::update(const uint64_t delta) {
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

    auto pAnimatedSprite = ResourceManager::loadAnimatedSprite("NewAnimatedSprite", "mapTextureAtlas", "spriteShader", 100, 100, "rightChicken_1");
    pAnimatedSprite->setPosition(glm::vec2(300, 300));
    std::vector<std::pair<std::string, uint64_t>> chickenState;

    chickenState.emplace_back(std::make_pair<std::string, uint64_t>("rightChicken_1", 500000000));
    chickenState.emplace_back(std::make_pair<std::string, uint64_t>("rightChicken_2", 500000000));
    chickenState.emplace_back(std::make_pair<std::string, uint64_t>("rightChicken_3", 500000000));
    chickenState.emplace_back(std::make_pair<std::string, uint64_t>("rightChicken_4", 500000000));

    std::vector<std::pair<std::string, uint64_t>> testState;

    testState.emplace_back(std::make_pair<std::string, uint64_t>("fruit", 500000000));
    testState.emplace_back(std::make_pair<std::string, uint64_t>("stone", 500000000));

    pAnimatedSprite->insertState("testState", std::move(testState));
    pAnimatedSprite->insertState("chickenState", std::move(chickenState));

    pAnimatedSprite->setState("chickenState");

    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f);

    pSpriteShaderProgram->use();
    pSpriteShaderProgram->setInt("tex", 0);
    pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

    auto pPlayerAnimatedSprite = ResourceManager::getAnimatedSprite("playerAnimatedSprite");
    if (!pPlayerAnimatedSprite) {
        std::cerr << "Can't find animated sprite" << "playerAnimatedSprite" << std::endl;
        return false;
    }

    m_pPlayer = std::make_unique<Player>(pPlayerAnimatedSprite, 0.0000002f, glm::vec2(100.f, 100.f));

    return true;
}