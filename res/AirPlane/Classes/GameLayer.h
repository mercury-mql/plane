#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "PlaneLayer.h"
#include "BulletLayer.h"
#include "MutiBulletLayer.h"
#include "EnemyLayer.h"
#include "ControlLayer.h"
#include "UFOLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;

//blood
const int ENEMY1_SCORE=1000;
const int ENEMY2_SCORE=6000;
const int ENEMY3_SCORE=30000;

const int MAX_BIGBOOM_COUNT=100000;

const int TAG_BIGBOOM_MENUITEM=1;//
const int TAG_BIGBOOMCOUNT_LABEL=2;


class GameLayer : public Layer
{
public:
	GameLayer();

	~GameLayer();
	
	virtual bool init();
	
	CREATE_FUNC(GameLayer);

	void backgroundMove(float dt);

	void registerTouch();

	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);

	void update(float dt);

	void menuBigBoomCallBack(Object* pSender);
	void updateBigBoomItem(int bigBoomCount);
	//level
	static GameLevel getCurLevel();
private:
	Node* backGround;
	Sprite* backGround1;
	Sprite* backGround2;
	PlaneLayer* mPlaneLayer;
	BulletLayer* mBulletLayer;
	MutiBulletLayer* mMutiBulletLayer;
	EnemyLayer* mEnemyLayer;
	ControlLayer* mControlLayer ;
	UFOLayer* mUFOLayer;

	static GameLevel level;
	
	int score;
	int bigBoomCount;

};