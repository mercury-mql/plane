#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "PlaneLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;

class MutiBulletLayer : public Layer{
public:
	MutiBulletLayer();
	~MutiBulletLayer();
	virtual bool init();
	CREATE_FUNC(MutiBulletLayer);

	void startShoot(float delay = 0);

	void stopShoot();

	void addMutiBullet(float dt);

	void mutiBulletMoveFinish(Object* pSender);

	void mutiBulletRemove(Sprite* bullet);

public:
	SpriteBatchNode* mutiBulletBacthNode;
	Array* pAllMutiBulletArr ;
};