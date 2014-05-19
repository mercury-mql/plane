#pragma once

#include "cocos2d.h"
#include "PlaneLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

class BulletLayer : public CCLayer
{
public:

	BulletLayer(void);

	~BulletLayer(void);

	CREATE_FUNC(BulletLayer);

	virtual bool init();

	void AddBullet(float dt);

	void bulletMoveFinished(Node* pSender);

	void RemoveBullet(Sprite* bullet);

	void StartShoot(float delay=0.0f);

	void StopShoot();

public:

	Array* m_pAllBullet;

	SpriteBatchNode* bulletBatchNode;

};