#pragma once

#include "Player.h"

class SmartPlayer final : public GameObject
{
public:
	explicit SmartPlayer(Manager * const manager);

	void update(const std::array<std::unique_ptr<GameObject>, domain::AMOUNT_GAME_OBJECTS>& objects) override;

	void setInitialPosition(const EventType event) override;

private:
	void chaseBall(const std::unique_ptr<GameObject>& ball);

	void move();

	const EventType checkBorderCollision() const override;
};