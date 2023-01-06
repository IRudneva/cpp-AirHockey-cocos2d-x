#pragma once

#include "GameObject.h"
#include <tuple>

class Ball : public GameObject
{
public:

	explicit Ball(Manager *const manager);

	void update(const std::array<std::unique_ptr<GameObject>, domain::AMOUNT_GAME_OBJECTS>& objects) override;

	void setInitialPosition(const EventType event) override;

private:
	void move();

	std::tuple<cocos2d::Vec2, cocos2d::Vec2> calculatePositionAfterCollision(const std::unique_ptr<GameObject>& player) const;

	const ObjectType checkGoal() const;
};
