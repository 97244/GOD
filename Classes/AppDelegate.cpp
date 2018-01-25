#include "AppDelegate.h"
#include "GameMain.h"
#include "FontChina.h"
#include "AppMacros.h"
#include <vector>
#include <string>
#include "LoginScenes.h"
#include "SceneManager.h"
using namespace std;
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
	
	
	// initialize director
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = pDirector->getOpenGLView();
	if (!pEGLView) {
		pEGLView = GLViewImpl::createWithRect(FontChina::G2U("·âÉñ°ñ"), Rect(0, 0, 1186, 640));
		Director::getInstance()->setOpenGLView(pEGLView);
	}

	pEGLView->setFrameZoomFactor(0.7f);
	pDirector->setOpenGLView(pEGLView);
	pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);

	Size frameSize = pEGLView->getFrameSize();
	vector<string> searchPath;
	if (frameSize.height > mediumResource.size.height)
	{
		searchPath.push_back(largeResource.directory);

		pDirector->setContentScaleFactor(MIN(largeResource.size.height / designResolutionSize.height, largeResource.size.width / designResolutionSize.width));
	}
	else if (frameSize.height > smallResource.size.height)
	{
		searchPath.push_back(mediumResource.directory);

		pDirector->setContentScaleFactor(MIN(mediumResource.size.height / designResolutionSize.height, mediumResource.size.width / designResolutionSize.width));
	}
	else
	{
		searchPath.push_back(smallResource.directory);

		pDirector->setContentScaleFactor(MIN(smallResource.size.height / designResolutionSize.height, smallResource.size.width / designResolutionSize.width));
	}

	FileUtils::getInstance()->setSearchPaths(searchPath);
	SceneManager::getInstance()->changeScene(SceneManager::en_LoginScene);
	return true;

}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
