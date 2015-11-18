#ifndef _DialogLayer_h
#define _DialogLayer_h

#include "cocos2d.h"
#include "GameSceneManager.h"
#include "GameLayer.h"

using namespace std;
using namespace cocos2d;

class DialogLayer: public LayerColor
{
public:
	//声音播放标志位
	static bool isMusic;
	//粒子效果标志位
	static bool isParticle;
    //主菜单界面
	Menu *m_pMenu;
    //按钮是否被点击的标志位
    bool m_bTouchedMenu;
    //声明叉号1-2的精灵对象
    Sprite* x_1;
    Sprite* x_2;
    //叉号标志
    bool xx_1;
    bool xx_2;
    //声明场景的所属管理者
    GameSceneManager *man;

public:
	//初始化的方法
    virtual bool init();
    //初始化
    void initDialog();
    //返回主菜单界面的方法
    void homeSence(Object* pSender);
    //粒子效果菜单按钮的回掉方法
    void parused();
    //声音菜单按钮的回掉方法
    void sounded();
    //继续游戏按钮的单机回调方法
    void menuCallbackContinueGame(Object *pSender);

    CREATE_FUNC(DialogLayer);
};

#endif
