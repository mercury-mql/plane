#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "NoTouchLayer.h"

USING_NS_CC;
using namespace CocosDenshion;

const int MAX_SCORE=1000000000;

class ControlLayer : public Layer
{
public:

	ControlLayer(void);

	~ControlLayer(void);

	virtual bool init();

	CREATE_FUNC(ControlLayer);

	void menuPauseCallback(Object* pSender);

	void updateScore(int score);

public:

	LabelBMFont* scoreItem;

	MenuItemSprite* pPauseItem;

	NoTouchLayer* noTouchLayer;

	Sprite* pauseNormal;

	Sprite* pausePressed;
};
