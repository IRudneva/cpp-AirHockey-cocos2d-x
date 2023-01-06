#include "SmartPlayer.h"
#include "Domain.h"

USING_NS_CC;

SmartPlayer::SmartPlayer(Manager* const manager)
	: GameObject(manager)
{
	setInitialPosition(EventType::START_GAME);
}

void SmartPlayer::update(const std::array<std::unique_ptr<GameObject>, domain::AMOUNT_GAME_OBJECTS>& objects) {
	GameObject::update(objects);

	chaseBall(objects[ObjectType::BALL]);
}

void SmartPlayer::chaseBall(const std::unique_ptr<GameObject>& ball) {
	const Vec2 ball_pos = ball->getPosition();
	const Vec2 ball_dir = ball->getVelocity();
	const float ball_rad = ball->getRadius();

	const Vec2 player_pos = getPosition();
	const Vec2 player_dir = getVelocity();
	const Vec2 player_start_pos = Vec2(domain::FRAME_SIZE.width * 0.5f, domain::FRAME_SIZE.height * 0.8f);

	setPosition(Vec2(player_pos.x + ball_dir.x * 0.3f, getPosition().y));

	Vec2 new_vel = Vec2::ZERO;

	if (player_pos.y < player_start_pos.y)
	{
		new_vel = player_start_pos - player_pos;
		new_vel = new_vel / new_vel.length();
		setVelocity(new_vel * 2.0f);
		move();
	}

	if (bool ball_on_player_side = ball_pos.y > domain::FRAME_SIZE.height * 0.5f; ball_on_player_side)
	{
		new_vel = ball_pos - player_pos;
		new_vel = new_vel / new_vel.length();
		setVelocity(new_vel * 4.0f);
		move();
	}
}

void SmartPlayer::move() 
{
	setPosition(getPosition() + getVelocity());
}

const EventType SmartPlayer::checkBorderCollision() const
{
	const EventType event = GameObject::checkBorderCollision();
	if (event != EventType::NO_EVENT)
	{
		return event;
	}

	Vec2 next_pos = getNextPosition();

	if (next_pos.y - getRadius() < domain::FRAME_SIZE.height * 0.5f)
	{
		return EventType::SMART_PLAYER_HALF_FIELD_CROSSING;
	}

	return EventType::NO_EVENT;
}

void SmartPlayer::setInitialPosition(const EventType event)
{
	setPosition(Vec2(domain::FRAME_SIZE.width * 0.5f, domain::FRAME_SIZE.height * 0.8f));
	setVelocity(Vec2(1, 1));
}