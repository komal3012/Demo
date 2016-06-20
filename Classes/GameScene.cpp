//
//  GameScene.cpp
//  proj_GA
//
//  Created by Komal Shah on 03/06/16.
//
//
#include "AppDelegate.h"
#include "GameScene.hpp"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init(){
    //////////////////////////////
    // 1. super init first
    if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    quesIngame = 0;
    rightAns = 0;
    presentBeam =1;
    
    //add required sprite sheets
    //--------------------------------------------------
    SpriteFrameCache::getInstance()->removeSpriteFrames();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/bird.plist", "plist/bird.png");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/boyDown.plist", "plist/boyDown.png");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/boyUp.plist", "plist/boyUp.png");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/canvas.plist", "plist/canvas.png");
    //--------------------------------------------------

    //add bg,beam,boy
    //--------------------------------------------------
    bg = Sprite::create("bg5.png");
    bg->setPosition(visibleSize.width/2, visibleSize.height/2);
    bg->setScale(1.5);
    this->addChild(bg, 1);
    
    sp_beam1 = Sprite::create("flatCliffSprite2_1.png");
    pos_Middle = Vec2(visibleSize.width - sp_beam1->getBoundingBox().size.width/2,visibleSize.height/2);
    sp_beam1->setPosition(pos_Middle);
    this->addChild(sp_beam1, 1);
    
    sp_beam0 = Sprite::create("flatCliffSprite2_2.png");
    pos_Up =Vec2(visibleSize.width - sp_beam0->getBoundingBox().size.width/2,visibleSize.height/2 + sp_beam1->getBoundingBox().size.height/2 + sp_beam0->getBoundingBox().size.height/2);
    sp_beam0->setPosition(pos_Up);
    this->addChild(sp_beam0, 1);
    
    sp_beam2 = Sprite::create("flatCliffSprite2_3.png");
    pos_Down = Vec2(visibleSize.width - sp_beam2->getBoundingBox().size.width/2, visibleSize.height/2 - sp_beam1->getBoundingBox().size.height/2 - sp_beam2->getBoundingBox().size.height/2);
    sp_beam2->setPosition(pos_Down);
    this->addChild(sp_beam2, 1);
    
    sp_boy = Sprite::createWithSpriteFrameName("boyDown_1.png");
    pos_Boy = Vec2(visibleSize.width - sp_beam1->getBoundingBox().size.width , visibleSize.height/2 + sp_boy->getBoundingBox().size.height*0.25);
    sp_boy->setPosition(visibleSize.width - sp_beam1->getBoundingBox().size.width , sp_beam1->getBoundingBox().size.height/2 - sp_boy->getBoundingBox().size.height*0.25);
    this->addChild(sp_boy, 1);
    //-----------------------------------------------------

    //add canvas,bird,right and wrong
    //-----------------------------------------------------
    canvas = Sprite::createWithSpriteFrameName("Canvas_1.png");
    canvas->setPosition(visibleSize.width/2 - sp_beam1->getBoundingBox().size.width/2, visibleSize.height/2);
    this->addChild(canvas, 1);
    
    sp_birdLeft = Sprite::createWithSpriteFrameName("bird_1.png");
    sp_birdLeft->setPosition(canvas->getPositionX() - canvas->getBoundingBox().size.width/2 - sp_birdLeft->getBoundingBox().size.width*0.2, canvas->getPositionY() + canvas->getBoundingBox().size.height/2- sp_birdLeft->getBoundingBox().size.height*0.7);
    sp_birdLeft->setFlippedX(true);
    this->addChild(sp_birdLeft, 1);
    
    sp_birdRight = Sprite::createWithSpriteFrameName("bird_1.png");
    sp_birdRight->setPosition(canvas->getPositionX() + canvas->getBoundingBox().size.width/2 - sp_birdRight->getBoundingBox().size.width*1.3, canvas->getPositionY() + canvas->getBoundingBox().size.height/2 - sp_birdRight->getBoundingBox().size.height/2);
    this->addChild(sp_birdRight, 1);

    sp_right = Sprite::create("tick.png");
    sp_right->setPosition(canvas->getBoundingBox().size.width/2,canvas->getBoundingBox().size.height/2);
    sp_right->setVisible(false);
    canvas->addChild(sp_right, 1);
    
    sp_wrong = Sprite::create("wrong.png");
    sp_wrong->setPosition(canvas->getBoundingBox().size.width/2,canvas->getBoundingBox().size.height/2);
    sp_wrong->setVisible(false);
    canvas->addChild(sp_wrong, 1);
    //------------------------------------------------------
    
    
    //add stone, distance images
    //-------------------------------------------------------
    sp_stone1 = Sprite::create("stones/stones.png");
    pos_stone1 = Vec2(visibleSize.width -sp_stone1->getBoundingBox().size.width/2,sp_stone1->getBoundingBox().size.height);
    sp_stone1->setPosition(visibleSize.width -sp_stone1->getBoundingBox().size.width/2,sp_stone1->getBoundingBox().size.height);
    this->addChild(sp_stone1, 1);
    
    sp_stone2 = Sprite::create("stones/stones2.png");
    pos_stone2 = Vec2(visibleSize.width -sp_stone2->getBoundingBox().size.width/2, visibleSize.height - sp_stone2->getBoundingBox().size.height);
    sp_stone2->setPosition(visibleSize.width -sp_stone2->getBoundingBox().size.width/2, visibleSize.height - sp_stone2->getBoundingBox().size.height);
    this->addChild(sp_stone2, 1);
    
    sp_distance = Sprite::create("distance/distance.png");
    pos_distance   =    Vec2(visibleSize.width - sp_beam0->getBoundingBox().size.width, sp_stone1->getPositionY() + sp_stone1->getBoundingBox().size.height + sp_distance->getBoundingBox().size.height*0.7);
    sp_distance->setPosition(visibleSize.width - sp_beam0->getBoundingBox().size.width, sp_stone1->getPositionY() + sp_stone1->getBoundingBox().size.height + sp_distance->getBoundingBox().size.height*0.7);
    this->addChild(sp_distance, 1);
    //-------------------------------------------------------
    
    //Animation
    //---------------------------------------------------------
    for(int i=1; i<=25; i++){
        frames_bird.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("bird_%d.png",i)));
    }
    for(int i=1; i<=14; i++){
        frames_boyDown.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("boyDown_%d.png",i)));
        frames_boyUp.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("boyUp_%d.png",i)));
    }
    for(int i=1,j=6; i<=6; i++,j--){
        frames_canvasUp.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("Canvas_%d.png",i)));
        frames_canvasDown.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("Canvas_%d.png",j)));
    }
    sp_birdLeft->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frames_bird, 0.04))));
    sp_birdRight->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frames_bird, 0.04))));
    //---------------------------------------------------------
    
    this->fn_addQuestion();
    this->fn_addAnsStone();
    
