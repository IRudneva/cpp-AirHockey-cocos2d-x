#include "Ball.h"
#include "Domain.h"
#include "GameManager.h"

#include <vector>

USING_NS_CC;

Ball::Ball(Manager*const manager)
	: GameObject(manager)
{
	setInitialPosition(EventType::START_GAME);
}

void Ball::update(const std::array<std::unique_ptr<GameObject>, domain::AMOUNT_GAME_OBJECTS>& objects)
{
	GameObject::update(objects);
	const EventType event = GameObject::checkObjectCollision(objects);
	switch (event)
	{
	case COLLISION_BALL_WITH_PLAYER:
	{
		const auto [new_pos_ball, new_vel_ball] = calculatePositionAfterCollision(objects[ObjectType::PLAYER]);
		setPosition(new_pos_ball);
		setVelocity(new_vel_ball);
	}
	break;
	case COLLISION_BALL_WITH_SMART_PLAYER:
	{
		const auto [new_pos, new_vel] = calculatePositionAfterCollision(objects[ObjectType::SMART_PLAYER]);
		setPosition(new_pos);
		setVelocity(new_vel);
	}
	break;
	default:
		break;
	}

	ObjectType player = checkGoal();

	switch (player)
	{
	case PLAYER:
		setInitialPosition(EventType::GOAL_PLAYER);
		break;
	case SMART_PLAYER:
		setInitialPosition(EventType::GOAL_SMART_PLAYER);
		break;
	default:
		break;
	}

	manager_->updateScore(player);

	move();
}

std::tuple<cocos2d::Vec2, cocos2d::Vec2> Ball::calculatePositionAfterCollision(const std::unique_ptr<GameObject>& player) const {
	Vec2 next_pos = getNextPosition();
	Vec2 player_pos = player->getPosition();
	Vec2 player_vel = player->getVelocity();
	float player_radius = player->getRadius();

	Vec2 diff = next_pos - player_pos;
	
	float force = sqrt(getVelocity().distanceSquared(player_vel));
	
	float angle = atan2(diff.y, diff.x);
	
	Vec2 new_ball_velocity = Vec2::ZERO;
	new_ball_velocity.x = force * cos(angle) * 1.5f; // * 0.95;
	new_ball_velocity.y = force * sin(angle) * 1.5f; // * 0.95;
	
	Vec2 new_ball_position = Vec2::ZERO;
	new_ball_position.x = player_pos.x + (player_radius + getRadius() + force) * cos(angle);
	new_ball_position.y = player_pos.y + (player_radius + getRadius() + force) * sin(angle);

	if (new_ball_velocity.y < -10.0f)
	{
		auto f = new_ball_velocity.y - (-10.0f);
		new_ball_velocity.y = new_ball_velocity.y - f;

	}
	else if (new_ball_velocity.y > 10.0f) {
		auto f = new_ball_velocity.y - 10.0f;
		new_ball_velocity.y -= f;
	}

	return std::make_tuple( new_ball_position , new_ball_velocity );
}

void Ball::move()
{
	setVelocity(getVelocity() * 0.99f);
	setPosition(getPosition() + getVelocity());
}

void Ball::setInitialPosition(const EventType event)
{
	switch (event)
	{
	case START_GAME:
		setPosition(Vec2(domain::FRAME_SIZE.width * 0.5f, domain::FRAME_SIZE.height * 0.5f));
		break;
	case GOAL_PLAYER:
		setPosition(Vec2(domain::FRAME_SIZE.width * 0.5f, domain::FRAME_SIZE.height * 0.4f));
		break;
	case GOAL_SMART_PLAYER:
		setPosition(Vec2(domain::FRAME_SIZE.width * 0.5f, domain::FRAME_SIZE.height * 0.6f));
		break;
	default:
		break;
	}

	setVelocity(Vec2(0, 0));
}

const ObjectType Ball::checkGoal() const
{
	Vec2 ball_pos = getPosition();
	float radius = getRadius();

	float left_x = (domain::FRAME_SIZE.width / 2) - (domain::GOAL_WIDTH / 2);
	float right_x = (domain::FRAME_SIZE.width / 2) + (domain::GOAL_WIDTH / 2);
	float up_y = domain::FRAME_SIZE.height - domain::BORDER_BUFF;
	float down_y = domain::FRAME_SIZE.height - up_y;

	if ((ball_pos.x - radius >= left_x && ball_pos.x + radius <= right_x)
		&& (ball_pos.y + radius >= up_y || ball_pos.y - radius <= down_y))
	{
		return (ball_pos.y < domain::FRAME_SIZE.height * 0.5f) ? ObjectType::PLAYER : ObjectType::SMART_PLAYER;
	}

	return ObjectType::NONE;
}
