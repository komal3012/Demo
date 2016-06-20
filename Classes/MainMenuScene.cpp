
#include "AppDelegate.h"
#include "MainMenuScene.hpp"
USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init(){
    //////////////////////////////
    // 1. super init first
    if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //add play button
    //--------------------------------------------------
    bn_play = Button::create("play.png","play.png");
    bn_play->setPosition(Vec2(visibleSize.width/2 , visibleSize.height/2 - bn_play->getBoundingBox().size.height/2));
    this->addChild(bn_play, 10);
    bn_play->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
            {
                auto scene = GameScene::createScene();
                Color3B color = Color3B(242,114,93);
                auto transition = TransitionFade::create(1.0, scene, color);
                Director::getInstance()->replaceScene(transition);
            }
                break;
            case ui::Widget::TouchEventType::ENDED:
                break;
            default:
                break;
        }
    });
    
    bg = Sprite::create("bg5.png");
    bg->setPosition(visibleSize.width/2, visibleSize.height/2);
    bg->setScale(1.5);
    this->addChild(bg, 1);
    //--------------------------------------------------
    return true;
}

