#include "StartScreen.h"

#include <iostream>
#include <array>

#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"
#include "../Game.h"

#include <GLFW/glfw3.h>


std::shared_ptr<RenderEngine::Sprite> getSpriteForDescription(const char description)
{
    switch (description)
    {
    case '0':
        return ResourceManager::getSprite("leftTopGrass");
    case '1':
        return ResourceManager::getSprite("middleTopGrass");
    case '2':
        return ResourceManager::getSprite("rightTopGrass");
    case '3':
        return ResourceManager::getSprite("leftGrass");
    case '4':                                              
        return ResourceManager::getSprite("middleGrass");
    case '5':
        return ResourceManager::getSprite("rightGrass");
    case '6':                                              
        return ResourceManager::getSprite("leftDownGrass");
    case '7':                                              
        return ResourceManager::getSprite("middleDownGrass");
    case '8':
        return ResourceManager::getSprite("rightDownGrass");
    case 'E':
        return nullptr;
    default:
        std::cerr << "Unknown Start Level description: " << description << std::endl;
    }
    return nullptr;
}

StartScreen::StartScreen(const std::vector<std::string>& startScreenDescription, Game* pGame)
    : m_pGame(pGame)
    , m_currentMenuSelection(0)
    , m_menuSprite(std::make_pair(ResourceManager::getSprite("title"), 
        glm::vec2(6 * BLOCK_SIZE, STARTSCREEN_HEIGHT - startScreenDescription.size() * BLOCK_SIZE - MENU_HEIGHT - 5 * BLOCK_SIZE)))
    , m_cursorSprite(std::make_pair(ResourceManager::getSprite("cursor"), 
        glm::vec2(7 * BLOCK_SIZE, m_menuSprite.second.y + 6 * BLOCK_SIZE - m_currentMenuSelection * 2 * BLOCK_SIZE + BLOCK_SIZE / 4.f)))
    , m_cursorAnimator(m_cursorSprite.first)
    , m_keyReleased(true)
{
    if (startScreenDescription.empty())
    {
        std::cerr << "Empty start screen description!" << std::endl;
    }

    auto leftOffsetPixels = 2 * BLOCK_SIZE;
    auto bottomOffset = STARTSCREEN_HEIGHT - 2 * BLOCK_SIZE;


    unsigned int currentBottomOffset = bottomOffset;
    for (const std::string& currentRow : startScreenDescription)
    {
        unsigned int currentLeftOffset = leftOffsetPixels;
        for (const char currentElement : currentRow)
        {
            m_sprites.emplace_back(std::make_pair(getSpriteForDescription(currentElement), glm::vec2(currentLeftOffset, currentBottomOffset)));
            currentLeftOffset += BLOCK_SIZE;
        }
        currentBottomOffset -= BLOCK_SIZE;
    }


}

unsigned int StartScreen::getStateWidth() const
{
    return STARTSCREEN_WIDTH;
}

unsigned int StartScreen::getStateHeight() const
{
    return STARTSCREEN_HEIGHT;
}

void StartScreen::render() const
{
    for (const auto& current : m_sprites)
    {
        if (current.first)
        {
            current.first->render(current.second, glm::vec2(BLOCK_SIZE), 0.f);
        }
    }

    m_menuSprite.first->render(m_menuSprite.second, glm::vec2(MENU_WIDTH, MENU_HEIGHT), 0.f);
    m_cursorSprite.first->render(glm::vec2(m_cursorSprite.second.x, m_cursorSprite.second.y - m_currentMenuSelection * 5.5f * BLOCK_SIZE), 
                                 glm::vec2(CURSOR_SIZE), 0.f, 0.f, m_cursorAnimator.getCurrentFrame());
}

void StartScreen::update(const double delta)
{
    m_cursorAnimator.update(delta);
}

void StartScreen::processInput(std::array<bool, 349>& keys) 
{
    if (!keys[GLFW_KEY_UP] && !keys[GLFW_KEY_DOWN])
    {
        m_keyReleased = true;
    }

    if (m_keyReleased)
    {
        if (keys[GLFW_KEY_UP])
        {
            m_keyReleased = false;
            m_currentMenuSelection--;
            if (m_currentMenuSelection < 0) {
                m_currentMenuSelection = 1;
            }
        }
        else if (keys[GLFW_KEY_DOWN])
        {
            m_keyReleased = false;
            m_currentMenuSelection++;
            if (m_currentMenuSelection > 1) {
                m_currentMenuSelection = 0;
            }
        }
    }

    if (keys[GLFW_KEY_ENTER])
    {
        switch (m_currentMenuSelection)
        {
        case 0:
            m_pGame->startNewLevel(4);
            break;
        case 1:
            m_pGame->setClose(true);
            break;
        default:
            break;
        }
    }
}