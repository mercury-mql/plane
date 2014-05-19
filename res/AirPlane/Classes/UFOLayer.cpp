#include "UFOLayer.h"


UFOLayer::UFOLayer(){
	m_pAllMutiBullets = Array::create();
	m_pAllMutiBullets->retain();
	m_pAllBigBoom = Array::create();
	m_pAllBigBoom->retain();
}
UFOLayer::~UFOLayer(){
	m_pAllMutiBullets->release();
	m_pAllMutiBullets = NULL;
	m_pAllBigBoom->release();
	m_pAllBigBoom = NULL;
}

bool UFOLayer::init(){
	if(!Layer::init()){
		return false;
	}
	//add muti
	this->schedule(schedule_selector(UFOLayer::AddMutiBullets),30.0f);
	//add big boom
	this->schedule(schedule_selector(UFOLayer::AddBigBoom),30.0f,kRepeatForever,5.0f);

	return true;
}

void UFOLayer::AddMutiBullets(float dt){

	SimpleAudioEngine::getInstance()->playEffect("out_porp.wav");
	Sprite* mutiBullet = Sprite::createWithSpriteFrameName("ufo1.png");

	Size mutiBulletSize = mutiBullet->getContentSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	int minX = mutiBulletSize.width / 2;
	int maxX = visibleSize.width - mutiBulletSize.width/2;
	int randomX = (rand() % (maxX - minX)) + minX;

	mutiBullet->setPosition(randomX, visibleSize.height + mutiBulletSize.height/2);
	this->addChild(mutiBullet);
	this->m_pAllMutiBullets->addObject(mutiBullet);

	//move action
	auto move1 = MoveBy::create(0.5f,Point(0,-150));
	auto move2 = MoveBy::create(0.5f,Point(0,100));
	auto move3 = MoveBy::create(1.0f,Point(0,-visibleSize.height - mutiBulletSize.height/2));
	auto moveDone = CallFuncN::create(CC_CALLBACK_1(UFOLayer::mutiBulletsMoveFinished,this));

	auto sequence = Sequence::create(move1,move2,move3,moveDone,NULL);
	mutiBullet->runAction(sequence);
}
void UFOLayer::mutiBulletsMoveFinished(CCNode* pSender){
	Sprite* mutiBullet = (Sprite*)pSender;
	this->removeChild(mutiBullet,true);
	this->m_pAllMutiBullets->removeObject(mutiBullet);
}

void UFOLayer::AddBigBoom(float dt){
	SimpleAudioEngine::getInstance()->playEffect("out_porp.wav");
	Sprite* bigBoom = Sprite::createWithSpriteFrameName("ufo2.png");

	Size mutiBulletSize = bigBoom->getContentSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	int minX = mutiBulletSize.width / 2;
	int maxX = visibleSize.width - mutiBulletSize.width/2;
	int randomX = (rand() % (maxX - minX)) + minX;

	bigBoom->setPosition(randomX, visibleSize.height + mutiBulletSize.height/2);
	this->addChild(bigBoom);
	this->m_pAllBigBoom->addObject(bigBoom);

	//move action
	auto move1 = MoveBy::create(0.5f,Point(0,-150));
	auto move2 = MoveBy::create(0.5f,Point(0,100));
	auto move3 = MoveBy::create(1.0f,Point(0,-visibleSize.height - mutiBulletSize.height/2));
	auto moveDone = CallFuncN::create(CC_CALLBACK_1(UFOLayer::bigBoomMoveFinished,this));

	auto sequence = Sequence::create(move1,move2,move3,moveDone,NULL);
	bigBoom->runAction(sequence);
}

void UFOLayer::bigBoomMoveFinished(CCNode* pSender){
	Sprite* sprite = (Sprite*)pSender;
	this->removeChild(sprite,true);
	this->m_pAllBigBoom->removeObject(sprite);
}

void UFOLayer::RemoveBigBoom(CCSprite* bigBoom){
	this->removeChild(bigBoom,true);
	this->m_pAllBigBoom->removeObject(bigBoom);
}

void UFOLayer::RemoveMutiBullets(CCSprite* mutiBullets){
	this->removeChild(mutiBullets,true);
	this->m_pAllMutiBullets->removeObject(mutiBullets);
}