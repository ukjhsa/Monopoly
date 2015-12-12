#ifndef GAMEEND_H
#define GAMEEND_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

namespace Monopoly {
    class Player;
}

class GameEnd : public QWidget
{
    Q_OBJECT
public:
    explicit GameEnd(QWidget *parent = 0);

    // Set winner info.
    void setWinnerInfo(const Monopoly::Player &player);

signals:
    // Pass signal to Widget to start GameStart.
    void startGameStart();

private slots:
    // To return GameStart called by returnGame button.
    void returnGameStart();

private:
    QLabel *winInfo;
    QPushButton *returnGame, *exitGame;

    void init();
};

#endif // GAMEEND_H
