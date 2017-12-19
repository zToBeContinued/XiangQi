#ifndef __HOMESENE_H
#define __HOMESENE_H
#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
USING_NS_CC;
using namespace ui;

class HomeScene :public Layer
{
	CC_SYNTHESIZE(int, layoutTag, LayoutTag);
	CC_SYNTHESIZE(Sprite*, chessleft, ChessLeft);
	CC_SYNTHESIZE(Sprite*, chessright, ChessRight);
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuCallback(Ref* pSender, Widget::TouchEventType type);
	void initUI(Node* node);
	virtual void update(float dt) override;
	void ExitGame();
	bool isChessStop();
	CREATE_FUNC(HomeScene);
};
#endif