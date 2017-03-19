#include "GameScene.h"
#include "MapLayer.h"
#include "SnackView.h"
#include "HandleView.h"
#include "TouchModel.h"
#include "FoodNode.h"
#include "FoodModel.h"
#include "AISnackView.h"

USING_NS_CC;

CCScene* GameScene::scene()
{
	CCScene *scene = CCScene::create();

	CCLayerColor *colorLayer = CCLayerColor::create(ccc4(114, 28, 27, 255));
	scene->addChild(colorLayer);

	GameScene *layer = GameScene::create();
	scene->addChild(layer);

	return scene;
}

void GameScene::onEnter()
{
	CCNode::onEnter();
	GameSceneModel::theModel()->addView(this);
	SnackModel::theModel()->addView(this);
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void GameScene::onExit()
{
	CCNode::onExit();
	GameSceneModel::theModel()->removeView(this);
	SnackModel::theModel()->removeView(this);
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool GameScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	auto size = CCDirector::sharedDirector()->getWinSize();

	m_mapLayer = MapLayer::create(0, 0);
	m_mapLayer->setPosition(0, 0);
	addChild(m_mapLayer);

	for (int i = 0; i < 20; i++)
	{
		addAISnackById(i);
	}

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("foods.plist");
	m_foods = CCSpriteBatchNode::create("foods.png");
	addChild(m_foods);
	srand(time(NULL));
	for (int i = 0; i < 400; i++)
	{
		addFoodNode();
	}

	m_snackView = SnackView::create(m_mapLayer->getContentSize());
	m_snackView->setPosition(size.width * 0.5f, size.height * 0.5f);
	addChild(m_snackView);

	m_handle = HandleView::create();
	m_handle->setPosition(0, 0);
	addChild(m_handle);

	setTouchEnabled(true);

	scheduleUpdate();

	return true;
}


bool GameScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	TouchModel::theModel()->onTonchBegan(pTouch);
	return true;
}

void GameScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	TouchModel::theModel()->onTouchMoved(pTouch);
}

void GameScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	TouchModel::theModel()->onTouchEnded(pTouch);
}

void GameScene::update(float fDelta)
{
	
}

void GameScene::updateViewPosition(CCPoint &pos)
{
	setPosition(-pos);
	m_handle->setPosition(pos);
}

void GameScene::removeAISnackById(int snackId)
{
	for (auto iter = m_AISnackViews.begin(); iter != m_AISnackViews.end(); iter++)
	{
		auto snack = (*iter);
		if (snack->getSnackId() == snackId)
		{
			m_AISnackViews.erase(iter);
			snack->removeFromParent();
			std::vector<SnackNode *> bodys = AISnackModel::theModel()->getBodys(snackId);
			for (int i = 0; i < bodys.size(); i++)
			{
				addDeadSnackFood(bodys[i]->getPosInView() + bodys[i]->getPosition());
			}
			AISnackModel::theModel()->removeBodys(snackId);
			addAISnackById(snackId);
			break;
		}
	}
}

void GameScene::addFoodNode()
{
	float posX = (m_mapLayer->getContentSize().width - BORDER_SIZE) * CCRANDOM_0_1() - (m_mapLayer->getContentSize().width - BORDER_SIZE) * 0.5f;
	float posY = (m_mapLayer->getContentSize().height - BORDER_SIZE) * CCRANDOM_0_1() - (m_mapLayer->getContentSize().height - BORDER_SIZE) * 0.5f;
	auto foodNode = FoodModel::theModel()->createFood();
	foodNode->setPosition(ccp(posX, posY));
	m_foods->addChild(foodNode);
}

void GameScene::addDeadSnackFood(CCPoint pos)
{
	auto foodNode = FoodModel::theModel()->createFood(2);
	foodNode->setScale(foodNode->getScale() * 1.5f);
	foodNode->setContentSize(foodNode->getContentSize()*1.5f);
	foodNode->setScore(3);
	float posX = CCRANDOM_0_1() * foodNode->getContentSize().width;
	float posY = CCRANDOM_0_1() * foodNode->getContentSize().height;
	foodNode->setPosition(ccp(pos.x + posX, pos.y + posY));
	m_foods->addChild(foodNode);
}

void GameScene::addAISnackById(int snackId)
{
	AISnackView *AIsnackView = AISnackView::create(snackId, m_mapLayer->getContentSize());
	float posX = (m_mapLayer->getContentSize().width - BORDER_SIZE) * CCRANDOM_0_1() - (m_mapLayer->getContentSize().width - BORDER_SIZE) * 0.5f;
	float posY = (m_mapLayer->getContentSize().height - BORDER_SIZE) * CCRANDOM_0_1() - (m_mapLayer->getContentSize().height - BORDER_SIZE) * 0.5f;
	AIsnackView->setPosition(posX, posY);
	addChild(AIsnackView);
	m_AISnackViews.push_back(AIsnackView);
}