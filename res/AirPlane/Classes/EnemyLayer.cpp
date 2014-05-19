#include "EnemyLayer.h"
#include "GameLayer.h"

EnemyLayer::EnemyLayer(){

	enemy1SpriteFrame=NULL;
	enemy2SpriteFrame=NULL;
	enemy3SpriteFrame_1=NULL;
	enemy3SpriteFrame_2=NULL;

	m_pAllEnemy1 = Array::create();
	m_pAllEnemy1->retain();
	m_pAllEnemy2 = Array::create();
	m_pAllEnemy2->retain();
	m_pAllEnemy3 = Array::create();
	m_pAllEnemy3->retain();

}

EnemyLayer::~EnemyLayer(){
	m_pAllEnemy1->release();
	m_pAllEnemy2->release();
	m_pAllEnemy3->release();

	m_pAllEnemy1 = NULL;
	m_pAllEnemy2 = NULL;
	m_pAllEnemy3 = NULL;
}

bool EnemyLayer::init(){
	if(!Layer::init()){
		return false;
	}
	enemy1SpriteFrame = SpriteFrameCache::getInstance()->spriteFrameByName("enemy1.png");
	enemy2SpriteFrame = SpriteFrameCache::getInstance()->spriteFrameByName("enemy2.png");
	enemy3SpriteFrame_1 = SpriteFrameCache::getInstance()->spriteFrameByName("enemy3_n1.png");
	enemy3SpriteFrame_2 = SpriteFrameCache::getInstance()->spriteFrameByName("enemy3_n2.png");

	auto animation1 = Animation::create();
	animation1->setDelayPerUnit(0.1f);
	animation1->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("enemy1_down1.png"));
	animation1->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("enemy1_down2.png"));
	animation1->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("enemy1_down3.png"));
	animation1->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("enemy1_down4.png"));

	auto animation2 = Animation::create();
	animation2->setDelayPerUnit(0.1f);
	animation2->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("enemy2_down1.png"));
	animation2->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("enemy2_down2.png"));
	animation2->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("enemy2_down3.png"));
	animation2->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("enemy2_down4.png"));

	auto animation3 = Animation::create();
	animation3->setDelayPerUnit(0.1f);
	animation3->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("enemy3_down1.png"));
	animation3->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("enemy3_down2.png"));
	animation3->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("enemy3_down3.png"));
	animation3->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("enemy3_down4.png"));
	animation3->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("enemy3_down5.png"));
	animation3->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("enemy3_down6.png"));

	AnimationCache::getInstance()->addAnimation(animation1,"Enemy1Blowup");
	AnimationCache::getInstance()->addAnimation(animation2,"Enemy2Blowup");
	AnimationCache::getInstance()->addAnimation(animation3,"Enemy3Blowup");

	this->schedule(schedule_selector(EnemyLayer::addEnemy1),1.5f);
	this->schedule(schedule_selector(EnemyLayer::addEnemy2),3.0f);
	this->schedule(schedule_selector(EnemyLayer::addEnemy3),6.0f);

	return true;
}

void EnemyLayer::addEnemy1(float dt){
	//postion
	Enemy* enemy1 = Enemy::create();
	enemy1->bindSprite(Sprite::createWithSpriteFrame(enemy1SpriteFrame),Enemy1_MaxLife);

	Size enemy1Size = enemy1->getSprite()->getContentSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	//random x
	int minX = enemy1Size.width / 2;
	int maxX = visibleSize.width - enemy1Size.width / 2;
	int randdomX = (rand() % (maxX - minX)) + minX;

	enemy1->setPosition(Point(randdomX, visibleSize.height + enemy1Size.height / 2));
	this->addChild(enemy1);
	this->m_pAllEnemy1->addObject(enemy1);

	float minDuration, maxDuration;
	switch (GameLayer::getCurLevel())
	{
	case EASY:
		minDuration=3.0;
		maxDuration=6.0;
		break;
	case MIDDLE:
		minDuration=1.8;
		maxDuration=3.6;
		break;
	case HARD:
		minDuration=1.6;
		maxDuration=3.2;
		break;
	default:
		minDuration=2.0;
		maxDuration=4.0;
		break;
	}
	int rangeDuration = maxDuration - minDuration;
	int randomDuration = (rand() % rangeDuration) + minDuration;

	FiniteTimeAction* actionMove = MoveTo::create(randomDuration, Point(randdomX, -enemy1->getSprite()->getContentSize().height / 2));
	FiniteTimeAction* actionDone = CallFuncN::create(std::bind(&EnemyLayer::enemy1MoveFinished,this,enemy1));
//	FiniteTimeAction* actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemy1MoveFinished,this));
	auto sequence = Sequence::create(actionMove,actionDone,NULL);

	enemy1->runAction(sequence);
}

