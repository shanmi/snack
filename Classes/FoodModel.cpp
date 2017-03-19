#include "FoodModel.h"
#include "FoodNode.h"
#include "SnackView.h"

#include <algorithm>

USING_NS_CC;

FoodModel::FoodModel()
{

}

FoodModel *FoodModel::theModel()
{
	static FoodModel model;
	return &model;
}

FoodNode *FoodModel::createFood(int color)
{
	if (color == -1)
	{
		color = rand() % cColor8 + 1;
	}
	auto foodNode = FoodNode::create(color);
	m_foods.push_back(foodNode);
	return foodNode;
}

void FoodModel::removeFood(FoodNode *node)
{
	auto iter = find(m_foods.begin(), m_foods.end(), node);
	if (iter != m_foods.end())
	{
		node->removeFromParent();
		m_foods.erase(iter);
	}
}

std::vector<FoodNode *> FoodModel::getFoods(CCPoint pos)
{
	std::vector<FoodNode *> neighbours;
	for (int i = 0; i < m_foods.size(); i++)
	{
		float distance = abs(ccpDistance(pos, m_foods[i]->getPosition()));
		if (distance < SNACK_SIZE)
		{
			neighbours.push_back(m_foods[i]);
		}
	}
	return neighbours;
}