#include "GameOverLayer.h"
#include "GameScene.h"

GameOverLayer::GameOverLayer(){
	score = 0;
	highestScore = NULL;
}

int GameOverLayer::highestHistoryScore  =0;

GameOverLayer::~GameOverLayer(){}

GameOverLayer* GameOverLayer::create(int passScore){
	
	GameOverLayer* pRet = new GameOverLayer();
	pRet->score = passScore;
	if(pRet && pRet->init()){
		pRet->autorelease();
		return pRet;
	}else{
		pRet->release();
		pRet = NULL;
		return NULL;
	}
}

bool GameOverLayer::init(){
	if(!Layer::init()){
		return false;
	}

	if(SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()){
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	SimpleAudioEngine::getInstance()->playEffect("game_over.mp3");

	Size winSize = Director::getInstance()->getWinSize();

	auto background = Sprite::createWithSpriteFrameName("gameover.png");
	background->setPosition(Point(winSize.width/2, winSize.height/2));
	this->addChild(background);

	//back to game menu
	auto normalBackToGame = Sprite::createWithSpriteFrameName("btn_finish.png");
	auto pressBackToGame = Sprite::createWithSpriteFrameName("btn_finish.png");
	auto menuitem = MenuItemSprite::create(normalBackToGame,pressBackToGame,NULL,CC_CALLBACK_1(GameOverLayer::menuBackCallback,this));
	menuitem->setPosition(Point(winSize.width - normalBackToGame->getContentSize().width/2, normalBackToGame->getContentSize().height/2));
	auto menu = Menu::create(menuitem,NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	//final score
	String* strScore = String::createWithFormat("%d",score);
	LabelBMFont* finalScore = LabelBMFont::create(strScore->getCString(),"font/font.fnt");
	finalScore->setColor(ccc3(143,146,147));
	finalScore->setPosition(Point(winSize.width/2,winSize.height/2));
	this->addChild(finalScore);

	DelayTime* delay = DelayTime::create(1.0f);
	ScaleTo* scaleBig = ScaleTo::create(1.0f,3.0f);
	ScaleTo* scaleSmall = ScaleTo::create(0.3f,2.0f);
	CallFunc* showAD = CallFunc::create(CC_CALLBACK_0(GameOverLayer::showAD,this));//ad
	Sequence* sequence = Sequence::create(delay,scaleBig,scaleSmall,showAD,NULL);

	finalScore->runAction(sequence);

	//highest score
	String* strHighestScore=String::createWithFormat("%d",highestHistoryScore);
	highestScore=LabelBMFont::create(strHighestScore->getCString(),"font/font.fnt");
	highestScore->setColor(Color3B(143,146,147));
	highestScore->setAnchorPoint(Point(0,0.5));
	highestScore->setPosition(Point(140,winSize.height-50));
	this->addChild(highestScore);


	if(score > highestHistoryScore){
		UserDefault::getInstance()->setIntegerForKey("HighestScore",score);
		highestHistoryScore = score;
		auto delayChange = DelayTime::create(1.3f);
		auto moveOut = MoveBy::create(0.1f,Point(0,100));
		auto beginChange = CallFuncN::create(CC_CALLBACK_1(GameOverLayer::beginChangeHighestScore,this));
		auto moveIn = MoveBy::create(0.1f,Point(0,-100));
		auto seq = Sequence::create(delayChange,moveOut,beginChange,moveIn,NULL);
		highestScore->runAction(seq);
	}

	this->setKeypadEnabled(true);

	return true;
}

void GameOverLayer::menuBackCallback(CCObject* pSender){
	auto scene = GameScene::create();
	auto animationScene = TransitionFade::create(0.5f,scene);
	Director::getInstance()->replaceScene(animationScene);

}

void GameOverLayer::beginChangeHighestScore(Node* pNode){
	SimpleAudioEngine::getInstance()->playEffect("achievement.mp3");
	String* changeScore = String::createWithFormat("%d",score);
	highestScore->setString(changeScore->getCString());
}

void GameOverLayer::showAD(){

}