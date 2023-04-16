#include "PhysicsEngine.h"

#include "../Game/GameObjects/IGameObject.h"
#include "../Game/GameStates/Level.h"

#include <iostream>

namespace Physics {

	std::unordered_set<std::shared_ptr<IGameObject>> PhysicsEngine::m_dynamicObjects;
	std::shared_ptr<Level> PhysicsEngine::m_pCurrentLevel;

	bool playerTouch;
	bool bulletTouch;
	std::shared_ptr<IGameObject> objectToDestroy1;
	std::shared_ptr<IGameObject> objectToDestroy2;

	void PhysicsEngine::init() {
		
	}

	void PhysicsEngine::terminate() {
		m_dynamicObjects.clear();
	}

	void PhysicsEngine::addDynamicGameObject(std::shared_ptr<IGameObject> pGameObject) {
		m_dynamicObjects.insert(std::move(pGameObject));
	}

	void PhysicsEngine::setCurrentLevel(std::shared_ptr<Level> pLevel) {
		m_pCurrentLevel.swap(pLevel);
		m_dynamicObjects.clear();
		m_pCurrentLevel->initPhysics();
	}

	void PhysicsEngine::update(const double delta) {
		objectToDestroy1 = nullptr;
		objectToDestroy2 = nullptr;
		for (auto& currentDynamicObject : m_dynamicObjects) {
			if (currentDynamicObject->getCurrentVelocity() > 0) {

				if (currentDynamicObject->getCurrentDirection().x != 0.f)
				{
					currentDynamicObject->getCurrentPosition() = glm::vec2(
						currentDynamicObject->getCurrentPosition().x,
						static_cast<unsigned int>(currentDynamicObject->getCurrentPosition().y / 4.f + 0.5f) * 4.f);
				}
				else if (currentDynamicObject->getCurrentDirection().y != 0.f)
				{
					currentDynamicObject->getCurrentPosition() = glm::vec2(
						static_cast<unsigned int>(currentDynamicObject->getCurrentPosition().x / 4.f + 0.5f) * 4.f,
						currentDynamicObject->getCurrentPosition().y);
				}

				const auto newPosition = currentDynamicObject->getCurrentPosition() + currentDynamicObject->getCurrentDirection() * static_cast<float>(currentDynamicObject->getCurrentVelocity() * delta);
				std::vector<std::shared_ptr<IGameObject>> objectsToCheck = m_pCurrentLevel->getObjectsInArea(newPosition, newPosition + currentDynamicObject->getSize());


				const auto& colliders = currentDynamicObject->getColliders();
				bool hasCollision = false;

				ECollisionDirection dynamicObjectCollisionDirection = ECollisionDirection::Right;
				if (currentDynamicObject->getCurrentDirection().x < 0) dynamicObjectCollisionDirection = ECollisionDirection::Left;
				else if (currentDynamicObject->getCurrentDirection().y > 0) dynamicObjectCollisionDirection = ECollisionDirection::Top;
				else if (currentDynamicObject->getCurrentDirection().y < 0) dynamicObjectCollisionDirection = ECollisionDirection::Bottom;

				ECollisionDirection objectCollisionDirection = ECollisionDirection::Left;
				if (currentDynamicObject->getCurrentDirection().x < 0) objectCollisionDirection = ECollisionDirection::Right;
				else if (currentDynamicObject->getCurrentDirection().y > 0) objectCollisionDirection = ECollisionDirection::Bottom;
				else if (currentDynamicObject->getCurrentDirection().y < 0) objectCollisionDirection = ECollisionDirection::Top;

				for (const auto& currentDynamicObjectCollider : colliders)
				{
					for (const auto& currentObjectToCheck : objectsToCheck)
					{
						playerTouch = false;
						bulletTouch = false;

						const auto& collidersToCheck = currentObjectToCheck->getColliders();
						if (currentObjectToCheck->collides(currentDynamicObject->getObjectType()) && !collidersToCheck.empty())
						{
							for (const auto& currentObjectCollider : currentObjectToCheck->getColliders())
							{
								if (currentObjectCollider.isActive && hasIntersection(currentDynamicObjectCollider, newPosition, currentObjectCollider, currentObjectToCheck->getCurrentPosition()))
								{
									
									/*if (!playerTouch)
									{
										playerTouch = currentDynamicObject->getObjectType() == IGameObject::EObjectType::Player;
									}

									if (!bulletTouch)
									{
										bulletTouch = currentDynamicObject->getObjectType() == IGameObject::EObjectType::Bullet;
									}

									if (playerTouch) {
										objectToDestroy1 = currentObjectToCheck;
									}

									if (bulletTouch) {
										objectToDestroy2 = currentObjectToCheck;
									}

									if (objectToDestroy1 == objectToDestroy2)
									{
										std::cout << "THERE WAS AN INTERSECTION (PLAYER AND BULLET): " << currentObjectToCheck->getName() << std::endl;
										if (currentObjectCollider.onCollisionCallback)
										{
											std::cout << "DELETE STONE" << std::endl;
											currentObjectCollider.onCollisionCallback(*currentDynamicObject, objectCollisionDirection);
										}
									}*/

									if (currentDynamicObject->getObjectType() == IGameObject::EObjectType::Bullet)
									{
										if (currentObjectCollider.onCollisionCallback)
										{
											if ((currentDynamicObject->getToolBullet() == IGameObject::EToolBullet::Pickaxe &&
												currentObjectToCheck->getObjectType() == IGameObject::EObjectType::Stone) ||
												(currentDynamicObject->getToolBullet() == IGameObject::EToolBullet::Axe &&
												currentObjectToCheck->getObjectType() == IGameObject::EObjectType::Log))
											{
												currentObjectCollider.onCollisionCallback(*currentDynamicObject, objectCollisionDirection);
											}

										}
									}

									/*std::cout << "THERE WAS AN INTERSECTION: " << currentDynamicObject->getName() << ", " << currentObjectToCheck->getName() << std::endl;*/
									hasCollision = true;
									/*if (currentObjectCollider.onCollisionCallback)
									{
										currentObjectCollider.onCollisionCallback(*currentDynamicObject, objectCollisionDirection);
									}*/
									if (currentDynamicObjectCollider.onCollisionCallback)
									{
										currentDynamicObjectCollider.onCollisionCallback(*currentObjectToCheck, dynamicObjectCollisionDirection);
									}
								}
							}
						}
					}
				}

				if (!hasCollision) {
					currentDynamicObject->getCurrentPosition() = newPosition;
				}
				else
				{
					if (currentDynamicObject->getCurrentDirection().x != 0.f)
					{
						currentDynamicObject->getCurrentPosition() = glm::vec2(
							currentDynamicObject->getCurrentPosition().x,
							static_cast<unsigned int>(currentDynamicObject->getCurrentPosition().y / 4.f + 0.5f) * 4.f);
					}
					else if (currentDynamicObject->getCurrentDirection().y != 0.f)
					{
						currentDynamicObject->getCurrentPosition() = glm::vec2(
							static_cast<unsigned int>(currentDynamicObject->getCurrentPosition().x / 4.f + 0.5f) * 4.f,
							currentDynamicObject->getCurrentPosition().y);
					}

					currentDynamicObject->onCollision(); // collision of block */

					/*if (currentObject->getObjectType() == IGameObject::EObjectType::Bullet)
					{
						std::cout << "Bullet shot" << std::endl;
					}*/
				}
			}
		}
	}

	bool PhysicsEngine::hasIntersection(const Collider& collider1, const glm::vec2& position1,
										const Collider& collider2, const glm::vec2& position2)
	{
		const glm::vec2 collider1_bottomLeft_world = collider1.boundingBox.bottomLeft + position1;
		const glm::vec2 collider1_topRight_world = collider1.boundingBox.topRight + position1;

		const glm::vec2 collider2_bottomLeft_world = collider2.boundingBox.bottomLeft + position2;
		const glm::vec2 collider2_topRight_world = collider2.boundingBox.topRight + position2;

		if (collider1_bottomLeft_world.x >= collider2_topRight_world.x)
		{
			return false;
		}
		if (collider1_topRight_world.x <= collider2_bottomLeft_world.x)
		{
			return false;
		}

		if (collider1_bottomLeft_world.y >= collider2_topRight_world.y)
		{
			return false;
		}
		if (collider1_topRight_world.y <= collider2_bottomLeft_world.y)
		{
			return false;
		}

		return true;
	}
}