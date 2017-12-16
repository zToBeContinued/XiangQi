#ifndef __GAMEMAINSCENE_H
#define __GAMEMAINSCENE_H
#include "cocos2d.h"
USING_NS_CC;
class GameMainScene :public Layer
{
	CC_SYNTHESIZE(float, spaceX, SpaceX); //棋盘X轴格子长度
	CC_SYNTHESIZE(float, spaceY, SpaceY); //棋盘Y轴格子长度
	CC_SYNTHESIZE(Vec2, leftTop, LeftTop);//棋盘左上角的position
	CC_SYNTHESIZE(Vec2, rightBottom, RightBottom);//棋盘右下角的position
	CC_SYNTHESIZE(int, player, Player);   //哪一方的棋子,0代表红色，1代表黑色
public:
	static Scene* createScene();
	virtual bool init();
	enum Player { RED = 0, BLACK };
	void initChess();

	CREATE_FUNC(GameMainScene);
};
#endif