#include "GameLayer.h"

GameLevel GameLayer::level=EASY;

GameLayer::GameLayer(){
	this->mPlaneLayer = NULL;
	this->mBulletLayer = NULL;
	this->mMutiBulletLayer = NULL;
	this->mUFOLayer = NULL;
	
	score = 0;
	bigBoomCount = 0;
}

GameLayer::~GameLayer(){

}


bool GameLayer::init(){
	if(!Layer::init()){
		return true;
	}

	level = EASY;

	//backgroud mp3
	if(!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()){
		SimpleAudioEngine::getInstance()->playBackgroundMusic("game_music.mp3");
	}
	this->scheduleUpdate();

	//background1
	backGround1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("background.png"));
	backGround1->setAnchorPoint(Point(0,0));
	backGround1->setPosition(Point::ZERO);
	this->addChild(backGround1,0);

	//background2
	backGround2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("background.png"));
	backGround2->setAnchorPoint(Point(0,0));
	backGround2->setPosition(Point(0,backGround2->getContentSize().height -2.0f ));
	this->addChild(backGround2,0);

	//move the ground
	this->schedule(schedule_selector(GameLayer::backgroundMove),0.01f);

	//plane
	this->mPlaneLayer = PlaneLayer::create();
	this->addChild(mPlaneLayer);

	//bullet
	mBulletLayer = BulletLayer::create();
	this->addChild(mBulletLayer);
	mBulletLayer->StartShoot(1.0f);

	//mutiBulletLayer
	mMutiBulletLayer = MutiBulletLayer::create();
	this->addChild(mMutiBulletLayer);
//	mMutiBulletLayer->startShoot(1.0f);

	//EnemyLayer
	mEnemyLayer = EnemyLayer::create();
	this->addChild(mEnemyLayer);

	//controlLayer
	mControlLayer = ControlLayer::create();
	this->addChild(mControlLayer);

	//ufolayer
	mUFOLayer = UFOLayer::create();
	this->addChild(mUFOLayer);

	//touch
	registerTouch();

	return true;
}

void GameLayer::registerTouch(){
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded,this);
	listener->setSwallowTouches(true);
	
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	
	
	this->setTouchEnabled(true);
}

bool GameLayer::onTouchBegan(Touch *touch, Event *unused_event){
	return true;
}

void GameLayer::onTouchMoved(Touch *touch, Event *unused_event){
	if(this->mPlaneLayer->isAlive){
		//屏幕坐标，左上角 （0,0)
		Point beginPos = touch->getLocationInView();
		//转化为openGL坐标系
		beginPos = Director::getInstance()->convertToGL(beginPos);
		Rect planeRect = mPlaneLayer->getChildByTag(Tag_Air_Plane)->boundingBox();
		planeRect.origin.x -= 150;
		planeRect.origin.y -= 150;
		planeRect.size.width += 300;
		planeRect.size.height += 300;
		if(planeRect.containsPoint(this->getParent()->convertTouchToNodeSpace(touch))){
			Point endPos = touch->getPreviousLocationInView();
			endPos = Director::getInstance()->convertToGL(endPos);
			
			Point offset = ccpSub(beginPos,endPos);
			Point toPoint = ccpAdd(this->mPlaneLayer->getChildByTag(Tag_Air_Plane)->getPosition(),offset);

			this->mPlaneLayer->moveTo(toPoint);



		}
	}
}

void GameLayer::onTouchEnded(Touch *touch, Event *unused_event){

}


void GameLayer::backgroundMove(float dt){
	//to make plane look like move up, so make the background move down
	backGround1->setPositionY(backGround1->getPositionY()-2.0f);
	backGround2->setPositionY(backGround1->getPositionY() + backGround1->getContentSize().height - 2.0f);
	if (backGround2->getPositionY() <= 0)
	{
		backGround1->setPositionY(0);
	}
}

GameLevel GameLayer::getCurLevel(){
	return level;
}


