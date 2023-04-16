#include "StartScreen.h"

#include <iostream>

#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"


std::shared_ptr<RenderEngine::Sprite> getSpriteForDescription(const char description)
{
    switch (description)
    {
    case '0':
        return ResourceManager::getSprite("leftTopGrass");
    case '1':
        return ResourceManager::getSprite("middleTopGrass");
    case '4':                                              
        return ResourceManager::getSprite("middleGrass");
    case '6':                                              
        return ResourceManager::getSprite("leftDownGrass");
    case '7':                                              
        return ResourceManager::getSprite("middleDownGrass");
    case 'E':
        return nullptr;
    default:
        std::cerr << "Unknown Start Level description: " << description << std::endl;
    }
    return nullptr;
}

StartScreen::StartScreen(const std::vector<std::string>& startScreenDescription)
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
}

void StartScreen::update(const double delta)
{

}