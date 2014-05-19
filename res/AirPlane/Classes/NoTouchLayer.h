#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class NoTouchLayer: public Layer{
public:
	NoTouchLayer();
	~NoTouchLayer();
	virtual bool init();
	CREATE_FUNC(NoTouchLayer);

	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
};