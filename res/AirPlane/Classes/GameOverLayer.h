#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

class GameOverLayer  : public Layer
{
public:
	GameOverLayer(void);

	~GameOverLayer(void);

	virtual bool init();

	static GameOverLayer* create(int passScore);

	void menuBackCallback(CCObject* pSender);

//	virtual void keyBackClicked();//

	void beginChangeHighestScore(Node* pNode);

	void showAD();

public:

	int score;

	static int highestHistoryScore;

	LabelBMFont* highestScore;
};
