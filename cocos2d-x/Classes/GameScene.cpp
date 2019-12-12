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

#include "GameScene.h"
#include "obj/Player.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

GameScene::~GameScene()
{
}

void GameScene::update(float delta)
{
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.
	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameScene::menuCloseCallback, this));
	if (closeItem == nullptr
	|| closeItem->getContentSize().width <= 0
	|| closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 100);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height));
		// add the label as a child to this layer
		this->addChild(label, (int)zOlder::BG);
	}

	// 背景
	auto bgLayer = Layer::create();
	bgLayer->setName("BG_LAYER");// レイヤーの名前
	this->addChild(bgLayer, (int)zOlder::BG);
	// 背景画像
	auto bgSprite = Sprite::create("Environment/background.png");
	bgSprite->setPosition(Vec2(0, 0));
	bgSprite->setAnchorPoint(Vec2(0, 0));// 左上に描画
	bgLayer->addChild(bgSprite, (int)zOlder::BG);

	// スクロール(sc)設定をいれるレイヤー
	auto scLayer = Layer::create();
	scLayer->setName("SC_LAYER");
	this->addChild(scLayer, (int)zOlder::SC);

	// playerレイヤー
	//auto plLayer = Layer::create();
	//plLayer->setName("PLAYER_LAYER");
	//this->addChild(plLayer, (int)zOlder::CHAR);

	// プレイヤー画像（初期設定のあいつ）
	//auto spriteIC = Sprite::create("HelloWorld.png");
	//spriteIC->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//plLayer->addChild(spriteIC, (int)zOlder::CHAR);
	//auto moveBy = MoveBy::create(5, Vec2(200, 0));
	//spriteIC->runAction(moveBy);

	/* 右スクロール*/
	//scLayer->runAction(Follow::create(spriteIC, Rect(0, 0, visibleSize.width*2.5, visibleSize.height)));// キャラが移動して動く
	//bgLayer->runAction(Follow::create(spriteIC, Rect(0, 0, visibleSize.width*2.5, visibleSize.height)));// 背景がついていく

	// プレイヤー画像(授業のあいつ)
	auto charLayer = Layer::create();
	charLayer->setName("CHAR_LAYER");
	auto plSprite = Player::createPlayer();
	charLayer->addChild((Node*)plSprite, (int)zOlder::CHAR);
	plSprite->setName("player");

	// キャラレイヤーをGameSceneにぶら下げる
	this->addChild(charLayer, (int)zOlder::CHAR);

	// playerクラスのupdateを呼ぶ
	plSprite->scheduleUpdate();

	return true;
}

void GameScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
