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
#pragma once

#include "cocos2d.h"
#include "GameManager.h"

#include <array>

class GraphicsScene final : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void update(float dt);

	void updateScoreLabel(const int player, const int smart_player);

	const cocos2d::Size & getFrameSize() const { return screen_size_; }

	CREATE_FUNC(GraphicsScene);

private:
	cocos2d::Size screen_size_;
	cocos2d::Sprite* frame_ = nullptr;
	std::unique_ptr<Manager> manager_ = nullptr;

	std::array<cocos2d::Sprite*, domain::AMOUNT_GAME_OBJECTS> object_sprites_ = { nullptr, nullptr, nullptr };

	struct ScoreLabel
	{
		cocos2d::Label* player = nullptr;
		cocos2d::Label* smart_player = nullptr;
	} score_label_;

	void setFrameSize();
	void initPlayingField();
	void initGameSprites();
	void initScoreLabel();
	void initManager();
};

