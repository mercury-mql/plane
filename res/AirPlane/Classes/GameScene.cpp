#include "GameScene.h"

GameScene::GameScene(){
	_gameLayer = NULL;
}

GameScene::~GameScene(){}

bool GameScene::init(){
	if(!Scene::init()){
		return false;
	}
	_gameLayer = GameLayer::create();
	this->addChild(_gameLayer);

	return true;
}

