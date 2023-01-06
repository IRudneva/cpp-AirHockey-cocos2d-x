#pragma once

#include "cocos2d.h"
#include "GameObject.h"
#include "Domain.h"

#include <array>

class Manager final 
{
public:
	Manager() = default;

	Manager* initGameObjects();

	const Manager* uniteSpritesWithGameObjects(const std::array<cocos2d::Sprite*, domain::AMOUNT_GAME_OBJECTS>& object_sprites);

	const std::array<std::unique_ptr<GameObject>, domain::AMOUNT_GAME_OBJECTS>& getGameObjects() const { return objects_; }

	void updateGameObjects();

	void updateSprite(const std::array<cocos2d::Sprite*, domain::AMOUNT_GAME_OBJECTS>& object_sprites);

	void updateScore(const ObjectType player);

	int getScorePlayer() const { return score_player_; }

	int getScoreSmartPlayer() const { return score_smart_player_; }

private:
	std::array<std::unique_ptr<GameObject>, domain::AMOUNT_GAME_OBJECTS> objects_ = { nullptr, nullptr ,nullptr };

	int score_player_ = 0;
	int score_smart_player_ = 0;
};
