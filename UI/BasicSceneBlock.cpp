#include <QLabel>
#include <QString>
#include <QFont>
#include <QMouseEvent>
#include <QMessageBox>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "../Monopoly/MapProperty.h"
#include "../Monopoly/GameConstant.h"
#include "BasicSceneBlock.h"

using namespace std;

BasicSceneBlock::BasicSceneBlock(QWidget *parent, size_t playerSize)
    : QLabel(parent), playerName(playerSize)
{
    init(playerSize);
}

void BasicSceneBlock::init(size_t playerSize)
{
    this->resize(216, 200);
    this->setStyleSheet("QLabel { border: 4px solid green; }");

    mapLocation = new QLabel(this);
    mapLocation->setFont(QFont("default", 15, QFont::DemiBold));
    mapLocation->setGeometry(0, 0, 50, 50);
    mapLocation->setAlignment(Qt::AlignCenter);
    mapLocation->setStyleSheet("QLabel { border: 2px solid dimgray; }");

    mapName = new QLabel(this);
    mapName->setFont(QFont("default", 15, QFont::DemiBold));
    mapName->setGeometry(mapLocation->width(), 0,
                         this->width()-mapLocation->width(), 50);
    mapName->setAlignment(Qt::AlignCenter);
    mapName->setStyleSheet("QLabel { border: 2px solid dimgray; }");

    mapOtherProperty = new QLabel(this);
    mapOtherProperty->setFont(QFont("default", 14, QFont::DemiBold));
    mapOtherProperty->setGeometry(0, mapLocation->height(), this->width(), 100);
    mapOtherProperty->setAlignment(Qt::AlignCenter);
    mapOtherProperty->setStyleSheet("QLabel { border: 2px solid dimgray; }");

    for (size_t i = 0; i < playerSize; ++i) {
        playerName[i] = new QLabel(this);
        playerName[i]->setFont(QFont("default", 15, QFont::DemiBold));
        playerName[i]->setGeometry(i * this->width()/playerSize,
                                   mapOtherProperty->y()+mapOtherProperty->height(),
                                   this->width()/playerSize, 50);
        playerName[i]->setAlignment(Qt::AlignCenter);
        playerName[i]->setStyleSheet("QLabel { border: 2px solid dimgray; }");
    }
}

void BasicSceneBlock::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // Pass signal to Widget to get all map property.
        this->displayAllMapProperty(mapLocation->text().toInt());
    }
}

void BasicSceneBlock::passAllMapProperty(int location,
                                         const vector<string> &allProperty) const
{
    if (location == mapLocation->text().toInt()) {
        // Get all property.
        string name = getSingleMapProperty(allProperty, Monopoly::MapProperty::NAME);
        string location = getSingleMapProperty(allProperty, Monopoly::MapProperty::LOCATION);
        //string whoishere = getSingleMapProperty(allProperty, Monopoly::MapProperty::WHOISHERE);
        string purchasePrice = getSingleMapProperty(allProperty, Monopoly::MapProperty::PURCHASE_PRICE);
        string host = getSingleMapProperty(allProperty, Monopoly::MapProperty::HOST);
        string fine = getSingleMapProperty(allProperty, Monopoly::MapProperty::FINE);
        string level = getSingleMapProperty(allProperty, Monopoly::MapProperty::LEVEL);
        string upgradePrice = getSingleMapProperty(allProperty, Monopoly::MapProperty::UPGRADE_PRICE);
        string upgradeFine = getSingleMapProperty(allProperty, Monopoly::MapProperty::UPGRADE_FINE);

        // Append all property into "propertyText".
        string propertyText;
        propertyText.append(Monopoly::MapProperty::NAME + ": " + name + "\n");
        propertyText.append(Monopoly::MapProperty::LOCATION + ": " + location + "\n");
        //propertyText.append(Monopoly::MapProperty::WHOISHERE + ": " + whoishere + "\n");

        // If it is buyable map.
        if ( ! purchasePrice.empty()) {
            propertyText.append(Monopoly::MapProperty::PURCHASE_PRICE + ": " + purchasePrice + "\n");
            propertyText.append(Monopoly::MapProperty::HOST + ": " + host + "\n");
            propertyText.append(Monopoly::MapProperty::FINE + ": " + fine + "\n");
        }
        // If it is upgradable map.
        if (! upgradePrice.empty()) {
            propertyText.append(Monopoly::MapProperty::LEVEL + ": " + level + "\n");
            propertyText.append(Monopoly::MapProperty::UPGRADE_PRICE + ": " + upgradePrice + "\n");
            propertyText.append(Monopoly::MapProperty::UPGRADE_FINE + ": " + upgradeFine + "\n");
        }

        // Show MessageBox of all map property.
        QMessageBox box(QMessageBox::Information, "Map Information",
                        QString::fromLocal8Bit(propertyText.c_str()), QMessageBox::Ok, 0);
        box.setStyleSheet("QLabel {border: none}");
        box.exec();
    }
}

