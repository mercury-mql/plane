#pragma once
#include "cocos2d.h"
#include "Enemy.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
using namespace CocosDenshion;

const int Enemy1_MaxLife = 1;
const int Enemy2_MaxLife = 5;
const int Enemy3_MaxLife = 10;

typedef enum Level
{
	EASY,
	MIDDLE,
	HARD,
}GameLevel;

class EnemyLayer : public Layer
{
public:
	EnemyLayer(void);
	~EnemyLayer(void);
	CREATE_FUNC(EnemyLayer);
	virtual bool init();

	void addEnemy1(float dt);
	void enemy1MoveFinished(Node* pSender);
	void enemy1Blowup(Enemy* enemy1);
	void removeEnemy1(Object* data);
	void removeAllEnemy1();

	void addEnemy2(float dt);
	void enemy2MoveFinished(Node* pSender);
	void enemy2Blowup(Enemy* enemy2);
	void removeEnemy2(Node* pSender);
	void removeAllEnemy2();

	void addEnemy3(float dt);
	void enemy3MoveFinished(Node* pSender);
	void enemy3Blowup(Enemy* enemy3);
	void removeEnemy3(Node* pSender);
	void removeAllEnemy3();
	void removeAllEnemy();

	Array* m_pAllEnemy1;
	Array* m_pAllEnemy2;
	Array* m_pAllEnemy3;

private:
	SpriteFrame* enemy1SpriteFrame;
	SpriteFrame* enemy2SpriteFrame;
	SpriteFrame* enemy3SpriteFrame_1;
	SpriteFrame* enemy3SpriteFrame_2;


};