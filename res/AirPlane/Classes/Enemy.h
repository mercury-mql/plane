#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Enemy : public CCNode
{
public:
	Enemy(void);
	~Enemy(void);
	CREATE_FUNC(Enemy);
	virtual bool init();
	void bindSprite(CCSprite* sprite,int life);
	Sprite* getSprite();
	int getLife();

	void loseLife();
	void die();
	Rect getBoundingBox();

private:
	Sprite* m_sprite;
	int m_life;
};
