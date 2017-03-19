#include "AppDelegate.h"
#include "GameScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	//pEGLView->setFrameSize(1334, 750);
	pEGLView->setFrameSize(1024, 576);
#endif
	CCSize designSize = CCSizeMake(800, 480);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionFixedWidth);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WP8 )
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionFixedWidth);
#else
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionFixedWidth);
#endif
	
	/*CCPointArray *array = CCPointArray::create(100);
	array->addControlPoint(ccp(250, 980));
	array->addControlPoint(ccp(350, 800));

	array->removeControlPointAtIndex(0);
	array->getControlPointAtIndex(0);
	CCLog("pointx==============%d", array->count());*/

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = GameScene::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
