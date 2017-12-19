#ifndef __CHESS_H
#define __CHESS_H
#include "cocos2d.h"
USING_NS_CC;
class Chess :public Sprite
{
	CC_SYNTHESIZE(std::string, chessName, ChessName);   //��������
	CC_SYNTHESIZE(int, player, Player);    //��һ��������,0�����ɫ��1�����ɫ
	CC_SYNTHESIZE(Vec2, point, Point);   //���������̵�����
	CC_SYNTHESIZE(int, state, State );   //����״̬  0 ������  1û����
public:
	void PositionToPoint(Vec2 position, float spaceX, float spaceY);
	static Chess* createWithSpriteFrameName(const int player, const std::string& spriteFrameName);
};
#endif