#include <QLabel>
#include <QFont>
#include <QComboBox>
#include <QPushButton>
#include <vector>
#include <QLineEdit>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include "../Monopoly/GameConstant.h"
#include "GameRoom.h"

using namespace std;

GameRoom::GameRoom(QWidget *parent) :
    QWidget(parent)
{
    init();
}

void GameRoom::init()
{
    this->resize(600, 600);
    // Delete when closed.
    this->setAttribute(Qt::WA_DeleteOnClose);

    helpNumberPlayer = new QLabel("Please choose the number of players.", this);
    helpNumberPlayer->setFont(QFont("default", 15, QFont::DemiBold));
    helpNumberPlayer->resize(350, 50);
    helpNumberPlayer->setGeometry(100, 25,
                                  helpNumberPlayer->width(),
                                  helpNumberPlayer->height());
    helpNumberPlayer->setAlignment(Qt::AlignCenter);

    numberPlayer = new QComboBox(this);
    numberPlayer->setFont(QFont("default", 15, QFont::DemiBold));
    numberPlayer->resize(50, 35);
    numberPlayer->setGeometry(helpNumberPlayer->x() + helpNumberPlayer->width(),
                              25,
                              numberPlayer->width(), numberPlayer->height());
    for (int number = Monopoly::GameConstant::MIN_NUMBER_PLAYER;
         number <= Monopoly::GameConstant::MAX_NUMBER_PLAYER; ++number) {
        QStringList strList;
        strList << QString::number(number);
        numberPlayer->addItems(strList);    // 1, 2, 3, 4
    }

    decisionNumberPlayer = new QPushButton("OK", this);
    decisionNumberPlayer->setFont(QFont("default", 15, QFont::DemiBold));
    decisionNumberPlayer->resize(50, 35);
    decisionNumberPlayer->setGeometry(numberPlayer->x() + numberPlayer->width(),
                                      25,
                                      decisionNumberPlayer->width(),
                                      decisionNumberPlayer->height());
    connect(decisionNumberPlayer, SIGNAL(clicked()),
            this, SLOT(choosePlayerAndMap()));
}

void GameRoom::choosePlayerAndMap()
{
    // Disable the UI of choosing the number of player.
    numberPlayer->setEnabled(false);
    decisionNumberPlayer->setEnabled(false);

    // Show Map UI.
    helpMap = new QLabel("Map:", this);
    helpMap->setFont(QFont("default", 15, QFont::DemiBold));
    helpMap->resize(100, 50);
    helpMap->setGeometry(25, 400, helpMap->width(), helpMap->height());
    helpMap->setAlignment(Qt::AlignCenter);
    helpMap->show();
    imageMap = new QLabel("map.dat", this);
    imageMap->setFont(QFont("default", 15, QFont::DemiBold));
    imageMap->resize(100, 100);
    imageMap->setGeometry(helpMap->x(), helpMap->y()+helpMap->height(),
                          imageMap->width(), imageMap->height());
    imageMap->setStyleSheet("QLabel { border: 2px solid green; }");
    imageMap->setAlignment(Qt::AlignCenter);
    imageMap->show();

    // According to the number of players to generate edit frame for input player's name.
    helpPlayerName.resize(numberPlayer->currentText().toUInt());
    editPlayerName.resize(numberPlayer->currentText().toUInt());
    for (unsigned i = 0; i < numberPlayer->currentText().toUInt(); ++i) {
        helpPlayerName[i] =
            new QLabel("Input player " + QString::number(i+1) + "'s name:", this);
        helpPlayerName[i]->setFont(QFont("default", 15, QFont::DemiBold));
        helpPlayerName[i]->setGeometry(150, 150 + i * 100, 350, 50);
        helpPlayerName[i]->setAlignment(Qt::AlignCenter);
        helpPlayerName[i]->show();

        editPlayerName[i] = new QLineEdit(this);
        editPlayerName[i]->setText(QChar('A'+i));
        editPlayerName[i]->setFont(QFont("default", 15, QFont::DemiBold));
        editPlayerName[i]->setGeometry(150, 200 + i * 100, 350, 50);
        editPlayerName[i]->show();
    }
    // Click "OK" button to save players' name and map.
    decisionPlayerAndMap = new QPushButton("OK", this);
    decisionPlayerAndMap->setFont(QFont("default", 15, QFont::DemiBold));
    decisionPlayerAndMap->setGeometry(500,
                                      200 + (numberPlayer->currentText().toInt()-1) * 100,
                                      50, 50);
    decisionPlayerAndMap->show();
    connect(decisionPlayerAndMap, SIGNAL(clicked()), this, SLOT(checkPlayerAndMap()));
}

void GameRoom::checkPlayerAndMap()
{
    if (isPlayerNameNotNull() && isMapExist()) {
        storePlayerAndMap();
    }
    else {
        QMessageBox box(QMessageBox::Warning, "Warning",
                        "The players' name is null or the map file doesn't exist!!", QMessageBox::Ok, this);
        box.exec();
    }
}

bool GameRoom::isPlayerNameNotNull()
{
    for (auto it = editPlayerName.begin(); it != editPlayerName.end(); ++it) {
        if ((*it)->text().isEmpty()) {
            return false;
        }
    }
    return true;
}

bool GameRoom::isMapExist()
{
    return QFile::exists(imageMap->text());
}

void GameRoom::storePlayerAndMap()
{
    // Create players by calling Widget's slot.
    for (unsigned i = 0; i < numberPlayer->currentText().toUInt(); ++i) {
        createPlayer(i, editPlayerName[i]->text().toLocal8Bit().constData());
    }
    // Load map by calling Widget's slot.
    loadMap(imageMap->text().toLocal8Bit().constData());
    // Store data finished.
    // Close self.
    this->close();
    // Start GameScene by calling Widget's slot.
    startGameScene();
}
