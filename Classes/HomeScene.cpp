#include "HomeScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameMainScene.h"

Scene* HomeScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HomeScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HomeScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto rootNode = CSLoader::createNode("csb/Home_Background.csb");
	rootNode->setContentSize(visibleSize);
	ui::Helper::doLayout(rootNode);
	this->initUI(rootNode);
	this->addChild(rootNode);

	return true;
}

void HomeScene::initUI(Node* node)
{
	auto winSize = Director::getInstance()->getWinSize();
	auto ScaleFactor = winSize.height / 640;

	for (int i = 1; i < 5; i++)
	{
		//获取layout控件并注册触摸事件
		auto str_layout = String::createWithFormat("layout_%d", i);
		auto layout = static_cast<Layout*>(node->getChildByName(str_layout->getCString()));
		layout->addTouchEventListener(CC_CALLBACK_2(HomeScene::menuCallback, this));
		layout->setTag(i);
	}

	auto children = node->getChildren();
	for (auto &child : children)
	{
		if (child->getName() == "background" || child->getName() == "bg_title" || child->getName() == "layout_1" || child->getName() == "layout_2" || child->getName() == "layout_3" || child->getName() == "layout_4")
			;
		else
			child->setScale(child->getScale()*ScaleFactor);
	}
}
bool HomeScene::isChessStop()
{
	//第一次点击的时候是空值，没动
	if (this->_chess_left == nullptr&& this->_chess_right == nullptr)
		return true;
	//如果圆心距离大于等于圆的直径就是碰撞停止了
	if (this->_chess_left->getContentSize().width * this->_chess_left->getScale() >= abs(this->_chess_left->getPositionX() - this->_chess_right->getPositionX()))
		return true;
	return false;
}
void HomeScene::menuCallback(Ref* pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		//根据layout的tag获取相对应的text控件和左右两边的棋子精灵
		auto layout = (Layout*)pSender;
		int tag = layout->getTag();
		auto text = String::createWithFormat("text_%d", tag);
		auto name_chess_left = String::createWithFormat("chess_%d", 2 * tag - 1);
		auto name_chess_right = String::createWithFormat("chess_%d", 2 * tag);
		//获取精灵
		auto parent = layout->getParent();
		auto text_node = parent->getChildByName(text->getCString());
		auto chess_left = (Sprite*)parent->getChildByName(name_chess_left->getCString());
		auto chess_right = (Sprite*)parent->getChildByName(name_chess_right->getCString());
		if (isChessStop())
		{
			this->_layoutTag = tag;
			this->_chess_left = chess_left;
			this->_chess_right = chess_right;

			auto toCenter = MoveTo::create(1, text_node->getPosition());   //创建移动到X轴中间的动作
			auto clockwiseSense = RotateBy::create(1, 720);   //顺时针方向旋转动作
			auto counterClockwise = clockwiseSense->reverse();   //逆时针方向旋转动作
			auto leftToright = Spawn::create(toCenter, clockwiseSense, NULL);
			auto rightToleft = Spawn::create(toCenter->clone(), counterClockwise, NULL);
			//text隐藏
			parent->getChildByName(text->getCString())->setVisible(false);
			chess_left->runAction(RepeatForever::create(leftToright));
			chess_right->runAction(RepeatForever::create(rightToleft));
			this->scheduleUpdate();//启动定时器
		}
	}
}
void HomeScene::update(float dt)
{
	if (isChessStop())
	{
		this->_chess_left->stopAllActions();
		this->_chess_right->stopAllActions();
		if (this->_layoutTag == 4)
		{
			this->unscheduleUpdate();
			this->ExitGame();
		}
		else if (this->_layoutTag == 1)
		{
			this->unscheduleUpdate();
			auto scene = GameMainScene::createScene();
			Director::getInstance()->replaceScene(TransitionSplitCols::create(0.5,scene));
		}
	}
}
void HomeScene::ExitGame()
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}