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

	/*��дPlayer��setTagPosition����*/
	virtual void setTagPosition(int x, int y);
	
	/*������С�¾��ж���Ч��*/
	void run();

    /*�õ�ͼ��������С�µ��ƶ����ƶ�*/
	void setViewPointByPlayer();

	/*��Ծ����*/
	void jump();
private:
	TMXTiledMap* m_map;

	bool m_isJumping;          //��������Ƿ�������Ծ

};

#endif
