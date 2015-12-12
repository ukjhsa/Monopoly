#ifndef SCENE_H
#define SCENE_H

#include <QScrollArea>
#include <vector>
#include "BasicSceneBlock.h"

namespace Monopoly {
	class WorldMap;
}

class Scene : public QScrollArea
{
    Q_OBJECT
public:
	explicit Scene(QWidget *parent, int width, int height, size_t mapSize, size_t playerSize);

	// Change Map status.
	void changeMapStatus(int currentPlayerId, const Monopoly::WorldMap &worldMap);
signals:
	// Pass signal from BasicSceneBlock to Widget to get all map property.
	void displayAllMapProperty(int) const;
	// Pass all map property from Widget to BasicSceneBlock.
	void passAllMapProperty(int, const std::vector<std::string> &) const;
public slots:

private:
	QWidget *allBackground;
	std::vector<BasicSceneBlock *> basicBlocks;

	void init(int width, int height);
	void initMapBlock(size_t playerSize);
};

#endif // SCENE_H