string BasicSceneBlock::getSingleMapProperty(const vector<string> &allProperty,
                                             const string &str) const
{
    string content;
    for (auto itProperty = allProperty.begin();
         itProperty != allProperty.end(); ++itProperty) {
        stringstream ss(*itProperty);
        string type;
        ss >> type;
        if (type == str) {
            ss >> content;
            break;
        }
    }
    return content;
}

void BasicSceneBlock::changeStatus(int currentPlayerId,
                                   const vector<string> &allProperty)
{
    changeNameStatus(allProperty);
    changeLocationStatus(allProperty);
    changeWhoStatus(currentPlayerId, allProperty);
    changeOtherStatus(allProperty);
}

void BasicSceneBlock::changeNameStatus(const vector<string> &allProperty)
{
    // Set map name.
    string name = getSingleMapProperty(allProperty, Monopoly::MapProperty::NAME);
    mapName->setText(QString::fromLocal8Bit(name.c_str()));
}

void BasicSceneBlock::changeLocationStatus(const vector<string> &allProperty)
{
    // Set map location.
    string location = getSingleMapProperty(allProperty, Monopoly::MapProperty::LOCATION);
    mapLocation->setText(QString::fromLocal8Bit(location.c_str()));
}

void BasicSceneBlock::changeWhoStatus(int currentPlayerId, const vector<string> &allProperty)
{
    // Set who is here.
    string whoishere = getSingleMapProperty(allProperty, Monopoly::MapProperty::WHOISHERE);
    stringstream ss(whoishere);
    // Clear all playerName label's text.
    for (auto itName = playerName.begin(); itName != playerName.end(); ++itName) {
        (*itName)->setText("");
    }
    // If it has player, then set text.
    while (ss.good()) {
        string str;
        getline(ss, str, '-');
        stringstream numberSS(str);
        int playerId = -1;
        numberSS >> playerId;
        if (playerId > -1) {
            playerName[playerId]->setText("P" + QString::number(playerId+1));
            if (playerId == currentPlayerId) {
                playerName[playerId]->setStyleSheet("QLabel {border: 2px solid dimgray; color: red}");
            }
            else {
                playerName[playerId]->setStyleSheet("QLabel { border: 2px solid dimgray; }");
            }
        }
    }
}

void BasicSceneBlock::changeOtherStatus(const vector<string> &allProperty)
{
    // Set other property.
    string otherPropertyStr;
    string purchasePrice = getSingleMapProperty(allProperty, Monopoly::MapProperty::PURCHASE_PRICE);
    string host = getSingleMapProperty(allProperty, Monopoly::MapProperty::HOST);
    string fine = getSingleMapProperty(allProperty, Monopoly::MapProperty::FINE);
    string level = getSingleMapProperty(allProperty, Monopoly::MapProperty::LEVEL);
    string upgradePrice = getSingleMapProperty(allProperty, Monopoly::MapProperty::UPGRADE_PRICE);
    // If it is upgradable map and has host player.
    if (! upgradePrice.empty() && ! host.empty() && host != "") {
        otherPropertyStr.append(Monopoly::MapProperty::HOST + ": " + host + "\n");
        otherPropertyStr.append(Monopoly::MapProperty::LEVEL + ": " + level + "\n");
        otherPropertyStr.append(Monopoly::MapProperty::UPGRADE_PRICE + ": " + upgradePrice + "\n");
        otherPropertyStr.append(Monopoly::MapProperty::FINE + ": " + fine);
    }
    // If it is buyable map and has host player.
    else if (! purchasePrice.empty() && ! host.empty() && host != "") {
        otherPropertyStr.append(Monopoly::MapProperty::HOST + ": " + host + "\n");
        otherPropertyStr.append(Monopoly::MapProperty::FINE + ": " + fine);
    }
    // If it is buyable map and it has not host player.
    else if ( ! purchasePrice.empty() && (host.empty() || host == "")) {
        otherPropertyStr.append(Monopoly::MapProperty::PURCHASE_PRICE + ": " + purchasePrice);
    }
    // If it is unbuyable map.
    else {
        string name = getSingleMapProperty(allProperty, Monopoly::MapProperty::NAME);
        otherPropertyStr.append("Unbuyable map:\n" + name);
    }
    mapOtherProperty->setText(QString::fromLocal8Bit(otherPropertyStr.c_str()));
}
