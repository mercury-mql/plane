#include "BulletLayer.h"

BulletLayer::BulletLayer(){
	bulletBatchNode=NULL;

	m_pAllBullet = Array::create();
	m_pAllBullet->retain();

}
BulletLayer::~BulletLayer(){}

bool BulletLayer::init(){
	if(!Layer::init()){
		return false;
	}
	//
	auto texture = TextureCache::getInstance()->textureForKey("shoot.png");
	bulletBatchNode = SpriteBatchNode::createWithTexture(texture);

	this->addChild(bulletBatchNode);

	return true;
}

void BulletLayer::StartShoot(float delay/* =0.0f */){
	this->schedule(schedule_selector(BulletLayer::AddBullet),0.2f,kRepeatForever,delay);
}
void BulletLayer::AddBullet(float dt){
	//mp3
	SimpleAudioEngine::getInstance()->playEffect("bullet.wav");
	
	//bullet
	auto bullet=Sprite::createWithSpriteFrameName("bullet1.png");

	bulletBatchNode->addChild(bullet);	
	this->m_pAllBullet->addObject(bullet);
	
	//bullet position
	Point planePosition=PlaneLayer::sharedPlane->getChildByTag(Tag_Air_Plane)->getPosition();
	Point bulletPosition=Point(planePosition.x, planePosition.y + PlaneLayer::sharedPlane->getChildByTag(Tag_Air_Plane)->getContentSize().height/2);
	bullet->setPosition(bulletPosition);

	float length=Director::getInstance()->getWinSize().height + bullet->getContentSize().height / 2 - bulletPosition.y;
	float velocity=500/1;//320pixel/sec
	float realMoveDuration=length/velocity;

	FiniteTimeAction* actionMove=MoveTo::create(realMoveDuration,Point(bulletPosition.x, Director::getInstance()->getWinSize().height + bullet->getContentSize().height/2));
	FiniteTimeAction* actionDone=CCCallFuncN::create(this,callfuncN_selector(BulletLayer::bulletMoveFinished));

	CCSequence* sequence=CCSequence::create(actionMove,actionDone,NULL);
	bullet->runAction(sequence);
}

void BulletLayer::bulletMoveFinished(Node* pSender){
	Sprite* bullet = (Sprite*)pSender;
	this->bulletBatchNode->removeChild(bullet,true);
	this->m_pAllBullet->removeObject(bullet);
}

void BulletLayer::RemoveBullet(Sprite* bullet){
	if(bullet != NULL){
		this->bulletBatchNode->removeChild(bullet,true);
		this->m_pAllBullet->removeObject(bullet);
	}
}

void BulletLayer::StopShoot()
{
	this->unschedule(schedule_selector(BulletLayer::AddBullet));
}

