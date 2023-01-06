/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "GraphicsScene.h"
#include "Domain.h"

USING_NS_CC;


Scene* GraphicsScene::createScene()
{
	Scene* scene = Scene::create();
	GraphicsScene* layer = GraphicsScene::create();

	scene->addChild(layer);
	return scene;
}

bool GraphicsScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	initPlayingField();
	setFrameSize();
	initGameSprites();
	initScoreLabel();
	initManager();

	this->schedule(CC_SCHEDULE_SELECTOR(GraphicsScene::update));

	return true;
}

void GraphicsScene::update(float dt)
{
	manager_->updateGameObjects();
	manager_->updateSprite(object_sprites_);
	updateScoreLabel(manager_->getScorePlayer(), manager_->getScoreSmartPlayer());
}

void GraphicsScene::updateScoreLabel(const int player, const int smart_player) {
	score_label_.player->setString(std::to_string(player));
	score_label_.smart_player->setString(std::to_string(smart_player));
}

void GraphicsScene::setFrameSize()
{
	screen_size_ = frame_->getTextureRect().size;
	Director::getInstance()->getOpenGLView()->setFrameSize(screen_size_.width, screen_size_.height);
	Director::getInstance()->getOpenGLView()->setDesignResolutionSize(screen_size_.width, screen_size_.height, ResolutionPolicy::SHOW_ALL);
}

void GraphicsScene::initPlayingField()
{
	frame_ = Sprite::create("rect.png");
	frame_->setAnchorPoint(Vec2(0, 0));
	frame_->setPosition(Vec2(0, 0));

	this->addChild(frame_);
}

void  GraphicsScene::initGameSprites()
{
	Sprite* sprite_ball = Sprite::create("puck.png");
	sprite_ball->setScale(0.4f);
	object_sprites_[ObjectType::BALL] = sprite_ball;
	this->addChild(object_sprites_[ObjectType::BALL]);

	Sprite* sprite_player = Sprite::create("mallet.png");
	sprite_player->setScale(0.4f);
	object_sprites_[ObjectType::PLAYER] = sprite_player;
	this->addChild(object_sprites_[ObjectType::PLAYER]);

	Sprite* sprite_smart_player = Sprite::create("mallet.png");
	sprite_smart_player->setScale(0.4f);
	object_sprites_[ObjectType::SMART_PLAYER] = sprite_smart_player;
	this->addChild(object_sprites_[ObjectType::SMART_PLAYER]);
}

void GraphicsScene::initScoreLabel() {
	score_label_.player = Label::createWithTTF("0", "fonts/awx.ttf", 50.0f);
	score_label_.player->setPosition(Vec2(domain::FRAME_SIZE.width - 30.0f, domain::FRAME_SIZE.height * 0.5f + 80.0f));
	score_label_.player->setRotation(90);
	score_label_.player->setColor(Color3B::GRAY);
	addChild(score_label_.player);

	score_label_.smart_player = Label::createWithTTF("0", "fonts/awx.ttf", 50.0f);
	score_label_.smart_player->setPosition(Vec2(domain::FRAME_SIZE.width - 30.0f, domain::FRAME_SIZE.height * 0.5f - 80.0f));
	score_label_.smart_player->setRotation(90);
	score_label_.smart_player->setColor(Color3B::GRAY);
	addChild(score_label_.smart_player);
}

void GraphicsScene::initManager() {
	manager_ = std::make_unique<Manager>();
	manager_->initGameObjects()->uniteSpritesWithGameObjects(object_sprites_);

	for (const auto& obj : manager_->getGameObjects())
	{
		this->addChild(obj.get());
	}
}
