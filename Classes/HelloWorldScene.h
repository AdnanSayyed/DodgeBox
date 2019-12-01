#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init() override;
	CREATE_FUNC(HelloWorld);

	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);

	void update(float) override;
	void Menu(Ref *pSender);
	void Pause(Ref *pSender);
	void ResetAll();
	void Death();
	void Resume();
private:
	cocos2d::Sprite* sprite;
	cocos2d::Label* infoLabel;
	cocos2d::Label* scoreLabel;
	cocos2d::Label* livesLabel;
	cocos2d::Label* boxMissedLabel;
	cocos2d::MenuItemFont* menuBtn;
	cocos2d::MenuItemFont* pauseBtn;
	std::vector<Sprite*> sprites;


};