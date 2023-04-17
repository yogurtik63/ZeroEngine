#include "Home.h"

#include "../../Renderer/Sprite.h"
#include <iostream>

Home::Home(const std::shared_ptr<RenderEngine::Sprite> pSprite, glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
	: IGameObject(IGameObject::EObjectType::Home, position, size, rotation, layer)
	, m_pCurrentSprite(pSprite)
{
	for (float i = 0; i < 5; i++)
	{
		for (float j = 0; j < 4; j++)
		{
			m_colliders.emplace_back(glm::vec2(i * 16.f), m_size + j * 16.f);
			std::cout << "new collider" << std::endl;
		}
	}


	std::cout << "(" << m_size.x << ", " << m_size.y << ")" << std::endl;
	std::cout << "(" << m_size.x * 4 << ", " << m_size.y * 5 << ")" << std::endl;

	setName("home");
}


void Home::render() const 
{
	m_pCurrentSprite->render(m_position, m_size, m_rotation, m_layer);
}

void Home::update(const double delta) {}