void EnemyLayer::enemy1MoveFinished(Node* pSender){
 	Enemy* enemy1 = (Enemy*)pSender;
	this->removeChild(enemy1, true);
	this->m_pAllEnemy1->removeObject(enemy1);
	
}

void EnemyLayer::enemy1Blowup(Enemy* enemy1){
	SimpleAudioEngine::getInstance()->playEffect("enemy1_down.mp3");
	auto animation = AnimationCache::getInstance()->animationByName("Enemy1Blowup");
	auto animate = Animate::create(animation);
	CallFuncN* animateDone = CallFuncN::create(std::bind(&EnemyLayer::removeEnemy1,this,enemy1));
	auto sequence = Sequence::create(animate, animateDone,NULL);
	enemy1->die();
	enemy1->getSprite()->runAction(sequence);
}

void EnemyLayer::removeEnemy1(Object* data){
	Enemy* enemy1 = (Enemy*)data;
	if(enemy1 != NULL){
		m_pAllEnemy1->removeObject(enemy1);
		this->removeChild(enemy1,true);
	}
}

void EnemyLayer::removeAllEnemy1()
{
	CCObject* obj;
	CCARRAY_FOREACH(m_pAllEnemy1,obj)
	{
		Enemy* enemy1=(Enemy*)obj;
		if (enemy1->getLife()>0)
		{
			enemy1Blowup(enemy1);
		}
	}
}

void EnemyLayer::addEnemy2(float dt){
	//postion
	Enemy* enemy2 = Enemy::create();
	enemy2->bindSprite(Sprite::createWithSpriteFrame(enemy2SpriteFrame),Enemy2_MaxLife);

	Size enemy1Size = enemy2->getSprite()->getContentSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//random x
	int minX = enemy1Size.width / 2;
	int maxX = visibleSize.width - enemy1Size.width / 2;
	int randdomX = (rand() % (maxX - minX)) + minX;

	enemy2->setPosition(Point(randdomX, visibleSize.height + enemy1Size.height / 2));
	this->addChild(enemy2);
	this->m_pAllEnemy2->addObject(enemy2);

	float minDuration, maxDuration;
	switch (GameLayer::getCurLevel())
	{
	case EASY:
		minDuration=3.0;
		maxDuration=6.0;
		break;
	case MIDDLE:
		minDuration=2.7;
		maxDuration=5.4;
		break;
	case HARD:
		minDuration=2.5;
		maxDuration=5.0;
		break;
	default:
		minDuration=3.0;
		maxDuration=6.0;
		break;
	}
	int rangeDuration = maxDuration - minDuration;
	int randomDuration = (rand() % rangeDuration) + minDuration;

	FiniteTimeAction* actionMove = MoveTo::create(randomDuration, Point(randdomX, -enemy2->getSprite()->getContentSize().height / 2));
	FiniteTimeAction* actionDone = CallFuncN::create(std::bind(&EnemyLayer::enemy2MoveFinished,this,enemy2));
	auto sequence = Sequence::createWithTwoActions(actionMove,actionDone);

	enemy2->runAction(sequence);
}

void EnemyLayer::enemy2MoveFinished(Node* pSender){
	Enemy* enemy = (Enemy*)pSender;
	this->removeChild(enemy, true);
	this->m_pAllEnemy2->removeObject(enemy);

}

