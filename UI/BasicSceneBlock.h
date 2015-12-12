#ifndef BASICSCENEBLOCK_H
#define BASICSCENEBLOCK_H

#include <QLabel>
#include <vector>
#include <string>

namespace Monopoly {
    class Map;
}

class QMouseEvent;

class BasicSceneBlock : public QLabel
{
    Q_OBJECT
public:
    BasicSceneBlock(QWidget *parent = 0, size_t playerSize = 0);

    // Change status.
    void changeStatus(int currentPlayerId,
                      const std::vector<std::string> &allProperty);

signals:
    // Pass signal to Widget to get all map property.
    void displayAllMapProperty(int) const;

public slots:
    // Pass all map property from Widget.
    void passAllMapProperty(int, const std::vector<std::string> &) const;

protected:
    // Mouse press screen will display all map property.
    void mousePressEvent(QMouseEvent *event);

private:
    QLabel *mapLocation, *mapName, *mapOtherProperty;
    std::vector<QLabel *> playerName;

    void init(size_t playerSize);
    std::string getSingleMapProperty(const std::vector<std::string> &allProperty,
                                     const std::string &str) const;
    void changeNameStatus(const std::vector<std::string> &allProperty);
    void changeLocationStatus(const std::vector<std::string> &allProperty);
    void changeWhoStatus(int currentPlayerId,
                         const std::vector<std::string> &allProperty);
    void changeOtherStatus(const std::vector<std::string> &allProperty);
};

#endif // BASICSCENEBLOCK_H
