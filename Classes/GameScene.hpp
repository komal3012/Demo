//
//  GameScene.hpp
//  proj_GA
//
//  Created by Komal Shah on 03/06/16.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::extension;
using namespace cocos2d;
using namespace ui;

class GameScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();
   
    virtual bool init();
    
    int quesIngame;
    int rightAns;
    int presentBeam;
    
    Vec2 pos_Up;
    Vec2 pos_Middle;
    Vec2 pos_Down;
    Vec2 pos_Boy;
    Vec2 pos_stone1;
    Vec2 pos_stone2;
    Vec2 pos_distance;
    
    Button *bn_play;
    Sprite *bg;
    Sprite *canvas;
    Sprite *sp_birdLeft;
    Sprite *sp_birdRight;
    Sprite *sp_boy;
    
    Sprite *sp_beam0;
    Sprite *sp_beam1;
    Sprite *sp_beam2;
    
    Sprite *sp_stone1;
    Sprite *sp_stone2;
    Sprite *sp_distance;
    Sprite *sp_right;
    Sprite *sp_wrong;
    
    Button *bn_optionA;
    Button *bn_optionB;
    Button *bn_optionC;
    Button *bn_optionD;
    
    Label *lbl_question;
    Label *lbl_ansA;
    Label *lbl_ansB;
    Label *lbl_ansC;
    Label *lbl_ansD;
    
    cocos2d::Vector<cocos2d::SpriteFrame *> frames_bird;
    cocos2d::Vector<cocos2d::SpriteFrame *> frames_boyUp;
    cocos2d::Vector<cocos2d::SpriteFrame *> frames_boyDown;
    cocos2d::Vector<cocos2d::SpriteFrame *> frames_canvasUp;
    cocos2d::Vector<cocos2d::SpriteFrame *> frames_canvasDown;
    
  
    //functions
    std::string fn_randQuestion();
    std::string fn_optionA();
    std::string fn_optionB();
    std::string fn_optionC();
    std::string fn_optionD();
    
    void fn_addQuestion();
    void fn_addAnsStone();
    void fn_placement();
    void fn_correctAns();
    void fn_wrongAns();
    void fn_beamTimer(float dt);
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(GameScene);
};
#endif /* GameScene_hpp */