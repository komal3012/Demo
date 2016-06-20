#include "AppDelegate.h"


USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

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

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("proj_GA", Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("proj_GA");
#endif
        director->setOpenGLView(glview);
    }

    auto fileUtils = FileUtils::getInstance();
    auto screenSize = glview->getFrameSize();
    std::vector<std::string> resDirOrders;
    cocos2d::UserDefault::getInstance()->setIntegerForKey("lastgame", 0);
    
    log("iOS device screen res is %f x %f", screenSize.width, screenSize.height);
    if(screenSize.width==2208 || screenSize.height==2208){
        log("iOS device is iPhone 6+");
        deviceType = 1;
        //resDirOrders.push_back("4x");
        resDirOrders.push_back("2x");
        //resDirOrders.push_back("1x");
        //glview->setDesignResolutionSize(2208, 1242, ResolutionPolicy::NO_BORDER);
        glview->setDesignResolutionSize(1104, 621, ResolutionPolicy::NO_BORDER);
    }
    else if(screenSize.width==2048 || screenSize.height==2048){
        log("iOS device is iPad Retina");
        deviceType = 1;
        //resDirOrders.push_back("4x");
        resDirOrders.push_back("2x");
        //resDirOrders.push_back("1x");
        //glview->setDesignResolutionSize(2048, 1536, ResolutionPolicy::NO_BORDER);
        glview->setDesignResolutionSize(1024, 768, ResolutionPolicy::NO_BORDER);
    }
    else if(screenSize.width==1334 || screenSize.height==1334){
        log("iOS device is iPhone 6");
        deviceType = 3;
        resDirOrders.push_back("2x");
        //resDirOrders.push_back("1x");
        glview->setDesignResolutionSize(1136, 640, ResolutionPolicy::NO_BORDER);
    }
    else if(screenSize.width==1024 || screenSize.height==1024){
        log("iOS device is iPad Regular");
        deviceType = 2;
        resDirOrders.push_back("2x");
        //resDirOrders.push_back("1x");
        glview->setDesignResolutionSize(1024, 768, ResolutionPolicy::NO_BORDER);
    }
    else if(screenSize.width==1136 || screenSize.height==1136){
        log("iOS device is iPhone 5");
        deviceType = 3;
        resDirOrders.push_back("2x");
        //resDirOrders.push_back("1x");
        glview->setDesignResolutionSize(1136, 640, ResolutionPolicy::NO_BORDER);
    }
    else if(screenSize.width==960 || screenSize.height==960){
        log("iOS device is iPhone 4");
        resDirOrders.push_back("2x");
        //resDirOrders.push_back("1x");
        glview->setDesignResolutionSize(960, 640, ResolutionPolicy::NO_BORDER);
    }
    else{
        if(screenSize.width>1080){
            log("other 1 if loop");
            resDirOrders.push_back("2x");
            //resDirOrders.push_back("1x");
            glview->setDesignResolutionSize(960, 640, ResolutionPolicy::NO_BORDER);
        }
        else{
            log("other 2 if loop");
            //resDirOrders.push_back("1x");
            //glview->setDesignResolutionSize(480, 320, ResolutionPolicy::NO_BORDER);
        }
    }
    fileUtils->setSearchPaths(resDirOrders);
    // create a scene. it's an autorelease object
    auto scene = MainMenuScene::createScene();
    // run
    director->runWithScene(scene);

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
AppDelegate* AppDelegate::getDelegate() {
    return (AppDelegate *)Application::getInstance();
}
