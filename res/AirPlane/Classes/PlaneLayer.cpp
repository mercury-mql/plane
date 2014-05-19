#include "PlaneLayer.h"
#include "GameOverScene.h"

PlaneLayer::PlaneLayer(){
	isAlive = true;
	score = 0;
}

PlaneLayer::~PlaneLayer(){}

PlaneLayer* PlaneLayer::sharedPlane = nullptr;

PlaneLayer* PlaneLayer::create() 
{ 
	PlaneLayer *pRet = new PlaneLayer();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		sharedPlane=pRet;
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}
bool PlaneLayer::init(){
	if(!Layer::init()){
		return false;
	}
	
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//plane and it's animation
	auto plane = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("hero1.png"));
	plane->setPosition(Point(visibleSize.width/2,100));
	this->addChild(plane,0,Tag_Air_Plane);
	
	auto blink = Blink::create(1.0f,3);

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("hero1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("hero2.png"));
	auto animate = Animate::create(animation);
	
	auto sequence = Sequence::create(blink,RepeatForever::create(animate),NULL);

	plane->runAction(sequence);

	return true;

}

void PlaneLayer::moveTo(Point pos){
	if(isAlive && !Director::getInstance()->isPaused()){
		Point actualPos;
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Size planeSize=this->getChildByTag(Tag_Air_Plane)->getContentSize();

		if (pos.x < planeSize.width/2)
		{
			pos. x =planeSize.width/2; // left
		}
		if (pos.x > visibleSize.width - planeSize.width/2)
		{
			pos.x = visibleSize.width - planeSize.width / 2; //right
		}
		if (pos.y < planeSize.height/2)
		{
			pos.y = planeSize.width/2 + 10;	//down
		}
		if (pos.y > visibleSize.height - planeSize.height/2)
		{
			pos.y = visibleSize.height - planeSize.height/2;  //up
		}
		this->getChildByTag(Tag_Air_Plane)->setPosition(pos);
	}
}

void PlaneLayer::blowup(int passScore){
	if(isAlive){
		isAlive = false;
		score = passScore;
		
		auto animation = Animation::create();
		animation->setDelayPerUnit(0.2f);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("hero_blowup_n1.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("hero_blowup_n2.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("hero_blowup_n3.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("hero_blowup_n4.png"));

		auto animate = Animate::create(animation);
		CallFunc* animateDone = CallFunc::create(CC_CALLBACK_0(PlaneLayer::removePlane,this));
		auto sequence = Sequence::create(animate,animateDone,NULL);

		this->getChildByTag(Tag_Air_Plane)->stopAllActions();
		this->getChildByTag(Tag_Air_Plane)->runAction(sequence);

		//

	}
}

void PlaneLayer::removePlane(){
	this->removeChildByTag(Tag_Air_Plane);
	auto scene = GameOverScene::create(score);
	auto animationScene = TransitionFade::create(0.5f,scene);
	Director::getInstance()->replaceScene(animationScene);

}