void EnemyLayer::enemy2Blowup(Enemy* enemy){
	SimpleAudioEngine::getInstance()->playEffect("enemy2_down.mp3");
	auto animation = AnimationCache::getInstance()->animationByName("Enemy2Blowup");
	auto animate = Animate::create(animation);
	CallFuncN* animateDone = CallFuncN::create(std::bind(&EnemyLayer::removeEnemy2,this,enemy));
	auto sequence = Sequence::create(animate, animateDone,NULL);
	enemy->die();
	enemy->getSprite()->runAction(sequence);
}

void EnemyLayer::removeEnemy2(Node* pSender){
	Enemy* enemy = (Enemy*)pSender;
	if(enemy != NULL){
		m_pAllEnemy2->removeObject(enemy);
		this->removeChild(enemy,true);
	}
}

void EnemyLayer::removeAllEnemy2()
{
	CCObject* obj;
	CCARRAY_FOREACH(m_pAllEnemy2,obj)
	{
		Enemy* enemy2=(Enemy*)obj;
		if (enemy2->getLife()>0)
		{
			enemy2Blowup(enemy2);
		}
	}
}

void EnemyLayer::addEnemy3(float dt){
	//postion
	Enemy* enemy3 = Enemy::create();
	enemy3->bindSprite(Sprite::createWithSpriteFrame(enemy3SpriteFrame_1),Enemy3_MaxLife);

	Size enemy1Size = enemy3->getSprite()->getContentSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//random x
	int minX = enemy1Size.width / 2;
	int maxX = visibleSize.width - enemy1Size.width / 2;
	int randdomX = (rand() % (maxX - minX)) + minX;

	enemy3->setPosition(Point(randdomX, visibleSize.height + enemy1Size.height / 2));
	this->addChild(enemy3);
	this->m_pAllEnemy3->addObject(enemy3);

	float minDuration, maxDuration;
	switch (GameLayer::getCurLevel())
	{
	case EASY:
		minDuration=4.0;
		maxDuration=8.0;
		break;
	case MIDDLE:
		minDuration=3.6;
		maxDuration=7.2;
		break;
	case HARD:
		minDuration=3.2;
		maxDuration=6.4;
		break;
	default:
		minDuration=4.0;
		maxDuration=8.0;
		break;
	}
	int rangeDuration = maxDuration - minDuration;
	int randomDuration = (rand() % rangeDuration) + minDuration;

	FiniteTimeAction* actionMove = MoveTo::create(randomDuration, Point(randdomX, -enemy3->getSprite()->getContentSize().height / 2));
	FiniteTimeAction* actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemy3MoveFinished,this));
	auto sequence = Sequence::createWithTwoActions(actionMove,actionDone);

	enemy3->runAction(sequence);
}
void EnemyLayer::enemy3MoveFinished(Node* pSender){
	Enemy* enemy = (Enemy*)pSender;
	this->removeChild(enemy, true);
	this->m_pAllEnemy3->removeObject(enemy);

}

void EnemyLayer::enemy3Blowup(Enemy* enemy){
	SimpleAudioEngine::getInstance()->playEffect("enemy3_down.mp3");
	auto animation = AnimationCache::getInstance()->animationByName("Enemy3Blowup");
	auto animate = Animate::create(animation);
	CallFuncN* animateDone = CallFuncN::create(std::bind(&EnemyLayer::removeEnemy3,this,enemy));
	auto sequence = Sequence::create(animate, animateDone,NULL);
	enemy->die();
	enemy->getSprite()->runAction(sequence);
}

void EnemyLayer::removeEnemy3(Node* pSender){
	Enemy* enemy = (Enemy*)pSender;
	if(enemy != NULL){
		m_pAllEnemy3->removeObject(enemy);
		this->removeChild(enemy,true);
	}
}
void EnemyLayer::removeAllEnemy3()
{
	CCObject* obj;
	CCARRAY_FOREACH(m_pAllEnemy3,obj)
	{
		Enemy* enemy3=(Enemy*)obj;
		if (enemy3->getLife()>0)
		{
			enemy3Blowup(enemy3);
		}
	}
}

void EnemyLayer::removeAllEnemy(){
	removeAllEnemy1();
	removeAllEnemy2();
	removeAllEnemy3();
}