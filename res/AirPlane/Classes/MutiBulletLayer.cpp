#include "MutiBulletLayer.h"

MutiBulletLayer::MutiBulletLayer(){
	mutiBulletBacthNode = NULL;
	pAllMutiBulletArr = Array::create();
	pAllMutiBulletArr->retain();
}

MutiBulletLayer::~MutiBulletLayer(){
		
}

bool MutiBulletLayer::init(){
	if(!Layer::init()){
		return false;
	}
	auto texture = TextureCache::getInstance()->textureForKey("shoot.png");
	mutiBulletBacthNode = SpriteBatchNode::createWithTexture(texture);
	this->addChild(mutiBulletBacthNode);

	return true;
}


void MutiBulletLayer::startShoot(float delay){
	this->schedule(schedule_selector(MutiBulletLayer::addMutiBullet),0.2f,30,delay);
}

void MutiBulletLayer::addMutiBullet(float dt){
	//play the music effect
	SimpleAudioEngine::getInstance()->playEffect("bullet.wav");

	//mutiBullet and it's action
	//bullet
	auto bulletLeft = Sprite::createWithSpriteFrameName("bullet2.png");
	auto bulletRight = Sprite::createWithSpriteFrameName("bullet2.png");

	mutiBulletBacthNode->addChild(bulletLeft);	
	this->pAllMutiBulletArr->addObject(bulletLeft);
	mutiBulletBacthNode->addChild(bulletRight);	
	this->pAllMutiBulletArr->addObject(bulletRight);

	//bullet position
	Point planePosition=PlaneLayer::sharedPlane->getChildByTag(Tag_Air_Plane)->getPosition();
	Point bulletLeftPosition=Point(planePosition.x-18, planePosition.y + PlaneLayer::sharedPlane->getChildByTag(Tag_Air_Plane)->getContentSize().height/2);
	Point bulletRightPosition=Point(planePosition.x+18, planePosition.y + PlaneLayer::sharedPlane->getChildByTag(Tag_Air_Plane)->getContentSize().height/2);
	bulletLeft->setPosition(bulletLeftPosition);
	bulletRight->setPosition(bulletRightPosition);

	float length=Director::getInstance()->getWinSize().height + bulletLeft->getContentSize().height / 2 - bulletLeftPosition.y;
	float velocity=500/1;//320pixel/sec
	float realMoveDuration=length/velocity;

	FiniteTimeAction* L_actionMove=MoveTo::create(realMoveDuration,Point(bulletLeftPosition.x, Director::getInstance()->getWinSize().height + bulletLeft->getContentSize().height/2));
	FiniteTimeAction* L_actionDone=CallFuncN::create(CC_CALLBACK_1(MutiBulletLayer::mutiBulletMoveFinish,this));
	CCSequence* L_sequence=CCSequence::create(L_actionMove,L_actionDone,NULL);

	FiniteTimeAction* R_actionMove=MoveTo::create(realMoveDuration,Point(bulletRightPosition.x, Director::getInstance()->getWinSize().height + bulletRight->getContentSize().height/2));
	FiniteTimeAction* R_actionDone=CallFuncN::create(CC_CALLBACK_1(MutiBulletLayer::mutiBulletMoveFinish,this));
	CCSequence* R_sequence=CCSequence::create(R_actionMove,R_actionDone,NULL);
	
	bulletLeft->runAction(L_sequence);
	bulletRight->runAction(R_sequence);


}

void MutiBulletLayer::mutiBulletMoveFinish(Object* pSender){
	//action 's Ö´ÐÐÕß
	auto bullet = (Sprite*) pSender; 
	this->mutiBulletBacthNode->removeChild(bullet,true);
	this->pAllMutiBulletArr->removeObject(bullet);
}

void MutiBulletLayer::mutiBulletRemove(Sprite* bullet){
	if(bullet == NULL){
		return;
	}
	this->mutiBulletBacthNode->removeChild(bullet,true);
	this->pAllMutiBulletArr->removeObject(bullet);
}

void MutiBulletLayer::stopShoot(){
	this->unschedule(schedule_selector(MutiBulletLayer::addMutiBullet));
}