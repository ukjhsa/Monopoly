#ifndef GAMESTART_H
#define GAMESTART_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class GameStart : public QWidget
{
    Q_OBJECT
public:
    explicit GameStart(QWidget *parent = 0);

signals:
    // Pass signal to Widget to start GameRoom.
    void startGameRoom();

private slots:
    // Player start Game called by newGame button.
    void startGame();

private:
    QLabel *title;
    QPushButton *newGame, *exitGame;

    void init();
};

#endif // GAMESTART_H
