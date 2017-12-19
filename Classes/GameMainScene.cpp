#include"GameMainScene.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
using namespace ui;

Scene* GameMainScene::createScene()
{
	Scene *scene = Scene::create();
	auto layer = GameMainScene::create();
	scene->addChild(layer);
	return scene;
}
void GameMainScene::creatChess(const std::string& player)
{
	auto winSize = Director::getInstance()->getWinSize();
	auto ScaleFactor = winSize.height / 640;

	std::string name[] = { "che","ma","xiang" ,"si" ,"jiang" ,"si" ,"xiang" ,"ma" ,"che" ,"pao", "pao", "zu", "zu" ,"zu" ,"zu" ,"zu" };
	int x[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 2, 8, 1, 3, 5, 7, 9 };
	int y[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 4, 4, 4, 4, 4 };
	if (player.empty())
	{
		log("error:玩家不知道是哪一方");
		return;
	}
	if (player == "hong_") 
	{
		for (int i = 0; i < 32; i++)
		{
			if (i < 16)
			{
				std::string spriteFrameName = player + name[i];
				Chess* chess = Chess::createWithSpriteFrameName(Player::RED, spriteFrameName);
				chess->setPoint(Vec2(x[i], y[i]));
				chess->setPosition(Vec2((chess->getPoint().x - 1)*this->getSpaceX() + this->getLeftTop().x, (chess->getPoint().y - 1)*this->getSpaceY() + this->getRightBottom().y));
				chess->setScale(0.5 * ScaleFactor);
				chess->setState(ChessExit::YES);    //棋子存在（没被吃）
				/*this->map.insert(i, static_cast<Sprite*>(chess));*/
				Vec2 a = Vec2(x[i], y[i]);
				this->map.insert(std::pair<Vec2, Chess*>(Vec2(x[i], y[i]), chess));
				this->addChild(chess);
			}
			else
			{
				std::string spriteFrameName = std::string("hei_") + name[i % 16];
				Chess* chess = Chess::createWithSpriteFrameName(Player::BLACK, spriteFrameName);
				chess->setPoint(Vec2(x[i % 16], 10 - y[i % 16] + 1));
				chess->setPosition(Vec2((chess->getPoint().x - 1)*this->getSpaceX() + this->getLeftTop().x, (chess->getPoint().y - 1)*this->getSpaceY() + this->getRightBottom().y));
				chess->setScale(0.5 * ScaleFactor);
				chess->setState(ChessExit::YES);
				this->map.insert(std::pair<Vec2, Chess*>(Vec2(x[i % 16], 10 - y[i % 16] + 1), chess));
				this->addChild(chess);
			}
		}
	}
	else if (player == "hei_")
	{
		for (int i = 0; i < 32; i++)
		{
			if (i < 16)
			{
				std::string spriteFrameName = player + name[i];
				Chess* chess = Chess::createWithSpriteFrameName(Player::BLACK, spriteFrameName);
				chess->setPoint(Vec2(x[i], y[i]));
				chess->setPosition(Vec2((chess->getPoint().x - 1)*this->getSpaceX() + this->getLeftTop().x, (chess->getPoint().y - 1)*this->getSpaceY() + this->getRightBottom().y));
				chess->setScale(0.5 * ScaleFactor);
				chess->setState(ChessExit::YES);
				this->map.insert(std::pair<Vec2, Chess*>(Vec2(x[i], y[i]), chess));
				this->addChild(chess);
			}
			else
			{
				std::string spriteFrameName = std::string("hong_") + name[i % 16];
				Chess* chess = Chess::createWithSpriteFrameName(Player::RED, spriteFrameName);
				chess->setPoint(Vec2(x[i % 16], 10 - y[i % 16] + 1));
				chess->setPosition(Vec2((chess->getPoint().x - 1)*this->getSpaceX() + this->getLeftTop().x, (chess->getPoint().y - 1)*this->getSpaceY() + this->getRightBottom().y));
				chess->setScale(0.5 * ScaleFactor);
				chess->setState(ChessExit::YES);
				this->map.insert(std::pair<Vec2, Chess*>(Vec2(x[i % 16], 10 - y[i % 16] + 1), chess));
				this->addChild(chess);
			}
		}
	}
}
void GameMainScene::initChess()
{
	
	if (this->getPlayer() == 0)  //红色
	{
		std::string player = "hong_";
		creatChess(player);
	}
	else
	{
		std::string player = "hei_";
		creatChess(player);
	}
}
bool GameMainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->setPlayer(Player::RED);

	auto rootNode = CSLoader::createNode("csb/GameMainLayer.csb");
	rootNode->setContentSize(visibleSize);
	ui::Helper::doLayout(rootNode);
	this->addChild(rootNode);

	auto node_1 = rootNode->getChildByName("node_1");
	auto node_2 = rootNode->getChildByName("node_2");
	this->setSpaceX(abs(node_1->getPositionX() - node_2->getPositionX()) / (9-1));
	this->setSpaceY(abs(node_1->getPositionY() - node_2->getPositionY()) / (10-1));
	this->setLeftTop(node_1->getPosition());
	this->setRightBottom(node_2->getPosition());
	this->initChess();

	log("x:%f,%f", node_1->getPositionX(), node_2->getPositionX());
	log("y:%f,%f", node_1->getPositionY(), node_2->getPositionY());
	return true;
}