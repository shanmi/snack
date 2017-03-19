#ifndef __MAP_LAYER_H__
#define __MAP_LAYER_H__
#include "cocos2d.h"

#define ROWS_SIZE 13 * 3
#define COlUMNS_SIZE 24 * 3

#define SCREEN_WIDTH 800
#define SCREEN_HEIGH 480

#define SCALEFACTOR 0.88f

class MapLayer : public cocos2d::CCNode
{
public:
	static MapLayer *create(int row, int column);
	virtual bool init();

private:
	MapLayer(int row, int column);
	~MapLayer();

private:
	int m_row;
	int m_column;
};

#endif