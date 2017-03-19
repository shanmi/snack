#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameSceneModel.h"
#include "SnackModel.h"

class HandleView;
class MapLayer;
class SnackView;
class AISnackView;
class FoodNode;

class GameScene 
	: public cocos2d::CCLayer
	, public IGameSceneView
	, public ISnackNode
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();

	virtual void onEnter();
	virtual void onExit();
    
    
    // implement the "static node()" method manually
	CREATE_FUNC(GameScene);

public:
	virtual void update(float fDelta);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouches, cocos2d::CCEvent *pEvent);

public:
	void updateViewPosition(cocos2d::CCPoint &pos);
	void removeAISnackById(int snackId);

public:
	void addFoodNode();
	void addDeadSnackFood(cocos2d::CCPoint pos);
	void addAISnackById(int snackId);
private:
	HandleView* m_handle;
	MapLayer *m_mapLayer;
	SnackView *m_snackView;
	cocos2d::CCSpriteBatchNode *m_foods;
	std::vector<AISnackView *> m_AISnackViews;
};

#endif
