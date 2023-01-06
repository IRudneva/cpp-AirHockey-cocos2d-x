#include "GameManager.h"
#include "Player.h"
#include "Ball.h"
#include "SmartPlayer.h"

#include <string>

USING_NS_CC;

Manager* Manager::initGameObjects() 
{
	objects_[ObjectType::BALL] = std::make_unique<Ball>(this);
	objects_[ObjectType::PLAYER] = std::make_unique<Player>(this);
	objects_[ObjectType::SMART_PLAYER] = std::make_unique<SmartPlayer>(this);
	return this;
}

const Manager* Manager::uniteSpritesWithGameObjects(const std::array<cocos2d::Sprite*, domain::AMOUNT_GAME_OBJECTS>& object_sprites)
{
	objects_[ObjectType::BALL]->setRadius(object_sprites[ObjectType::BALL]->getTexture()->getContentSize().width * object_sprites[ObjectType::BALL]->getScale() *0.5f);
	objects_[ObjectType::PLAYER]->setRadius(object_sprites[ObjectType::PLAYER]->getTexture()->getContentSize().width * object_sprites[ObjectType::BALL]->getScale() *0.5f);
	objects_[ObjectType::SMART_PLAYER]->setRadius(object_sprites[ObjectType::SMART_PLAYER]->getTexture()->getContentSize().width * object_sprites[ObjectType::BALL]->getScale() *0.5f);

	objects_[ObjectType::PLAYER]->initListener();
	return this;
}

void Manager::updateGameObjects()
{
	for (const auto& obj : objects_)
	{
		obj->update(objects_);
	}
}

void Manager::updateSprite(const std::array<cocos2d::Sprite*, domain::AMOUNT_GAME_OBJECTS>& object_sprites) 
{
	object_sprites[ObjectType::BALL]->setPosition(objects_[ObjectType::BALL]->getPosition());
	object_sprites[ObjectType::PLAYER]->setPosition(objects_[ObjectType::PLAYER]->getPosition());
	object_sprites[ObjectType::SMART_PLAYER]->setPosition(objects_[ObjectType::SMART_PLAYER]->getPosition());
}

void Manager::updateScore(const ObjectType player)
{
	if (player == ObjectType::PLAYER)
	{
		++score_player_;
	}
	else if (player == ObjectType::SMART_PLAYER)
	{
		++score_smart_player_;
	}

	if (score_player_ == domain::MAX_GOAL || score_smart_player_ == domain::MAX_GOAL)
	{
		score_player_ = 0;
		score_smart_player_ = 0;

		for (const auto& obj : objects_)
		{
			obj->setInitialPosition(EventType::START_GAME);
		}
	}
}
