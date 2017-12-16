#include "Chess.h"
void Chess::PositionToPoint(Vec2 position, float spaceX, float spaceY)
{
	if (spaceX == 0 || spaceY == 0)
	{
		this->point = Vec2(0, 0);
		return;
	}
	this->point = Vec2((int)position.x % (int)spaceX, (int)position.y % (int)spaceY);//%��������߶�Ӧ��������
}
Chess* Chess::createWithSpriteFrameName(const int player,const std::string& chessName)
{
	Chess *chess = new Chess();
	std::string spriteFrameName = chessName;
	spriteFrameName = spriteFrameName.append(".png");
	if (chess&&chess->initWithSpriteFrameName(spriteFrameName))
	{
		chess->setPlayer(player);
		chess->setChessName(chessName);
		chess->autorelease();
		return chess;
	}
	CC_SAFE_DELETE(chess);
	return nullptr;
}