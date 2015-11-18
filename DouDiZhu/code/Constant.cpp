#include "Constant.h"
#include "AppMacros.h"

int Constant::playerCount=0;//进入游戏的玩家数目
//玩家ID
int Constant::playerId=-1;//当前玩家id
int Constant::lastPlayerId=-1;//上一家id
int Constant::nextPlayerId=-1;//下一家id
//玩家准备0表示没有准备1表示已准备
int Constant::playerReady=0;//当前玩家准备
int Constant::lastPlayerReady=0;//上一玩家准备
int Constant::nextPlayerReady=0;//下一玩家准备
int Constant::readyNum=0;//准备玩家数目
//===========初始化牌类数组
int Constant::pukeRemainNumber;	//剩余数量
int Constant::upCards[54];//锁定每个牌的编号
int Constant::tishiCard[20];
int	Constant::PUKEARRAY[20]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
								-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int	Constant::tempPUKE[20]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
								-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int Constant::lastPukeId[3]={-1,-1,-1};			//底牌的ID
int Constant::landlordList[3]={-1,-1,-1};		//每个玩家叫地主的状态，依次对应编号0，1，2
//用于接收每个玩家出牌的内容
int	Constant::playerCards[20]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
								-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int	Constant::lastPlayerCards[20]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
								-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int	Constant::nextPlayerCards[20]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
								-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

int Constant::EFFECT_ROW_COL[4][15]={
										{DAN_1,DAN_2,DAN_3,DAN_4,DAN_5,DAN_6,DAN_7,DAN_8,DAN_9,DAN_10,DAN_11,DAN_12,DAN_13,DAN_14,DAN_15},
										{DUI_1,DUI_2,DUI_3,DUI_4,DUI_5,DUI_6,DUI_7,DUI_8,DUI_9,DUI_10,DUI_11,DUI_12,DUI_13,-1,-1},
										{SAN_1,SAN_2,SAN_3,SAN_4,SAN_5,SAN_6,SAN_7,SAN_8,SAN_9,SAN_10,SAN_11,SAN_12,SAN_13,-1,-1},
										{FEI_JI,LIAN_DUI,SAN_DAI_YI,SAN_DAI_DUI,SHUN_ZI,SI_DAI_ER,SI_DAI_DUI,WANG_ZHA,ZHA_DAN,BU_YAO,-1,-1,-1,-1,-1}
									};

bool Constant::pukeFlag = false;//扑克标志位，用于判断是否牌发完
bool Constant::readyFlag = false;//用于设置发牌后，ok手势消失
bool Constant::landlordHadPuke = false;//地主已经拿到20张牌
bool Constant::clearLandlordState = false;//用于清除地主字样
bool Constant::effectFlag = true;//音效标志位
bool Constant::musicFlag = true;//音乐标志位	背景音乐
bool Constant::isDrawChuPai = false;//绘制出牌菜单项标志位,当可以出牌时设置为true
bool Constant::isDrawReset = false;//绘制重选的判断标志
bool Constant::isCanPlayEffect = false;//默认不可以播放出牌音效

int Constant::whoFlag = -1;//初始叫地主的玩家,即当前玩家牌权
int Constant::whoIsLandlord = -1;//判断谁是最后的地主
int Constant::landlordCount = 0;//地主计数器
int Constant::oldGoldFlag = -1;//记录每次金框的编号
int Constant::pukeNumber = 0;//扑克数目
int Constant::beiNum = 15;//当前倍数,默认为15倍
int Constant::oldBeiNum = 15;//上一次的倍数

int Constant::landlordListNum = -1;//用于接收3个玩家抢地主前的状态
int Constant::soundType = -1;//声音的类型，播放抢地主音效
//绘制玩家手牌数目
int Constant::playerCardsCount = 17;//当前玩家手牌数目，id=0;
int Constant::lastPlayerCardsCount = 17;//上一玩家手牌数目，id=2;
int Constant::nextPlayerCardsCount = 17;//下一玩家手牌数目，id=1;
int Constant::upCardsCount = 0;//当前有牌权的玩家点起牌的数目

int Constant::isCanChuPai = 0;//是否可以出牌,0-不能出，1-可以出，
int Constant::drawCardsFlag = 0;//绘制玩家手牌的标志位,0-不绘制，1-绘制
bool Constant::drawCards=false;	//重新画一遍牌
bool Constant::drawAlreadyCard=false;//画已出的牌
int Constant::isBuChu = 0;//用于绘制“不出”的标志位,0-绘制，1-不绘制

//每个玩家的出牌数目 0  1  2
int Constant::playerLength = 0;
int Constant::lastPlayerLength = 0;
int Constant::nextPlayerLength = 0;
//标志位  是否画已出的牌
bool Constant::playerCardDraw=true;
bool Constant::lastPlayerCardDraw=true;
bool Constant::nextPlayerCardDraw=true;
//删除叫地主，抢地主menu
bool Constant::deleteMenu=false;
bool Constant::menuItem=false;
//画地主头像，农民头像
bool Constant::drawHeadImage=false;
//画不画logo
bool Constant::drawLogo=true;
//画提示
bool Constant::drawTiShi=false;
//是否提示
bool Constant::isTishi=true;
//接收音效数组的行列
int Constant::effectRow = -1;
int Constant::effectCol = -1;
//胜利标志位
bool Constant::drawVictory=false;
//最后是谁赢了
int Constant::victory=-1;
bool Constant::drawAct=false;
