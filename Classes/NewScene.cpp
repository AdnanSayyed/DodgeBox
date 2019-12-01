#include "NewScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* NewScene::createScene()
{
	auto scene = Scene::create();
	auto layer = NewScene::create();
	scene->addChild(layer);
	return scene;
}

bool NewScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Director::getInstance()->setClearColor(Color4F::ORANGE);


	auto PlayBtn = MenuItemFont::create("PLAY", CC_CALLBACK_1(NewScene::Play, this));
	PlayBtn->setPosition(visibleSize.width*0.5f, visibleSize.height*0.5f);
	PlayBtn->setFontSize(40);
	PlayBtn->setColor(Color3B::YELLOW);
	auto *menu = Menu::create(PlayBtn, NULL);
	menu->setPosition(0, 0);
	this->addChild(menu);
	return true;
}

void NewScene::Play(cocos2d::Ref *pSender) {
	auto scene = HelloWorld::createScene();
	//Director::getInstance()->pushScene(scene);
	Director::getInstance()->pushScene(TransitionFade::create(0.03, scene, Color3B(0, 255, 255)));
}

bool NewScene::onTouchBegan(Touch* touch, Event* event)
{
	
	Point pt = touch->getLocation();
	return true;
}

void NewScene::onTouchEnded(Touch* touch, Event* event)
{
	cocos2d::log("touch ended");
}

void NewScene::onTouchMoved(Touch* touch, Event* event)
{
	cocos2d::log("touch moved");
}

void NewScene::onTouchCancelled(Touch* touch, Event* event)
{
	cocos2d::log("touch cancelled");
}

void NewScene::update(float delta) {

}
