#include "HelloWorldScene.h"
#include "NewScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

int score = 0;
int lives = 3;
int missedNo = 0;
float speed = 1;
float countDownTime = 3.0f;
String scoreText;
bool stopTouch = false;


Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}

bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	scoreText = "score" + std::to_string(score);

	
	
	pauseBtn = MenuItemFont::create("PAUSE", CC_CALLBACK_1(HelloWorld::Pause, this));
	menuBtn = MenuItemFont::create("MENU", CC_CALLBACK_1(HelloWorld::Menu, this));

	pauseBtn->setPosition(visibleSize.width*0.9f, visibleSize.height*0.2f);
	menuBtn->setPosition(visibleSize.width*0.9f, visibleSize.height*0.9f);

	auto *menu = Menu::create(pauseBtn, menuBtn, NULL);

	menu->setPosition(0, 0);
	menuBtn->setScale(0.7f);
	menuBtn->setEnabled(false);
	pauseBtn->setScale(0.7f);

	pauseBtn->runAction(TintTo::create(2, Color3B::WHITE));
	
	
	//labels
	infoLabel = Label::createWithSystemFont("Collect Yellow!", "Marker Felt.ttf", 15);
	scoreLabel = Label::createWithSystemFont("SCORE: 0", "Arial", 15);
	livesLabel = Label::createWithSystemFont("Lives:3", "Arial", 15);
	boxMissedLabel = Label::createWithSystemFont("Missed:0", "Arial", 15);
	
	infoLabel->setPosition(visibleSize.width*0.9, visibleSize.height*0.3);
	scoreLabel->setPosition(visibleSize.width*0.9, visibleSize.height*0.8);
	livesLabel->setPosition(visibleSize.width*0.9, visibleSize.height*0.6);
	boxMissedLabel->setPosition(visibleSize.width*0.9, visibleSize.height*0.5);

	infoLabel->runAction(TintTo::create(2, Color3B::YELLOW));
	scoreLabel->runAction(TintTo::create(2, Color3B::RED));
	livesLabel->runAction(TintTo::create(2, Color3B::BLUE));
	boxMissedLabel->runAction(TintTo::create(2, Color3B::BLACK));

	infoLabel->enableShadow();
	infoLabel->enableBold();
	scoreLabel->enableBold();
	
	

	for (int i = 0; i < 4; i++)
	{
		auto box = Sprite::create("yellowBox.png");
		box->setPosition(Vec2(visibleSize.width / 10 + i*100 , visibleSize.height / 4));
		this->addChild(box);
		sprites.push_back(box);
	}
	
	Director::getInstance()->setClearColor(Color4F::GREEN);

	auto touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	
	sprite = Sprite::create("redBox.png");
	//sprite->setPosition(this->getBoundingBox().getMidX(), this->getBoundingBox().getMinY());

	//just changed positon outside screen i used reference of screen at other places
	//just this sprite as i used its size for stuffs
	sprite->setPosition(visibleSize.width*0.5, visibleSize.height*1.5);

	this->addChild(menu);
	this->addChild(sprite, 0);
	this->addChild(infoLabel);
	this->addChild(scoreLabel);
	this->addChild(livesLabel);
	this->addChild(boxMissedLabel);
	this->scheduleUpdate(); 
	return true;
}
void HelloWorld::ResetAll() {
	score = 0;
	lives = 3;
	missedNo = 0;
	speed = 1;
	stopTouch = false;
	pauseBtn->setString("PAUSE");
	Director::getInstance()->resume();
	
}
void HelloWorld::Menu(cocos2d::Ref *pSender) {
	
	ResetAll();
	auto scene = NewScene::createScene();
	Director::getInstance()->replaceScene(scene);
	Director::getInstance()->replaceScene(TransitionFlipX::create(2, scene));
}
void HelloWorld::Pause(cocos2d::Ref *pSender) {
	auto pauseNo = 0;
	if (pauseBtn->getString() == "PAUSE") {
		pauseNo = 1;
		stopTouch = true;
	}
	if (pauseBtn->getString() == "RESUME") {
		pauseNo = 2;
		stopTouch = false;
	}

	switch (pauseNo)
	{
	case 1:
		Director::getInstance()->pause();
		pauseBtn->setString("RESUME");
		pauseBtn->setScale(0.6f);
		menuBtn->setEnabled(true);
		break;
	case 2:
		pauseBtn->setString("PAUSE");
		pauseBtn->setScale(0.7f);
		menuBtn->setEnabled(false);
		Director::getInstance()->resume();
		break;
	}
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	if(stopTouch==false){
		Point pt = touch->getLocation();
		for (int i = 0; i < sprites.size(); i++) {
			if (sprites.at(i)->getBoundingBox().containsPoint(pt))
			{
				auto pos = sprites.at(i)->getPosition();
				score++;
				scoreLabel->setString("score: " + std::to_string(score));
				pos.y = this->getBoundingBox().getMinY() - (sprite->getBoundingBox().size.width); //chage position to below screen
				sprites.at(i)->setPosition(pos);
			}

		}
	}
	
	return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	cocos2d::log("touch ended");
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
	cocos2d::log("touch moved");
}

void HelloWorld::onTouchCancelled(Touch* touch, Event* event)
{
	cocos2d::log("touch cancelled");
}


void HelloWorld::update(float delta) {
	auto visibleSize = Director::getInstance()->getVisibleSize();

	for (int i = 0; i < sprites.size(); i++)
	{
		auto box = sprites.at(i);
		auto pos = sprites.at(i)->getPosition();
		box->setPositionY(box->getPositionY() + delta * 100*speed);
		if (pos.y >visibleSize.height) {
			pos.y = this->getBoundingBox().getMinY() - (sprite->getBoundingBox().size.width);
			box->setPosition(pos);
			missedNo++;
			boxMissedLabel->setString("Missed: " + std::to_string(missedNo));
			speed += 0.05;
		}
		
	}
	if (missedNo >= 2 ) {
		lives = 2;
		livesLabel->setString("Lives: " + std::to_string(lives));
	}
	if (missedNo >= 4) {
		lives = 1;
		livesLabel->setString("Lives: " + std::to_string(lives));
	}
	if (missedNo >= 6 ) {
		Death();
	}
}
void HelloWorld::Death() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	lives = 0;
	speed = 0;
	livesLabel->setString("Lives: " + std::to_string(lives));
	infoLabel->setPosition(visibleSize.width*0.5f, visibleSize.height*0.5f);
	infoLabel->setScale(3);
	infoLabel->setColor(Color3B::RED);
	infoLabel->setString("GAME OVER!");
	stopTouch = true;
	menuBtn->setEnabled(true);
	menuBtn->setPosition(visibleSize.width*0.5f, visibleSize.height*0.3f);
	pauseBtn->setEnabled(false);
	
}
