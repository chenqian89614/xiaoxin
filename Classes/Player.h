#ifndef _Player_H_
#define _Player_H_

#include "cocos2d.h"
#include "Entity.h"

class Player : public Entity {
public:
	Player();
	~Player();
	CREATE_FUNC(Player);
	virtual bool init();

	void setTiledMap(TMXTiledMap* map);

	/*重写Player的setTagPosition函数*/
	virtual void setTagPosition(int x, int y);
	
	/*让主角小新具有动画效果*/
	void run();

    /*让地图随着主角小新的移动而移动*/
	void setViewPointByPlayer();

	/*跳跃函数*/
	void jump();
private:
	TMXTiledMap* m_map;

	bool m_isJumping;          //标记主角是否正在跳跃

};

#endif
