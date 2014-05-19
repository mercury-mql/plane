#pragma 

#include "cocos2d.h"
#include "WelcomeLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

class WelcomeScene : public Scene{
public:
	WelcomeScene(void);

	~WelcomeScene(void);

	virtual bool init();

	CREATE_FUNC(WelcomeScene);

	void PreloadMusic();

public:
	WelcomeLayer* _welcomeLayer;

};