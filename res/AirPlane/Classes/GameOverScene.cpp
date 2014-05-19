#include "GameOverScene.h"

GameOverScene::GameOverScene(){
	score = 0;
	gameOverLayer = NULL;
}

GameOverScene::~GameOverScene(){}



GameOverScene* GameOverScene::create(int passScore){
	GameOverScene* pRet = new GameOverScene();
	pRet->score = passScore;
	if(pRet && pRet->init()){
		pRet->autorelease();
		return pRet;
	}else{
		pRet->release();
		pRet = NULL;
		return NULL;
	}
}

bool GameOverScene::init(){
	if(!Scene::init()){
		return false;
	}
	gameOverLayer = GameOverLayer::create(score);
	this->addChild(gameOverLayer);

	return true;
}