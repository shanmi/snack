#include "MapLayer.h"

USING_NS_CC;

MapLayer* MapLayer::create(int row, int column)
{
	MapLayer *map = new MapLayer(row, column);
	map->autorelease();
	map->init();
	return map;
}

MapLayer::MapLayer(int row, int column)
{
	m_row = row;
	m_column = column;
}

MapLayer::~MapLayer()
{

}

bool MapLayer::init()
{

	CCSpriteBatchNode *node = CCSpriteBatchNode::create("map_01.png");
	static const float kSpacing = 0.8f;
	float curX = kSpacing;
	float curY = kSpacing;
	float maxWidth = 0;
	float maxHeight = 0;
	CCSize totalSize(0, 0);
	for (int row = 0; row < ROWS_SIZE; ++row)
	{
		for (int col = 0; col < COlUMNS_SIZE; ++col)
		{
			auto grid = CCSprite::create("map_01.png");
			grid->setScale(SCALEFACTOR);
			grid->setAnchorPoint(ccp(0, 0));
			auto size = grid->getContentSize() * SCALEFACTOR;
			node->addChild(grid);
			grid->setPosition(ccp(curX, curY));
			if (col == 3)
			{
				curX += size.width + 1;
			}
			else
			{
				curX += size.width + kSpacing;
			}
			if (maxHeight < size.height)
			{
				maxWidth = size.width;
				maxHeight = size.height;
			}
		}
		curX = kSpacing;
		curY += maxHeight + kSpacing;
	}
	totalSize = ccp((maxWidth + kSpacing)*COlUMNS_SIZE, (maxHeight + kSpacing)*ROWS_SIZE);
	node->setContentSize(totalSize);
	addChild(node, 1);
	node->setPosition(ccp(0, 0));

	CCLayerColor *color = CCLayerColor::create(ccc4(208, 208, 217, 208));
	color->setPosition(ccp(0, 0));
	color->setContentSize(totalSize+ccp(10, 10));
	addChild(color, 0);

	setContentSize(totalSize);
	setAnchorPoint(ccp(0.5f, 0.5f));

	return true;
}