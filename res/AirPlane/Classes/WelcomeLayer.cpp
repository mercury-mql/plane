#include "WelcomeLayer.h"
#include "GameScene.h"

WelcomeLayer::WelcomeLayer(){

}

WelcomeLayer::~WelcomeLayer(){

}

bool WelcomeLayer::init(){
	if(!Layer::init()){
		return false;
	}

	//»º³å³Ø
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot_background.plist","shoot_background.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot.plist","shoot.png");

	Point origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//background
	Sprite* backGround = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("background.png"));
	backGround->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
	this->addChild(backGround);

	//copyright
	Sprite* copyright=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("shoot_copyright.png"));
	copyright->setAnchorPoint(ccp(0.5,0));
	copyright->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	this->addChild(copyright);

	//plane1
	Sprite* loading=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("game_loading1.png"));
	loading->setPosition(ccp(visibleSize.width/2,visibleSize.height/2-40));
	this->addChild(loading);

	//animation
	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.3f);
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("game_loading1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("game_loading2.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("game_loading3.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("game_loading4.png"));

	Animate* animate = Animate::create(animation);
	RepeatForever* repeat = RepeatForever::create(animate);

	loading->runAction(repeat);

	//onTouch gameStart
	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
	EventListenerTouchAllAtOnce* listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(WelcomeLayer::onTouchesBegan,this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	return true;
}

void WelcomeLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event){

}



void WelcomeLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event){
	
	auto scene = GameScene::create();
	auto animationScene = TransitionFade::create(0.5f,scene);
	Director::getInstance()->replaceScene(animationScene);
}

bool WelcomeLayer::isHaveSaveFile(){
	bool bRet = UserDefault::getInstance()->getBoolForKey("isHaveSaveFileXml");
	//
	if(!bRet){
		UserDefault::getInstance()->setBoolForKey("isHaveSaveFileXml",true);
		UserDefault::getInstance()->setIntegerForKey("HighestScore",0);
		UserDefault::getInstance()->flush();

		return false;
	}
	else{
		return true;
	}
}

void WelcomeLayer::getHighestHistorySorce(){

}