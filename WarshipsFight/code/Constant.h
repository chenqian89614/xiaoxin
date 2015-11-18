#ifndef _Constant_H_
#define _Constant_H_
#include "cocos2d.h"
using namespace cocos2d;
class Constant
{
public :
	//通关数
	static std::string LEVELNUM ;
	//是否为第一次进入游戏
	static std::string ISFIRSTENTER ;
	//杀敌数
	static std::string SHADISHU;

	//玩家金钱
	static std::string COUNTGOLD;

	//船只导弹等级
	static std::string SHIPZERO ;
	static std::string SHIPONE ;
	static std::string SHIPTWO ;
	static std::string SHIPTHREE ;
	static std::string SHIPFOUR ;

	//胜利数
	static std::string WINCOUNT;
	//失败数
	static std::string LOSECOUNT;
	//获得金钱数
	static std::string GETGOLDCOUNT;

	//关数的成绩
	static std::string LEVEL1;
	static std::string LEVEL2;
	static std::string LEVEL3;
	static std::string LEVEL4;

	//声音
	static std::string BGSY;//0----正常播放，1-----暂停播放
	static std::string YSSY;


};
#endif