void GameLayer::update(float dt){
	if(level == EASY &&  score >= 100000){
		level = MIDDLE;
	}else if(level == MIDDLE && score >= 500000){
		level = HARD;
	}

	Array* bulletsToDelete = Array::create();
	bulletsToDelete->retain();
	Object* bt,*ut,*et;

	//bullet and enemy1
	CCARRAY_FOREACH(this->mBulletLayer->m_pAllBullet, bt){
		Sprite* bullet = (Sprite*)bt;
		
		Array* enemy1ToDelete = Array::create();
		enemy1ToDelete->retain();
		int a = this->mEnemyLayer->m_pAllEnemy1->capacity();
		//enemy1
		CCARRAY_FOREACH(this->mEnemyLayer->m_pAllEnemy1,et){
			Enemy* enemy1 = (Enemy*)et;
			if(bullet->boundingBox().intersectsRect(enemy1->getBoundingBox())){
				if(enemy1->getLife() == 1){
					enemy1->loseLife();
					bulletsToDelete->addObject(bullet);
					enemy1ToDelete->addObject(enemy1);
					score += ENEMY1_SCORE;
					this->mControlLayer->updateScore(score);
				}
			}
		}
		//enemy1 delete
		CCARRAY_FOREACH(enemy1ToDelete,et){
			Enemy* enemy1 = (Enemy*)et;
			this->mEnemyLayer->enemy1Blowup(enemy1);
		}
		enemy1ToDelete->release();
	}
	CCARRAY_FOREACH(bulletsToDelete,bt)
	{
		Sprite* bullet=(Sprite*)bt;
		this->mBulletLayer->RemoveBullet(bullet);
	}
	bulletsToDelete->removeAllObjects();


	//enemy2 & bullet 
	CCARRAY_FOREACH(this->mBulletLayer->m_pAllBullet,bt)
	{
		Sprite* bullet=(Sprite*)bt;

		Array* enemy2sToDelete=Array::create();
		enemy2sToDelete->retain();
		CCARRAY_FOREACH(this->mEnemyLayer->m_pAllEnemy2,et)
		{
			Enemy* enemy2=(Enemy*)et;
			if (bullet->boundingBox().intersectsRect(enemy2->getBoundingBox()))
			{
				if (enemy2->getLife()>1)
				{
					enemy2->loseLife();
					bulletsToDelete->addObject(bullet);
				}
				else if(enemy2->getLife()==1)
				{
					enemy2->loseLife();
					bulletsToDelete->addObject(bullet);
					enemy2sToDelete->addObject(enemy2);
					score+=ENEMY2_SCORE;
					this->mControlLayer->updateScore(score);
				}
				else ;
			}
		}
		CCARRAY_FOREACH(enemy2sToDelete,et)
		{
			Enemy* enemy2=(Enemy*)et;
			this->mEnemyLayer->enemy2Blowup(enemy2);
		}
		enemy2sToDelete->release();
	}
	CCARRAY_FOREACH(bulletsToDelete,bt)
	{
		CCSprite* bullet=(CCSprite*)bt;
		this->mBulletLayer->RemoveBullet(bullet);
	}
	bulletsToDelete->removeAllObjects();

	//enemy3 & bullet 
	CCARRAY_FOREACH(this->mBulletLayer->m_pAllBullet,bt)
	{
		CCSprite* bullet=(CCSprite*)bt;

		CCArray* enemy3sToDelete=CCArray::create();
		enemy3sToDelete->retain();
		CCARRAY_FOREACH(this->mEnemyLayer->m_pAllEnemy3,et)
		{
			Enemy* enemy3=(Enemy*)et;
			if (bullet->boundingBox().intersectsRect(enemy3->getBoundingBox()))
			{
				//如果life>1,移除bullet
				if (enemy3->getLife()>1)
				{
					enemy3->loseLife();
					bulletsToDelete->addObject(bullet);
				}
				//如果life==1,移除enemy3
				else if(enemy3->getLife()==1)
				{
					enemy3->loseLife();
					bulletsToDelete->addObject(bullet);
					enemy3sToDelete->addObject(enemy3);
					score+=ENEMY3_SCORE;
					this->mControlLayer->updateScore(score);
				}
				//此时处在animate阶段,不做处理
				else ;
			}
		}
		CCARRAY_FOREACH(enemy3sToDelete,et)
		{
			Enemy* enemy3=(Enemy*)et;
			this->mEnemyLayer->enemy3Blowup(enemy3);
		}
		enemy3sToDelete->release();
	}
	CCARRAY_FOREACH(bulletsToDelete,bt)
	{
		Sprite* bullet=(Sprite*)bt;
		this->mBulletLayer->RemoveBullet(bullet);
	}
	bulletsToDelete->removeAllObjects();
	bulletsToDelete->release();
	
	//mutiBullet and enemy
	Array* mutiBulletToDelete = Array::create();
	mutiBulletToDelete->retain();
	Object *mbt;
	//enemy1 and muti_bullet
	CCARRAY_FOREACH(this->mMutiBulletLayer->pAllMutiBulletArr,mbt){
		Sprite* mutiBullet = (Sprite*)mbt;
		Array* enemy1ToDelete = Array::create();
		enemy1ToDelete->retain();
		//碰撞
		CCARRAY_FOREACH(this->mEnemyLayer->m_pAllEnemy1,et){
			Enemy* enemy1 = (Enemy*)et;
			if(mutiBullet->boundingBox().intersectsRect(enemy1->getBoundingBox())){
				if(enemy1->getLife() == 1){
					enemy1->loseLife();

					mutiBulletToDelete->addObject(mutiBullet);
					enemy1ToDelete->addObject(enemy1);

					score += ENEMY1_SCORE;
					this->mControlLayer->updateScore(score);
				}
			}
		}
		//blowup
		CCARRAY_FOREACH(enemy1ToDelete,et){
			Enemy* enemy1 = (Enemy*)et;
			this->mEnemyLayer->enemy1Blowup(enemy1);
		}
		enemy1ToDelete->release();
	}
	//移除muti子弹
	CCARRAY_FOREACH(mutiBulletToDelete,mbt){
		Sprite* mutiBullet = (Sprite*)mbt;
		this->mMutiBulletLayer->mutiBulletRemove(mutiBullet);
	}
	mutiBulletToDelete->removeAllObjects();
	

	//enemy2 and muti_bullet
	CCARRAY_FOREACH(this->mMutiBulletLayer->pAllMutiBulletArr,mbt){
		Sprite* mutiBullet = (Sprite*)mbt;
		Array* enemy2ToDelete = Array::create();
		enemy2ToDelete->retain();
		//enemy2 and mutibullet 's contact
		CCARRAY_FOREACH(this->mEnemyLayer->m_pAllEnemy2,et){
			Enemy* enemy2 = (Enemy*) et;
			if(mutiBullet->boundingBox().intersectsRect(enemy2->getBoundingBox())){
				if(enemy2->getLife() > 1){
					enemy2->loseLife();
					mutiBulletToDelete->addObject(mutiBullet);
				}else if(enemy2->getLife() == 1){
					enemy2->loseLife();
					mutiBulletToDelete->addObject(mutiBullet);
					enemy2ToDelete->addObject(enemy2);
					score += ENEMY2_SCORE;
					this->mControlLayer->updateScore(score);
				}
			}
		}
		//blowup
		CCARRAY_FOREACH(enemy2ToDelete,et){
			Enemy* enemy2 = (Enemy*) et;
			this->mEnemyLayer->enemy2Blowup(enemy2);
		}
		enemy2ToDelete->release();
	}
	CCARRAY_FOREACH(mutiBulletToDelete,mbt){
		Sprite* mutiBullet = (Sprite*)mbt;
		this->mMutiBulletLayer->mutiBulletRemove(mutiBullet);
	}
	mutiBulletToDelete->removeAllObjects();

	


	//enemy3 and muti_bullet
	CCARRAY_FOREACH(this->mMutiBulletLayer->pAllMutiBulletArr,mbt){
		Sprite* mutiBullet = (Sprite*)mbt;
		Array* enemy3ToDelete = Array::create();
		enemy3ToDelete->retain();
		//enemy2 and mutibullet 's contact
		CCARRAY_FOREACH(this->mEnemyLayer->m_pAllEnemy3,et){
			Enemy* enemy3 = (Enemy*) et;
			if(mutiBullet->boundingBox().intersectsRect(enemy3->getBoundingBox())){
				if(enemy3->getLife() > 1){
					enemy3->loseLife();
					mutiBulletToDelete->addObject(mutiBullet);
				}else if(enemy3->getLife() == 1){
					enemy3->loseLife();
					mutiBulletToDelete->addObject(mutiBullet);
					enemy3ToDelete->addObject(enemy3);
					score += ENEMY3_SCORE;
					this->mControlLayer->updateScore(score);
				}
			}
		}
		//blowup
		CCARRAY_FOREACH(enemy3ToDelete,et){
			Enemy* enemy3 = (Enemy*) et;
			this->mEnemyLayer->enemy3Blowup(enemy3);
		}
		enemy3ToDelete->release();
	}
	CCARRAY_FOREACH(mutiBulletToDelete,mbt){
		Sprite* mutiBullet = (Sprite*)mbt;
		this->mMutiBulletLayer->mutiBulletRemove(mutiBullet);
	}
	mutiBulletToDelete->removeAllObjects();
	mutiBulletToDelete->release();

	//碰撞检测
	Rect airPlaneRect = this->mPlaneLayer->getChildByTag(Tag_Air_Plane)->boundingBox();
	airPlaneRect.origin.x += 30;
	airPlaneRect.size.width -= 60;

	//enemy1
	CCARRAY_FOREACH(this->mEnemyLayer->m_pAllEnemy1,et){
		Enemy* enemy1 = (Enemy*) et;
		if(enemy1->getLife()>0){
			if(airPlaneRect.intersectsRect(enemy1->getBoundingBox())){
				this->unscheduleAllSelectors();
				this->mBulletLayer->StopShoot();
				this->mMutiBulletLayer->stopShoot();
				this->mPlaneLayer->blowup(score);
				return ;
			}
		}
	}
	//enemy2
	CCARRAY_FOREACH(this->mEnemyLayer->m_pAllEnemy2,et){
		Enemy* enemy2 = (Enemy*)et;
		if(enemy2->getLife() > 0){
			if(airPlaneRect.intersectsRect(enemy2->getBoundingBox())){

				this->unscheduleAllSelectors();
				this->mBulletLayer->StopShoot();
				this->mMutiBulletLayer->stopShoot();
				this->mPlaneLayer->blowup(score);
				return ;
			}
		}
	}
	//enemy3
	CCARRAY_FOREACH(this->mEnemyLayer->m_pAllEnemy3,et){
		Enemy* enemy3 = (Enemy*)et;
		if(enemy3->getLife()>0){
			if(airPlaneRect.intersectsRect(enemy3->getBoundingBox())){
				this->unscheduleAllSelectors();
				this->mBulletLayer->StopShoot();
				this->mMutiBulletLayer->stopShoot();
				this->mPlaneLayer->blowup(score);
				return ;
			}
		}
	}
	//ufo mutiBullet
	CCARRAY_FOREACH(this->mUFOLayer->m_pAllMutiBullets,ut){
		Sprite* mutiBulletUFO = (Sprite*)ut;
		if(this->mPlaneLayer->getChildByTag(Tag_Air_Plane)->boundingBox().intersectsRect(mutiBulletUFO->boundingBox())){
			SimpleAudioEngine::getInstance()->playEffect("get_double_laser.mp3");
			this->mUFOLayer->RemoveMutiBullets(mutiBulletUFO);
			this->mBulletLayer->StopShoot();
			this->mMutiBulletLayer->startShoot();
			this->mBulletLayer->StartShoot(6.2f);
		}
	}
	//bigboom
	CCARRAY_FOREACH(this->mUFOLayer->m_pAllBigBoom,ut){
		Sprite* bigboom = (Sprite*)ut;
		if(this->mPlaneLayer->getChildByTag(Tag_Air_Plane)->boundingBox().intersectsRect(bigboom->boundingBox())){
			SimpleAudioEngine::getInstance()->playEffect("get_bomb.mp3");
			this->mUFOLayer->RemoveBigBoom(bigboom);
			bigBoomCount ++;

			updateBigBoomItem(bigBoomCount);
		}
	}

}

