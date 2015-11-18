#ifndef __MusicFlag_H__
#define __MusicFlag_H__

#include "cocos2d.h"

bool loadMusicFlag()
{
	bool isMusics=UserDefault::getInstance()->getBoolForKey("bool1",true);
	return isMusics;
}

bool loadSoundFlag()
{
	bool isSounds=UserDefault::getInstance()->getBoolForKey("bool2",true);
	return isSounds;
}


#endif
