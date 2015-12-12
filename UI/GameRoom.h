#ifndef GAMEROOM_H
#define GAMEROOM_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <vector>
#include <QLineEdit>

class GameRoom : public QWidget
{
    Q_OBJECT
public:
    explicit GameRoom(QWidget *parent = 0);

signals:
    // Pass player's info to Widget to add players.
    void createPlayer(unsigned, const char *);
    // Pass map file name to Widget to load maps.
    void loadMap(const char *);
    // Pass signal to Widget to start GameScene.
    void startGameScene();

private slots:
    // Player input names and choose map called by decisionNumberPlayer button.
    void choosePlayerAndMap();
    // To check players' name and map's file name called by decisionPlayerAndMap button.
    void checkPlayerAndMap();

private:
    // UI of choosing the number of player.
    QLabel *helpNumberPlayer;
    QComboBox *numberPlayer;
    QPushButton *decisionNumberPlayer;
    // UI of map.
    QLabel *helpMap;
    QLabel *imageMap;
    // UI of player.
    std::vector<QLabel *> helpPlayerName;
    std::vector<QLineEdit *> editPlayerName;
    QPushButton *decisionPlayerAndMap;

    void init();
    // Is players' name not null.
    bool isPlayerNameNotNull();
    // Is map file exist.
    bool isMapExist();
    // Add players and lod maps by calling signal to Widget, and then close self.
    void storePlayerAndMap();
};

#endif // GAMEROOM_H
