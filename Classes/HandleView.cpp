#include "HandleView.h"
#include "HandleModel.h"

USING_NS_CC;

HandleView *HandleView::create()
{
	HandleView *handle = new HandleView();
	handle->autorelease();
	handle->init();
	return handle;
}

HandleView::HandleView()
{

}

HandleView::~HandleView()
{

}

void HandleView::onEnter()
{
	CCNode::onEnter();
	TouchModel::theModel()->addView(this);
}

void HandleView::onExit()
{
	CCNode::onExit();
	TouchModel::theModel()->removeView(this);
}

bool HandleView::init()
{
	auto size = CCDirector::sharedDirector()->getWinSize();

	m_circleArea = CCSprite::create("circleArea.png");
	m_circleArea->setPosition(ccp(m_circleArea->getContentSize().width, m_circleArea->getContentSize().height));
	addChild(m_circleArea);

	m_handle = CCSprite::create("handle.png");
	m_handle->setPosition(m_circleArea->getPosition());
	addChild(m_handle);

	setContentSize(size);

	return true;
}

void HandleView::onTonchBegan(cocos2d::CCTouch *pTouch)
{
	handleMove(pTouch);
}

void HandleView::onTouchMoved(cocos2d::CCTouch *pTouch)
{
	handleMove(pTouch);
}

void HandleView::onTouchEnded(cocos2d::CCTouch *pTouch)
{
	m_handle->setPosition(m_circleArea->getPosition());
}

void HandleView::handleMove(cocos2d::CCTouch *pTouch)
{
	CCPoint nextPos;
	CCPoint beginPos = m_circleArea->getPosition();
	float radius = m_circleArea->getContentSize().width;

	float curAngle = HandleModel::theModel()->getDegreeTwoPoints(m_circleArea->getPosition(), pTouch->getLocation());
	float const_pi = 180.0f / (float)M_PI;
	float distance = (90 - curAngle) / const_pi;
	float moveX = cos(distance)*(radius - m_handle->getContentSize().width)*0.5f;
	float moveY = sin(distance)*(radius - m_handle->getContentSize().height)*0.5f;
	nextPos.x = beginPos.x + moveX;
	nextPos.y = beginPos.y + moveY;

	m_handle->setPosition(nextPos);
	float degree = HandleModel::theModel()->getDegreeTwoPoints(beginPos, nextPos);
	HandleModel::theModel()->setAngle(degree);
}