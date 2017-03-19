#ifndef __FOOD_MODEL_H__
#define __FOOD_MODEL_H__

#include "cocos2d.h"

class FoodNode;
class FoodModel
{
public:
	static FoodModel *theModel();
	~FoodModel(){}

public:
	FoodNode *createFood(int color = -1);
	void removeFood(FoodNode *node);

	std::vector<FoodNode *> getFoods(cocos2d::CCPoint pos);

private:
	FoodModel();

private:
	std::vector<FoodNode *> m_foods;
};

#endif