#ifndef _Constant_H_
#define _Constant_H_
#include "cocos2d.h"
using namespace cocos2d;
class Constant{
public:
	static int playerCount;//进入游戏玩家个数
	static int playerId;//当前玩家的id
	static int lastPlayerId;
	static int nextPlayerId;
	//===================准备===============
	static int playerReady;
	static int lastPlayerReady;
	static int nextPlayerReady;
	static int readyNum;//已准备玩家个数
	//============牌
	static int pukeRemainNumber;		//剩余扑克的数量
	static int PUKEARRAY[20];
	static int tempPUKE[20];
	static int lastPukeId[3];//剩余牌的id，即剩余的三张牌
	static int landlordList[3];//每个玩家叫地主的状态，依次对应编号0，1，2
	static int playerCards[20];
	static int lastPlayerCards[20];
	static int nextPlayerCards[20];
	static int EFFECT_ROW_COL[4][15];//音效行列
	static int upCards[54];
	static int tishiCard[20];

	//接收扑克标志位，0代表未接收，1代表接收完毕
	static bool pukeFlag;//扑克标志位，用于判断发牌是否完成
	static bool readyFlag;//用于设置发牌后，ok手势消失
	static bool landlordHadPuke;//地主已经拿到20张牌
	static bool effectFlag;//音效标志位
	static bool musicFlag;//音乐标志位
	static bool isDrawChuPai;//绘制出牌菜单项标志位
	static bool clearLandlordState;//用于清除地主字样即状态

	static int landLordFlag;//金框位置
	static int whoFlag;//地主标志位，初始叫地主的玩家
	static int whoIsLandlord;//判断谁是地主
	//static int playerCardsNum;//当前玩家手牌数目
	static int landlordCount;//叫/抢地主次数计数器
	static int oldGoldFlag;//旧的金币编号
	static int pukeNumber;//扑克数目
	static int beiNum;//接收当前倍数
	static int oldBeiNum;//上一次倍数

	static int landlordListNum;//用于接收3个玩家抢地主前的状态

	static int soundType;//声音的类型
	static int playerCardsCount;//当前玩家手牌数目，id=0;
	static int lastPlayerCardsCount;//上一玩家手牌数目，id=2;
	static int nextPlayerCardsCount;//下一玩家手牌数目，id=1;
	static int upCardsCount;//点起牌的数目
	static int isCanChuPai;//是否可以出牌,0-不能出，1-可以出，2-待定
	static int drawCardsFlag;//绘制玩家手牌的标志位
	static int isBuChu;//用于绘制“不出”的标志位
	static bool isDrawReset;//绘制重选的判断标志
	static bool drawCards; 	//当出牌了 重新画一遍自己的牌
	static bool drawAlreadyCard;//画已出的牌
	//每个玩家出牌的数目
	static int playerLength;//玩家0
	static int lastPlayerLength;//玩家1
	static int nextPlayerLength;//玩家2
	//标志位
	static bool playerCardDraw;
	static bool lastPlayerCardDraw;
	static bool nextPlayerCardDraw;

	//删除叫地主，抢地主的菜单
	static bool deleteMenu;
	//画地主，农民头像
	static bool drawHeadImage;
	//menuitem
	static bool menuItem;
	//是否继续画
	static bool drawLogo;
	//画提示
	static bool drawTiShi;
	//播放出牌音效
	static bool isCanPlayEffect;
	static int effectRow;//接收行
	static int effectCol;//接收列
	//是否提示
	static bool isTishi;
	//胜利
	static bool drawVictory;
	//是谁赢了
	static int victory;
    static bool drawAct;
};
#endif