//    Button *bn_back = Button::create("a.png","a.png");
//    bn_back->setPosition(Vec2(bn_back->getBoundingBox().size.width/2,visibleSize.height - bn_back->getBoundingBox().size.height/2));
//    this->addChild(bn_back, 1);
//    bn_back->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
//        switch (type){
//            case ui::Widget::TouchEventType::BEGAN:
//                break;
//            case ui::Widget::TouchEventType::ENDED:{
//                auto scene = MainMenuScene::createScene();
//                Color3B color = Color3B(242,114,93);
//                auto transition = TransitionFade::create(1.0, scene, color);
//                Director::getInstance()->replaceScene(transition);
//            }
//                break;
//            default:
//                break;
//        }
//    });
    return true;
}
void GameScene::fn_addAnsStone()
{
     Size visibleSize = Director::getInstance()->getVisibleSize();
    
    //select random answerstone, stones and distance image
    //---------------------------------------------------------
    int rand = 1 + arc4random()%4;
    std::string bn_image1;
    std::string bn_image2;
    std::string bn_image3;
    std::string bn_image4;
    switch (rand) {
        case 1:
            bn_image1 = "answerStone/a.png";
            bn_image2 = "answerStone/b.png";
            bn_image3 = "answerStone/c.png";
            bn_image4 = "answerStone/d.png";
            sp_stone1->setTexture("stones/stones2.png");
            sp_stone2->setTexture("stones/stones4.png");
            sp_distance->setTexture("distance/distance.png");
            break;
        case 2:
            bn_image1 = "answerStone/a2.png";
            bn_image2 = "answerStone/b2.png";
            bn_image3 = "answerStone/c2.png";
            bn_image4 = "answerStone/d2.png";
            sp_stone1->setTexture("stones/stones.png");
            sp_stone2->setTexture("stones/stones3.png");
            sp_distance->setTexture("distance/distance2.png");
            break;
        case 3:
            bn_image1 = "answerStone/a3.png";
            bn_image2 = "answerStone/b3.png";
            bn_image3 = "answerStone/c3.png";
            bn_image4 = "answerStone/d3.png";
            sp_stone1->setTexture("stones/stones4.png");
            sp_stone2->setTexture("stones/stones2.png");
            sp_distance->setTexture("distance/distance3.png");
            break;
        case 4:
            bn_image1 = "answerStone/a4.png";
            bn_image2 = "answerStone/b4.png";
            bn_image3 = "answerStone/c4.png";
            bn_image4 = "answerStone/d4.png";
            sp_stone1->setTexture("stones/stones3.png");
            sp_stone2->setTexture("stones/stones.png");
            sp_distance->setTexture("distance/distance4.png");
            break;
            
        default:
            break;
    }
    //---------------------------------------------------------
    
    //answer option buttons
    //---------------------------------------------------------
    //-------------------------------OptionD-------------------------------
    bn_optionD = Button::create(bn_image4,bn_image4);
    bn_optionD->setPosition(Vec2(visibleSize.width - bn_optionD->getBoundingBox().size.width/2,sp_beam1->getBoundingBox().size.height/2));
    this->addChild(bn_optionD, 1);
    bn_optionD->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:{
                //
                if (rightAns == 4) {
                    sp_boy->runAction(Animate::create(Animation::createWithSpriteFrames(frames_boyUp, 0.04)));
                    sp_right->setVisible(true);
                    CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(GameScene::fn_correctAns, this));
                    this->runAction(Sequence::create(DelayTime::create(0.5), runCallback, nullptr));
                }
                else{
                    sp_wrong->setVisible(true);
                    sp_boy->runAction(Animate::create(Animation::createWithSpriteFrames(frames_boyDown, 0.04)));
                    bn_optionD->setEnabled(false);
                    bn_optionD->setVisible(false);
                    CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(GameScene::fn_wrongAns, this));
                    this->runAction(Sequence::create(DelayTime::create(0.5), runCallback, nullptr));
                }
            }
                break;
            default:
                break;
        }
    });
    //-------------------------------OptionC-------------------------------
    bn_optionC = Button::create(bn_image3,bn_image3);
    bn_optionC->setPosition(Vec2(bn_optionD->getPositionX() - bn_optionC->getBoundingBox().size.width,sp_beam1->getBoundingBox().size.height/2));
    this->addChild(bn_optionC, 1);
    bn_optionC->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:{
                if (rightAns == 3) {
                    sp_boy->runAction(Animate::create(Animation::createWithSpriteFrames(frames_boyUp, 0.04)));
                    sp_right->setVisible(true);
                    CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(GameScene::fn_correctAns, this));
                    this->runAction(Sequence::create(DelayTime::create(0.5), runCallback, nullptr));
                }
                else{
                    sp_wrong->setVisible(true);
                    sp_boy->runAction(Animate::create(Animation::createWithSpriteFrames(frames_boyDown, 0.04)));
                    bn_optionC->setEnabled(false);
                    bn_optionC->setVisible(false);
                    CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(GameScene::fn_wrongAns, this));
                    this->runAction(Sequence::create(DelayTime::create(0.5), runCallback, nullptr));
                }
            }
                break;
            default:
                break;
        }
    });
    //-------------------------------OptionB-------------------------------
    bn_optionB = Button::create(bn_image2,bn_image2);
    bn_optionB->setPosition(Vec2(bn_optionC->getPositionX() - bn_optionB->getBoundingBox().size.width,sp_beam1->getBoundingBox().size.height/2));
    this->addChild(bn_optionB, 1);
    bn_optionB->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:{
                if (rightAns == 2) {
                    sp_boy->runAction(Animate::create(Animation::createWithSpriteFrames(frames_boyUp, 0.04)));
                    sp_right->setVisible(true);
                    CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(GameScene::fn_correctAns, this));
                    this->runAction(Sequence::create(DelayTime::create(0.5), runCallback, nullptr));
                }
                else{
                    sp_wrong->setVisible(true);
                    sp_boy->runAction(Animate::create(Animation::createWithSpriteFrames(frames_boyDown, 0.04)));
                    bn_optionB->setEnabled(false);
                    bn_optionB->setVisible(false);
                    CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(GameScene::fn_wrongAns, this));
                    this->runAction(Sequence::create(DelayTime::create(0.5), runCallback, nullptr));
                }
            }
                break;
            default:
                break;
        }
    });
    //-------------------------------OptionA-------------------------------
    bn_optionA = Button::create(bn_image1,bn_image1);
    bn_optionA->setPosition(Vec2(bn_optionB->getPositionX() - bn_optionA->getBoundingBox().size.width,sp_beam1->getBoundingBox().size.height/2));
    this->addChild(bn_optionA, 1);
    bn_optionA->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:{
                if (rightAns == 1) {
                    sp_boy->runAction(Animate::create(Animation::createWithSpriteFrames(frames_boyUp, 0.04)));
                    sp_right->setVisible(true);
                    CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(GameScene::fn_correctAns, this));
                    this->runAction(Sequence::create(DelayTime::create(0.5), runCallback, nullptr));
                }
                else{
                    sp_wrong->setVisible(true);
                    sp_boy->runAction(Animate::create(Animation::createWithSpriteFrames(frames_boyDown, 0.04)));
                    bn_optionA->setEnabled(false);
                    bn_optionA->setVisible(false);
                    CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(GameScene::fn_wrongAns, this));
                    this->runAction(Sequence::create(DelayTime::create(0.5), runCallback, nullptr));
                }
            }
                break;
            default:
                break;
        }
    });
    //---------------------------------------------------------
}
void GameScene::fn_addQuestion()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    float font_size = (visibleSize.width/1920) * 70;
     //-------------------------------Question label-------------------------------
    lbl_question = Label::createWithTTF("", "fonts/Marker Felt.ttf", font_size);
    lbl_question->setColor(Color3B(0,0,0));
    lbl_question->setString(this->fn_randQuestion());
    lbl_question->setPosition(lbl_question->getBoundingBox().size.width, canvas->getBoundingBox().size.height - lbl_question->getBoundingBox().size.height *3 );
    canvas->addChild(lbl_question);
    
    //-------------------------------Answer label A-------------------------------
    lbl_ansA = Label::createWithTTF("", "fonts/Marker Felt.ttf", font_size);
    lbl_ansA->setColor(Color3B(0,0,0));
    lbl_ansA->setString(this->fn_optionA());
    lbl_ansA->setPosition(lbl_ansA->getBoundingBox().size.width, canvas->getBoundingBox().size.height/2);
    canvas->addChild(lbl_ansA);
    
     //-------------------------------Answer label B-------------------------------
    lbl_ansB = Label::createWithTTF("", "fonts/Marker Felt.ttf", font_size);
    lbl_ansB->setColor(Color3B(0,0,0));
    lbl_ansB->setString(this->fn_optionB());
    lbl_ansB->setPosition(canvas->getBoundingBox().size.width/2 + lbl_ansA->getBoundingBox().size.width/2, canvas->getBoundingBox().size.height/2);
    canvas->addChild(lbl_ansB);
    
     //-------------------------------Answer label C-------------------------------
    lbl_ansC = Label::createWithTTF("", "fonts/Marker Felt.ttf", font_size);
    lbl_ansC->setColor(Color3B(0,0,0));
    lbl_ansC->setString(this->fn_optionC());
    lbl_ansC->setPosition(lbl_ansC->getBoundingBox().size.width, canvas->getBoundingBox().size.height/2 - lbl_ansA->getBoundingBox().size.height * 2);
    canvas->addChild(lbl_ansC);
    
     //-------------------------------Answer label D-------------------------------
    lbl_ansD = Label::createWithTTF("", "fonts/Marker Felt.ttf", font_size);
    lbl_ansD->setColor(Color3B(0,0,0));
    lbl_ansD->setString(this->fn_optionD());
    lbl_ansD->setPosition(canvas->getBoundingBox().size.width/2 + lbl_ansC->getBoundingBox().size.width/2, canvas->getBoundingBox().size.height/2 - lbl_ansA->getBoundingBox().size.height * 2);
    canvas->addChild(lbl_ansD);

}
std::string GameScene::fn_randQuestion()
{
    std::string Question;
    int rand = 1 + arc4random() % 10;
    quesIngame = rand;
    //select random question from 10 total questions
    //---------------------------------------------------
    switch (rand) {
        case 1:
            Question = "9 + 2 = ?";
            rightAns = 1;
            break;
        case 2:
            Question = "9 - 2 = ?";
            rightAns = 4;
            break;
        case 3:
            Question = "8 * 2 = ?";
             rightAns = 3;
            break;
        case 4:
            Question = "10 + 0 = ?";
             rightAns = 3;
            break;
        case 5:
            Question = "17 + 9 = ?";
             rightAns = 2;
            break;
        case 6:
            Question = "17 - 9 = ?";
             rightAns = 2;
            break;
        case 7:
            Question = "11 - 0 = ?";
             rightAns = 1;
            break;
        case 8:
            Question = "2 * 4 = ?";
             rightAns = 4;
             break;
        case 9:
            Question = "20 + 4 = ?";
             rightAns = 3;
            break;
        case 10:
            Question = "30 - 7 = ?";
             rightAns = 2;
            break;
        default:
            break;
    }
    //---------------------------------------------------
    return Question;
}
std::string GameScene::fn_optionA()
{
    std::string optionA;
    switch (quesIngame) {
        case 1:
            optionA = "A.  11";
            break;
        case 2:
            optionA = "A.  8";
            break;
        case 3:
            optionA = "A.  14";
            break;
        case 4:
            optionA = "A.  11";
            break;
        case 5:
            optionA = "A.  25";
            break;
        case 6:
            optionA = "A.  10";
            break;
        case 7:
            optionA = "A.  11";
            break;
        case 8:
            optionA = "A.  11";
            break;
        case 9:
            optionA = "A.  21";
            break;
        case 10:
            optionA = "A.  21";
            break;
        default:
            break;
    }
    return optionA;
}
std::string GameScene::fn_optionB()
{
    std::string optionB;
    switch (quesIngame) {
        case 1:
            optionB = "B.  12";
            break;
        case 2:
            optionB = "B.  11";
            break;
        case 3:
            optionB = "B.  15";
            break;
        case 4:
            optionB = "B.  12";
            break;
        case 5:
            optionB = "B.  26";
            break;
        case 6:
            optionB = "B.  8";
            break;
        case 7:
            optionB = "B.  12";
            break;
        case 8:
            optionB = "B.  12";
            break;
        case 9:
            optionB = "B.  20";
            break;
        case 10:
            optionB = "B.  23";
            break;
        default:
            break;
    }
    return optionB;
}
std::string GameScene::fn_optionC()
{
    std::string optionC;
    switch (quesIngame) {
        case 1:
            optionC = "C.  10";
            break;
        case 2:
            optionC = "C.  10";
            break;
        case 3:
            optionC = "C.  16";
            break;
        case 4:
            optionC = "C.  10";
            break;
        case 5:
            optionC = "C.  24";
            break;
        case 6:
            optionC = "C.  9";
            break;
        case 7:
            optionC = "C.  10";
            break;
        case 8:
            optionC = "C.  14";
            break;
        case 9:
            optionC = "C.  24";
            break;
        case 10:
            optionC = "C.  22";
            break;
        default:
            break;
    }
    return optionC;
}
std::string GameScene::fn_optionD()
{
    std::string optionD;
    switch (quesIngame) {
        case 1:
            optionD = "D.  13";
            break;
        case 2:
            optionD = "D.  7";
            break;
        case 3:
            optionD = "D.  13";
            break;
        case 4:
            optionD = "D.  9";
            break;
        case 5:
            optionD = "D.  20";
            break;
        case 6:
            optionD = "D.  7";
            break;
        case 7:
            optionD = "D.  13";
            break;
        case 8:
            optionD = "D.  8";
            break;
        case 9:
            optionD = "D.  23";
            break;
        case 10:
            optionD = "D.  25";
            break;
        default:
            break;
    }
    return optionD;
}


