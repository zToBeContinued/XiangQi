#ifndef __GAMEMAINSCENE_H
#define __GAMEMAINSCENE_H
#include "cocos2d.h"
#include "Chess.h"
USING_NS_CC;
class GameMainScene :public Layer
{
	CC_SYNTHESIZE(float, spaceX, SpaceX); //����X����ӳ���
	CC_SYNTHESIZE(float, spaceY, SpaceY); //����Y����ӳ���
	CC_SYNTHESIZE(Vec2, leftTop, LeftTop);//�������Ͻǵ�position
	CC_SYNTHESIZE(Vec2, rightBottom, RightBottom);//�������½ǵ�position
	CC_SYNTHESIZE(int, player, Player);   //��һ��������,0�����ɫ��1�����ɫ
	std::map<Vec2, Chess*> map;
public:
	static Scene* createScene();
	virtual bool init();
	enum Player { RED = 0, BLACK };
	enum ChessExit { NO = 0, YES };
	void creatChess(const std::string& player);
	void initChess();

	CREATE_FUNC(GameMainScene);
};
#endif