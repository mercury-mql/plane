#include "Enemy.h"

Enemy::Enemy(){
	this->m_life = 0 ;
	this->m_sprite = NULL;
}

Enemy::~Enemy(){
	
}

bool Enemy::init(){
	return true;
}

void Enemy::bindSprite(CCSprite* sprite,int life){
	this->m_sprite = sprite;
	this->m_life = life;
	this->addChild(m_sprite);
}

Sprite* Enemy::getSprite(){
	return this->m_sprite;
}
int Enemy::getLife(){
	return this->m_life;
}


void Enemy::loseLife(){
	m_life -- ;
}

void Enemy::die(){
	m_life = 0;
}

Rect Enemy::getBoundingBox(){
	Rect rect = this->m_sprite->boundingBox();
	Point pos = this->convertToWorldSpace(rect.origin);
	return Rect(pos.x, pos.y, rect.size.width, rect.size.height);
}
