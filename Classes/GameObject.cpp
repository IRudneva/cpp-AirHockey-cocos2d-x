#include "GameObject.h"
#include "Domain.h"

USING_NS_CC;

GameObject::GameObject(Manager* const manager)
	:manager_(manager)
{
}

void GameObject::update(const std::array<std::unique_ptr<GameObject>, domain::AMOUNT_GAME_OBJECTS>& objects)
{
	EventType event = checkBorderCollision();
	switch (event)
	{
	case COLLISION_WITH_AXES_X_RIGHT:
		setVelocity(Vec2(-std::abs(velocity_.x), velocity_.y));
		setPosition(Vec2(domain::FRAME_SIZE.width - domain::BORDER_BUFF - radius_, getPosition().y));
		break;
	case COLLISION_WITH_AXES_X_LEFT:
		setVelocity(Vec2(std::abs(velocity_.x), velocity_.y));
		setPosition(Vec2(domain::BORDER_BUFF + radius_, getPosition().y));
		break;
	case COLLISION_WITH_AXES_Y_UP:
		setVelocity(Vec2(velocity_.x, -std::abs(velocity_.y)));
		setPosition(Vec2(getPosition().x, domain::FRAME_SIZE.height - domain::BORDER_BUFF - radius_));
		break;
	case COLLISION_WITH_AXES_Y_DOWN:
		setVelocity(Vec2(velocity_.x, std::abs(velocity_.y)));
		setPosition(Vec2(getPosition().x, domain::BORDER_BUFF + radius_));
		break;
	case PLAYER_HALF_FIELD_CROSSING:
		setPosition(Vec2(getPosition().x, domain::FRAME_SIZE.height * 0.5f - radius_));
		break;
	case SMART_PLAYER_HALF_FIELD_CROSSING:
		setPosition(Vec2(getPosition().x, domain::FRAME_SIZE.height * 0.5f + radius_));
		break;
	default:
		break;
	}
}

const EventType GameObject::checkObjectCollision(const std::array<std::unique_ptr<GameObject>, domain::AMOUNT_GAME_OBJECTS>& objects) const
{
	Vec2 ball_pos = objects[ObjectType::BALL]->getPosition();
	Vec2 ball_next_pos = objects[ObjectType::BALL]->getNextPosition();
	float ball_radius = objects[ObjectType::BALL]->getRadius();
	Vec2 ball_vel = objects[ObjectType::BALL]->getVelocity();

	Vec2 player_pos = objects[ObjectType::PLAYER]->getPosition();
	float player_radius = objects[ObjectType::PLAYER]->getRadius();
	Vec2 player_vel = objects[ObjectType::PLAYER]->getVelocity();

	Vec2 smart_player_pos = objects[ObjectType::SMART_PLAYER]->getPosition();
	float smart_player_radius = objects[ObjectType::SMART_PLAYER]->getRadius();
	Vec2 smart_player_vel = objects[ObjectType::SMART_PLAYER]->getVelocity();

	float squared_radius_ball_player = pow(ball_radius + player_radius, 2);
	float squared_radius_ball_smart_player = pow(ball_radius + smart_player_radius, 2);

	float distance_ball_player_next = ball_next_pos.distanceSquared(player_pos);
	float distance_ball_player = ball_pos.distanceSquared(player_pos);

	float distance_ball_smart_player_next = ball_next_pos.distanceSquared(smart_player_pos);
	float distance_ball_smart_player = ball_pos.distanceSquared(smart_player_pos);

	if (distance_ball_player_next <= squared_radius_ball_player || distance_ball_player <= squared_radius_ball_player)
	{
		return EventType::COLLISION_BALL_WITH_PLAYER;
	}

	if (distance_ball_smart_player_next <= squared_radius_ball_smart_player || distance_ball_smart_player <= squared_radius_ball_smart_player)
	{
		return EventType::COLLISION_BALL_WITH_SMART_PLAYER;
	}

	return EventType::NO_EVENT;
}

void GameObject::setRadius(float radius) {
	radius_ = radius;
}

void GameObject::setVelocity(const cocos2d::Vec2& direction) {
	if (!velocity_.equals(direction))
	{
		velocity_ = direction;
	}
}

const cocos2d::Vec2 GameObject::getNextPosition() const {
	auto position = getPosition();
	return cocos2d::Vec2(position.x + velocity_.x, position.y + velocity_.y);
}

const EventType GameObject::checkBorderCollision() const
{
	auto position = getPosition();
	// Check collision by X axes.
	if (position.x + radius_ > domain::FRAME_SIZE.width - domain::BORDER_BUFF)
	{
		return EventType::COLLISION_WITH_AXES_X_RIGHT;
	}
	if (position.x - radius_ < domain::BORDER_BUFF)
	{
		return EventType::COLLISION_WITH_AXES_X_LEFT;
	}

	// Check collision by Y axes.
	if (position.y + radius_ > domain::FRAME_SIZE.height - domain::BORDER_BUFF)
	{
		return EventType::COLLISION_WITH_AXES_Y_UP;
	}
	if (position.y - radius_ < domain::BORDER_BUFF)
	{
		return EventType::COLLISION_WITH_AXES_Y_DOWN;
	}

	return EventType::NO_EVENT;
}