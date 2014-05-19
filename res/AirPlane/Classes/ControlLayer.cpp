#include "ControlLayer.h"

ControlLayer::ControlLayer(){

}
ControlLayer::~ControlLayer(){

}
bool ControlLayer::init(){
	if(!Layer::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	//add pause menu
	pauseNormal = Sprite::createWithSpriteFrameName("game_pause_nor.png");
	pausePressed = Sprite::createWithSpriteFrameName("game_pause_pressed.png");
	
	pPauseItem = MenuItemSprite::create(pauseNormal,pausePressed,NULL,CC_CALLBACK_1(ControlLayer::menuPauseCallback,this));
	pPauseItem->setPosition(Point(pauseNormal->getContentSize().width/2 + 10, visibleSize.height - pauseNormal->getContentSize().height/2 - 10));
	auto menuPause = Menu::create(pPauseItem,NULL);
	menuPause->setPosition(Point::ZERO);
	this->addChild(menuPause,101);

	scoreItem = LabelBMFont::create("0","font.fnt");
	scoreItem->setColor(Color3B(143,146,147));
	scoreItem->setAnchorPoint(Point(0,0.5));
	scoreItem->setPosition(Point(pPauseItem->getPositionX()+pauseNormal->getContentSize().width/2+5,pPauseItem->getPositionY()));
	this->addChild(scoreItem);

	return true;
}

void ControlLayer::menuPauseCallback(Object* pSender){
	SimpleAudioEngine::getInstance()->playEffect("button.mp3");

	if(!Director::getInstance()->isPaused()){//pause
		pPauseItem->setNormalImage(Sprite::createWithSpriteFrameName("game_resume_nor.png"));
		pPauseItem->setSelectedImage(Sprite::createWithSpriteFrameName("game_resume_pressed.png"));
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		SimpleAudioEngine::getInstance()->stopAllEffects();
		Director::getInstance()->pause();
		//no Touch
		//noTouchLayer = NoTouchLayer::create();
		//this->addChild(noTouchLayer);
	}else{						//resume
		pPauseItem->setNormalImage(Sprite::createWithSpriteFrameName("game_pause_nor.png"));
		pPauseItem->setSelectedImage(Sprite::createWithSpriteFrameName("game_pause_pressed.png"));
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		SimpleAudioEngine::getInstance()->resumeAllEffects();
		Director::getInstance()->resume();
		//resume touch
		//this->removeChild(noTouchLayer,true);

	}
}

void ControlLayer::updateScore(int score){
	if(score >= 0 && score <= MAX_SCORE){
		scoreItem->setString(String::createWithFormat("%d",score)->getCString());
	}
}