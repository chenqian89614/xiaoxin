#ifndef __MusicLoad_H__
#define __MusicLoad_H__

#include "AppMacros.h"

using namespace cocos2d;
using namespace std;

void LoadMusic(string instrument, int num)
{
	string number;
	if(num<10)
	{
		number  = "0" + StringUtils::format("%d", num);
	}else
	{
		number = StringUtils::format("%d", num);
	}
	string route = music_RESOURE_PATH + instrument + number + ".mp3";
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(route.c_str());
}

void RemoveMusic(string instrument)
{
	string number;
	for(int i=0; i<38; i++)
	{
		if(i<10)
		{
			number = "0" + StringUtils::format("%d", i);
		}else
		{
			number = StringUtils::format("%d", i);
		}
		string route = music_RESOURE_PATH + instrument + number + ".mp3";
		CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(route.c_str());
	}
}

#endif
