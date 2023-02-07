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
    auto pDefaultShaderProgram = ResourceManager::loadShaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
    if (!pDefaultShaderProgram) {
        std::cerr << "Can't create shader program: " << "DefaultShader" << std::endl;
        return false;
    }

    auto pSpriteShaderProgram = ResourceManager::loadShaders("SpriteShader", "res/shaders/vSprite.txt", "res/shaders/fSprite.txt");
    if (!pSpriteShaderProgram) {
        std::cerr << "Can't create shader program: " << "SpriteShader" << std::endl;
        return false;
    }

    auto tex = ResourceManager::loadTexture("DefaultTexture", "res/textures/map_13x10.png");

    std::vector<std::string> subTexturesName =
    {
        "leftTopGrass", "middleTopGrass", "rightTopGrass", "leftDown_rightTopGrass", "leftTopCorner_rightDownGrass", "dirt1", "dirt2", "dirt3", "smallGrass", "fruit", "stone", "flowers", "",
        "leftGrass", "middleGrass", "rightGrass", "rightDown_FullGrass", "leftDown_FullGrass", "", "", "", "", "", "",  "", "",
        "", "", "", "", "", "",  "", "", "", "", "", "", "",
        "", "", "", "", "", "",  "", "", "", "", "", "", "",
        "", "", "", "", "", "",  "", "", "", "", "", "", "",
        "", "", "", "", "", "",  "", "", "", "", "", "", "",
        "", "", "", "", "", "",  "", "", "", "", "", "", "",
        "", "", "", "", "", "",  "", "", "", "", "", "", "",
        "rightChicken_1", "rightChicken_2", "rightChicken_3", "rightChicken_4"
    };
    auto pTextureAtlas = ResourceManager::loadTextureAtlas("DefaultTextureAtlas", "res/textures/map_13x10.png", std::move(subTexturesName), 16, 16);

    auto pAnimatedSprite = ResourceManager::loadAnimatedSprite("NewAnimatedSprite", "DefaultTextureAtlas", "SpriteShader", 100, 100, "rightChicken_1");
    pAnimatedSprite->setPosition(glm::vec2(300, 100));
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

    pDefaultShaderProgram->use();
    pDefaultShaderProgram->setInt("tex", 0);

    glm::mat4 modelMatrix_1 = glm::mat4(1.f);
    modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(100.f, 50.f, 0.f));

    glm::mat4 modelMatrix_2 = glm::mat4(1.f);
    modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(590.f, 50.f, 0.f));

    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f);

    pDefaultShaderProgram->setMatrix4("projectionMat", projectionMatrix);

    pSpriteShaderProgram->use();
    pSpriteShaderProgram->setInt("tex", 0);
    pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

    std::vector<std::string> playerSubTexturesName =
    {
        "playerRight1", "playerRight2", "playerRight3", "playerRight4",
        "playerRight5", "playerRight6", "playerRight7", "playerRight8",
        "playerLeft1", "playerLeft2", "playerLeft3", "playerLeft4",
        "playerLeft5", "playerLeft6", "playerLeft7", "playerLeft8",
    };
    
    auto pPlayerTextureAtlas = ResourceManager::loadTextureAtlas("PlayerTextureAtlas", "res/textures/player_1.png", std::move(playerSubTexturesName), 16, 22);
    auto pPlayerAnimatedSprite = ResourceManager::loadAnimatedSprite("PlayerAnimatedSprite", "PlayerTextureAtlas", "SpriteShader", 48, 66, "playerRight1");

    std::vector<std::pair<std::string, uint64_t>> playerRightState;

    playerRightState.emplace_back(std::make_pair<std::string, uint64_t>("playerRight1", 500000000));
    playerRightState.emplace_back(std::make_pair<std::string, uint64_t>("playerRight2", 500000000));
    playerRightState.emplace_back(std::make_pair<std::string, uint64_t>("playerRight3", 500000000));
    playerRightState.emplace_back(std::make_pair<std::string, uint64_t>("playerRight4", 500000000));
    playerRightState.emplace_back(std::make_pair<std::string, uint64_t>("playerRight5", 500000000));
    playerRightState.emplace_back(std::make_pair<std::string, uint64_t>("playerRight6", 500000000));
    playerRightState.emplace_back(std::make_pair<std::string, uint64_t>("playerRight7", 500000000));
    playerRightState.emplace_back(std::make_pair<std::string, uint64_t>("playerRight8", 500000000));

    std::vector<std::pair<std::string, uint64_t>> playerLeftState;

    playerLeftState.emplace_back(std::make_pair<std::string, uint64_t>("playerLeft1", 500000000));
    playerLeftState.emplace_back(std::make_pair<std::string, uint64_t>("playerLeft2", 500000000));
    playerLeftState.emplace_back(std::make_pair<std::string, uint64_t>("playerLeft3", 500000000));
    playerLeftState.emplace_back(std::make_pair<std::string, uint64_t>("playerLeft4", 500000000));
    playerLeftState.emplace_back(std::make_pair<std::string, uint64_t>("playerLeft5", 500000000));
    playerLeftState.emplace_back(std::make_pair<std::string, uint64_t>("playerLeft6", 500000000));
    playerLeftState.emplace_back(std::make_pair<std::string, uint64_t>("playerLeft7", 500000000));
    playerLeftState.emplace_back(std::make_pair<std::string, uint64_t>("playerLeft8", 500000000));

    pPlayerAnimatedSprite->insertState("playerRightState", std::move(playerRightState));
    pPlayerAnimatedSprite->insertState("playerLeftState", std::move(playerLeftState));

    pPlayerAnimatedSprite->setState("playerRightState");

    m_pPlayer = std::make_unique<Player>(pPlayerAnimatedSprite, 0.0000002f, glm::vec2(100.f, 100.f));

    return true;
}