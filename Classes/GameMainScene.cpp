#include"GameMainScene.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "Chess.h"
using namespace ui;

Scene* GameMainScene::createScene()
{
	Scene *scene = Scene::create();
	auto layer = GameMainScene::create();
	scene->addChild(layer);
	return scene;
}
void GameMainScene::initChess()
{
	auto winSize = Director::getInstance()->getWinSize();
	auto ScaleFactor = winSize.height / 640;

	std::string name[] = { "che","ma","xiang" ,"si" ,"jiang" ,"si" ,"xiang" ,"ma" ,"che" ,"pao", "pao", "zu", "zu" ,"zu" ,"zu" ,"zu" };
	int x[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 2, 8, 1, 3, 5, 7, 9 };
	int y[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 4, 4, 4, 4, 4 };
	if (this->getPlayer() == 0)  //ºìÉ«
	{
		for (int i = 0; i < 16; i++)
		{
			std::string spriteFrameName = std::string("hong_") + name[i];
			Chess* chess = Chess::createWithSpriteFrameName(this->getPlayer(), spriteFrameName);
			chess->setPoint(Vec2(x[i], y[i]));
			chess->setPosition(Vec2((chess->getPoint().x - 1)*this->getSpaceX() + this->getLeftTop().x, (chess->getPoint().y - 1)*this->getSpaceY() + this->getRightBottom().y));
			chess->setScale(0.5 * ScaleFactor/ ScaleFactor);
			this->addChild(chess);
		}
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
	/*auto chess_1 = Sprite::createWithSpriteFrameName("hong_che.png");
	chess_1->setPosition(node_1->getPosition());
	chess_1->setScale(0.35);
	this->addChild(chess_1);*/
	this->initChess();

	log("x:%f,%f", node_1->getPositionX(), node_2->getPositionX());
	log("y:%f,%f", node_1->getPositionY(), node_2->getPositionY());

	return true;
}