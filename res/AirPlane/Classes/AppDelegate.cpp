#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "WelcomeScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::createWithRect("shun's air plane",Rect(0,0,480,800),0.5);
		//
        director->setOpenGLView(glview);
    }
	glview->setDesignResolutionSize(480,800,ResolutionPolicy::SHOW_ALL);
    

	setResourceSearchResolution();


    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = WelcomeScene::create();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AppDelegate::setResourceSearchResolution(){
	std::vector<std::string> paths;
	paths.push_back("font");
	paths.push_back("ui");
	paths.push_back("sound");
	FileUtils::getInstance()->setSearchResolutionsOrder(paths);
}
