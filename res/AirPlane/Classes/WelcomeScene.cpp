#include "WelcomeScene.h"

WelcomeScene::WelcomeScene(){
	this->_welcomeLayer = NULL;
};

WelcomeScene::~WelcomeScene(){

};

bool WelcomeScene::init(){
	if(!Scene::init()){
		return false;
	}
	_welcomeLayer = WelcomeLayer::create();
	if(_welcomeLayer == NULL){
		return false;
	}
	this->addChild(_welcomeLayer);

	PreloadMusic();

	return true;
}

void WelcomeScene::PreloadMusic(){
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("game_music.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("bullet.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("enemy1_down.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("enemy2_down.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("enemy3_down.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("game_over.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("get_bomb.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("get_double_laser.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("use_bomb.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("big_spaceship_flying.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("achievement.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("out_porp.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("button.mp3");

	SimpleAudioEngine::getInstance()->playBackgroundMusic("game_music.mp3",true);

	
}