#pragma once

#include "cocos2d.h"
#include "Domain.h"

#include <array>
#include <tuple>

class Manager;

class GameObject :public cocos2d::Node
{
protected:
	explicit GameObject(Manager* const manager);

public:
	virtual void update(const std::array<std::unique_ptr<GameObject>, domain::AMOUNT_GAME_OBJECTS>& objects);

	virtual void setInitialPosition(const EventType event) = 0;

	void setRadius(float radius);

	const cocos2d::Vec2& getVelocity() const { return velocity_; }

	float getRadius() const { return radius_; }

	virtual void initListener(){}

	virtual ~GameObject() = default;

protected:
	Manager* manager_ = nullptr;

	const cocos2d::Vec2 getNextPosition() const;

	virtual const EventType checkBorderCollision() const;

	virtual const EventType checkObjectCollision(const std::array<std::unique_ptr<GameObject>, domain::AMOUNT_GAME_OBJECTS>& objects) const;

	void setVelocity(const cocos2d::Vec2& direction);

private:
	cocos2d::Vec2 velocity_ = cocos2d::Vec2::ZERO;
	float radius_ = 0.0f;
};

