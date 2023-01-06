#include "Player.h"
#include "Domain.h"

USING_NS_CC;

Player::Player(Manager* const manager)
	: GameObject(manager)
{
	setInitialPosition(EventType::START_GAME);
}

void Player::initListener() {
	listener_ = cocos2d::EventListenerTouchOneByOne::create();

	listener_->onTouchBegan = CC_CALLBACK_2(Player::onTouchBegan, this);
	listener_->onTouchMoved = CC_CALLBACK_2(Player::onTouchMoved, this);

	cocos2d::EventDispatcher* dispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener_, this);
}

void Player::setInitialPosition(const EventType event)
{
	setPosition(Vec2(domain::FRAME_SIZE.width * 0.5f, domain::FRAME_SIZE.height * 0.2f));
	setVelocity(Vec2(1, 1));
}

const EventType Player::checkBorderCollision() const
{
	const EventType event = GameObject::checkBorderCollision();
	if (event != EventType::NO_EVENT)
	{
		return event;
	}

	Vec2 next_pos = getNextPosition();

	if (next_pos.y + getRadius() > domain::FRAME_SIZE.height * 0.5f)
	{
		return EventType::PLAYER_HALF_FIELD_CROSSING;
	}

	return EventType::NO_EVENT;
}

bool  Player::onTouchBegan(const Touch* touch, Event* event)
{
	Vec2 position = getPosition();
	Vec2 tap = touch->getLocation();
	float dist = tap.distance(position);
	if (dist < getRadius())
	{
		return true;
	}
	return false;
}

void  Player::onTouchMoved(const Touch* touch, Event* event)
{
	Vec2 position = getPosition();
	Vec2 tap = touch->getLocation();
	Vec2 diff = touch->getDelta();
	setPosition(position + diff);
}