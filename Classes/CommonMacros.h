#define BORDER_SIZE 30 //生成精灵的边缘限制
#define SNACK_SIZE 28  //蛇的大小
#define MOVE_PACE 2.4  //移动步伐
#define MOVE_SPEED 1  //移动速度
#define NEED_FOOD 6  //一个蛇身等于6个食物

#define NOTIFY_VIEWS(_FUNC_ ,...)						\
for (size_t index = 0; index < m_views.size(); ++index) \
{														\
	m_views[index]->_FUNC_(__VA_ARGS__);				\
}