void GameLayer::updateBigBoomItem(int bigBoomCount){
	auto normalBomb = Sprite::createWithSpriteFrameName("bomb.png");
	auto pressBomb = Sprite::createWithSpriteFrameName("bomb.png");

	if(bigBoomCount < 0){
		return;
	}else if(bigBoomCount == 0){
		if(this->getChildByTag(TAG_BIGBOOM_MENUITEM)){
			this->removeChildByTag(TAG_BIGBOOM_MENUITEM,true);
		}
		if(this->getChildByTag(TAG_BIGBOOMCOUNT_LABEL)){
			this->removeChildByTag(TAG_BIGBOOMCOUNT_LABEL,true);
		}
	}else if(bigBoomCount == 1)
	{
		 if(!this->getChildByTag(TAG_BIGBOOM_MENUITEM)){
			 MenuItemSprite* menuitem = MenuItemSprite::create(normalBomb,pressBomb,NULL,CC_CALLBACK_1(GameLayer::menuBigBoomCallBack,this));
			 menuitem->setPosition(Point(normalBomb->getContentSize().width/2 + 10, normalBomb->getContentSize().height / 2 + 10));
			 Menu* menu = Menu::create(menuitem,NULL);
			 menu->setPosition(Point::ZERO);
			 this->addChild(menu,0,TAG_BIGBOOM_MENUITEM);
		 }
		 if(this->getChildByTag(TAG_BIGBOOMCOUNT_LABEL)){
			 this->removeChildByTag(TAG_BIGBOOMCOUNT_LABEL,true);
		 }
	}else {
		if(!this->getChildByTag(TAG_BIGBOOM_MENUITEM)){
			MenuItemSprite* menuitem = MenuItemSprite::create(normalBomb,pressBomb,NULL,CC_CALLBACK_1(GameLayer::menuBigBoomCallBack,this));
			menuitem->setPosition(Point(normalBomb->getContentSize().width/2 + 10, normalBomb->getContentSize().height / 2 + 10));
			Menu* menu = Menu::create(menuitem,NULL);
			menu->setPosition(Point::ZERO);
			this->addChild(menu,0,TAG_BIGBOOM_MENUITEM);
		}
		if(this->getChildByTag(TAG_BIGBOOMCOUNT_LABEL)){
			this->removeChildByTag(TAG_BIGBOOMCOUNT_LABEL,true);
		}
		if(bigBoomCount >= 0 && bigBoomCount < MAX_BIGBOOM_COUNT){
			String* strScore = String::createWithFormat("X%d",bigBoomCount);
			LabelBMFont* label = LabelBMFont::create(strScore->getCString(),"font/font.fnt");
			label->setColor(ccc3(143,146,147));
			label->setAnchorPoint(Point(0,0.5));
			label->setPosition(Point(normalBomb->getContentSize().width + 15 ,normalBomb->getContentSize().height/2 + 5));
			this->addChild(label,0,TAG_BIGBOOMCOUNT_LABEL);

		}
	}

}

void GameLayer::menuBigBoomCallBack(Object* pSender){
	if(bigBoomCount > 0 && !Director::getInstance()->isPaused()){
		SimpleAudioEngine::getInstance()->playEffect("use_boom.mp3");
		bigBoomCount --;
		score += this->mEnemyLayer->m_pAllEnemy1->count() * ENEMY1_SCORE;
		score += this->mEnemyLayer->m_pAllEnemy2->count() * ENEMY2_SCORE;
		score += this->mEnemyLayer->m_pAllEnemy3->count() * ENEMY3_SCORE;
		this->mEnemyLayer->removeAllEnemy();
		updateBigBoomItem(bigBoomCount);
		this->mControlLayer->updateScore(score);

	}
}