#include "NoTouchLayer.h"

NoTouchLayer::NoTouchLayer(){}

NoTouchLayer::~NoTouchLayer(){}

bool NoTouchLayer::init(){
	if(!Layer::init()){
		return false;
	}

	

// 	//´¥Ãþ¼àÌý
	auto dispatcher = Director::getInstance()->getEventDispatcher();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(NoTouchLayer::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(NoTouchLayer::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(NoTouchLayer::onTouchEnded,this);
	
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	return true;
}

bool NoTouchLayer::onTouchBegan(Touch *pTouch, Event *pEvent){
	return true;
}

void NoTouchLayer::onTouchMoved(Touch *touch, Event *unused_event){

}

void NoTouchLayer::onTouchEnded(Touch *touch, Event *unused_event){

}