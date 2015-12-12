#include <vector>
#include "BasicSceneBlock.h"
#include "../Monopoly/WorldMap.h"
#include "Scene.h"

Scene::Scene(QWidget *parent, int width, int height, size_t mapSize, size_t playerSize)
	: QScrollArea(parent), basicBlocks(mapSize)
{
	init(width, height);
	initMapBlock(playerSize);
}

void Scene::init(int width, int height)
{
	this->resize(width, height);

	allBackground = new QWidget(this);
}

void Scene::initMapBlock(size_t playerSize)
{
	for (size_t i = 0; i < basicBlocks.size(); ++i) {
		basicBlocks[i] = new BasicSceneBlock(allBackground, playerSize);
		basicBlocks[i]->setGeometry((i%3)*basicBlocks[i]->width(), (i/3)*basicBlocks[i]->height(),
							   basicBlocks[i]->width(), basicBlocks[i]->height());
		connect(basicBlocks[i], SIGNAL(displayAllMapProperty(int)), this, SIGNAL(displayAllMapProperty(int)));
		connect(this, SIGNAL(passAllMapProperty(int, std::vector<std::string>)), basicBlocks[i], SLOT(passAllMapProperty(int, std::vector<std::string>)));
	}
	// Adjust scrollArea's background size.
	allBackground->adjustSize();
	this->setWidget(allBackground);
}

void Scene::changeMapStatus(int currentPlayerId, const Monopoly::WorldMap &worldMap)
{
	for (size_t i = 0; i < worldMap.size(); ++i) {
		basicBlocks[i]->changeStatus(currentPlayerId, worldMap[i]->getAllMapProperty());
	}
}
