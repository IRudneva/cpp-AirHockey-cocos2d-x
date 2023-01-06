#pragma once

#include "GameObject.h"
#include "cocos2d.h"

class Player : public GameObject
{
public:
	explicit Player(Manager * const manager);

	void initListener() override;
	
	void setInitialPosition(const EventType event) override;

private:
	cocos2d::EventListenerTouchOneByOne* listener_ = nullptr;

	const EventType checkBorderCollision() const override;

	bool onTouchBegan(const cocos2d::Touch* touch, cocos2d::Event* event);

	void onTouchMoved(const cocos2d::Touch* touch, cocos2d::Event* event);
};