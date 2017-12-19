#ifndef __CHESS_H
#define __CHESS_H
#include "cocos2d.h"
USING_NS_CC;
class Chess :public Sprite
{
	CC_SYNTHESIZE(std::string, chessName, ChessName);   //棋子名称
	CC_SYNTHESIZE(int, player, Player);    //哪一方的棋子,0代表红色，1代表黑色
	CC_SYNTHESIZE(Vec2, point, Point);   //棋子在棋盘的坐标
	CC_SYNTHESIZE(int, state, State );   //棋子状态  0 被吃了  1没被吃
public:
	void PositionToPoint(Vec2 position, float spaceX, float spaceY);
	static Chess* createWithSpriteFrameName(const int player, const std::string& spriteFrameName);
};
#endif