
#ifndef MainMenuScene_hpp
#define MainMenuScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::extension;
using namespace cocos2d;
using namespace ui;

class MainMenuScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    Button *bn_play;
    Sprite *bg;
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(MainMenuScene);
};

#endif /* MainMenuScene_hpp */