void GameScene::fn_correctAns()
{
    //remove previous question labels
    //------------------------------------------------
    canvas->removeChild(lbl_question, true);
    canvas->removeChild(lbl_ansA, true);
    canvas->removeChild(lbl_ansB, true);
    canvas->removeChild(lbl_ansC, true);
    canvas->removeChild(lbl_ansD, true);
    //------------------------------------------------
    
    //remove previous answer buttons
    //------------------------------------------------
    this->removeChild(bn_optionA);
    this->removeChild(bn_optionB);
    this->removeChild(bn_optionC);
    this->removeChild(bn_optionD);
    //------------------------------------------------
    
    sp_stone1->setVisible(false);
    sp_stone2->setVisible(false);
    sp_distance->setVisible(false);
    
    //canvas animation
    //------------------------------------------------
    Animate *canvasUp =Animate::create(Animation::createWithSpriteFrames(frames_canvasUp, 0.08));
    Animate *canvasDown =Animate::create(Animation::createWithSpriteFrames(frames_canvasDown, 0.08));
    
    CallFunc *runCallbackQ = CallFunc::create(CC_CALLBACK_0(GameScene::fn_addQuestion, this));
    CallFunc *runCallbackA = CallFunc::create(CC_CALLBACK_0(GameScene::fn_addAnsStone, this));
    
    Sequence *sequneceAction = Sequence::create(canvasUp,canvasDown,runCallbackQ,runCallbackA, NULL);
    canvas->runAction(sequneceAction);
    //------------------------------------------------
    
    //beam movement
    //------------------------------------------------
    if (presentBeam == 1) {
        MoveBy *moveAction = MoveBy::create(1.0, Vec2(0,-sp_beam1->getBoundingBox().size.height));
        sp_beam1->runAction(moveAction);
        
        MoveBy *moveAction1 = MoveBy::create(1.0, Vec2(0,-sp_beam0->getBoundingBox().size.height));
        sp_beam0->runAction(moveAction1);
        
        MoveBy *moveAction2 = MoveBy::create(1.0, Vec2(0,-sp_beam1->getBoundingBox().size.height));
        sp_boy->runAction(moveAction2);
        
        sp_beam2->setPosition(Vec2(pos_Up));
        CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(GameScene::fn_placement, this));
        this->runAction(Sequence::create(DelayTime::create(1.1), runCallback, nullptr));
        
        presentBeam = 0;
    }
    else if (presentBeam == 2){
        MoveBy *moveAction = MoveBy::create(1.0, Vec2(0,-sp_beam2->getBoundingBox().size.height));
        sp_beam2->runAction(moveAction);
        
        MoveBy *moveAction1 = MoveBy::create(1.0, Vec2(0,-sp_beam1->getBoundingBox().size.height));
        sp_beam1->runAction(moveAction1);
        
        MoveBy *moveAction2 = MoveBy::create(1.0, Vec2(0,-sp_beam1->getBoundingBox().size.height));
        sp_boy->runAction(moveAction2);
        
        sp_beam0->setPosition(Vec2(pos_Up));
        CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(GameScene::fn_placement, this));
        this->runAction(Sequence::create(DelayTime::create(1.1), runCallback, nullptr));
        
        presentBeam = 1;
        
    }
    else if (presentBeam == 0){
        MoveBy *moveAction = MoveBy::create(1.0, Vec2(0,-sp_beam0->getBoundingBox().size.height));
        sp_beam0->runAction(moveAction);
        
        MoveBy *moveAction1 = MoveBy::create(1.0, Vec2(0,-sp_beam2->getBoundingBox().size.height));
        sp_beam2->runAction(moveAction1);
        
        MoveBy *moveAction2 = MoveBy::create(1.0, Vec2(0,-sp_beam1->getBoundingBox().size.height));
        sp_boy->runAction(moveAction2);
        
        sp_beam1->setPosition(Vec2(pos_Up));
        
        CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(GameScene::fn_placement, this));
        this->runAction(Sequence::create(DelayTime::create(1.1), runCallback, nullptr));
        presentBeam = 2;
        
    }
     //------------------------------------------------
    
}
void GameScene::fn_wrongAns()
{

    sp_stone1->setVisible(false);
    sp_stone2->setVisible(false);
    sp_distance->setVisible(false);
    
    //beam movement
    //------------------------------------------------
    if (presentBeam == 1) {
        MoveBy *moveAction = MoveBy::create(1.0, Vec2(0,sp_beam1->getBoundingBox().size.height));
        sp_beam1->runAction(moveAction);
        
        MoveBy *moveAction1 = MoveBy::create(1.0, Vec2(0,sp_beam2->getBoundingBox().size.height));
        sp_beam2->runAction(moveAction1);
        
        MoveBy *moveAction2 = MoveBy::create(1.0, Vec2(0,sp_beam1->getBoundingBox().size.height));
        sp_boy->runAction(moveAction2);
        
        sp_beam0->setPosition(Vec2(pos_Down));
        CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(GameScene::fn_placement, this));
        this->runAction(Sequence::create(DelayTime::create(1.1), runCallback, nullptr));

        presentBeam = 2;
    }
    else if (presentBeam == 2){
        MoveBy *moveAction = MoveBy::create(1.0, Vec2(0,sp_beam2->getBoundingBox().size.height));
        sp_beam2->runAction(moveAction);
        
        MoveBy *moveAction1 = MoveBy::create(1.0, Vec2(0,sp_beam0->getBoundingBox().size.height));
        sp_beam0->runAction(moveAction1);
        
        MoveBy *moveAction2 = MoveBy::create(1.0, Vec2(0,sp_beam1->getBoundingBox().size.height));
        sp_boy->runAction(moveAction2);
        
        sp_beam1->setPosition(Vec2(pos_Down));
        CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(GameScene::fn_placement, this));
        this->runAction(Sequence::create(DelayTime::create(1.1), runCallback, nullptr));

        presentBeam = 0;
    }
    else if (presentBeam == 0){
        MoveBy *moveAction = MoveBy::create(1.0, Vec2(0,sp_beam0->getBoundingBox().size.height));
        sp_beam0->runAction(moveAction);
        
        MoveBy *moveAction1 = MoveBy::create(1.0, Vec2(0,sp_beam1->getBoundingBox().size.height));
        sp_beam1->runAction(moveAction1);
        
        MoveBy *moveAction2 = MoveBy::create(1.0, Vec2(0,sp_beam1->getBoundingBox().size.height));
        sp_boy->runAction(moveAction2);
        
        sp_beam2->setPosition(Vec2(pos_Down));
        CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(GameScene::fn_placement, this));
        this->runAction(Sequence::create(DelayTime::create(1.1), runCallback, nullptr));
        presentBeam = 1;
        
    }
    //------------------------------------------------
}
void GameScene::fn_placement()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    sp_boy->setSpriteFrame("boyDown_1.png");
    if(AppDelegate::getDelegate()->deviceType==1)
        pos_Boy = Vec2(visibleSize.width - sp_beam1->getBoundingBox().size.width , visibleSize.height/2 - sp_boy->getBoundingBox().size.height*0.25);
    else
        pos_Boy = Vec2(visibleSize.width - sp_beam1->getBoundingBox().size.width , visibleSize.height/2 - sp_boy->getBoundingBox().size.height*0.15);
    sp_boy->setPosition(pos_Boy);
    
    sp_stone1->setPosition(pos_stone1);
    sp_stone2->setPosition(pos_stone2);
    sp_distance->setPosition(pos_distance);
    
    sp_wrong->setVisible(false);
    sp_right->setVisible(false);
    
    sp_stone1->setVisible(true);
    sp_stone2->setVisible(true);
    sp_distance->setVisible(true);
}