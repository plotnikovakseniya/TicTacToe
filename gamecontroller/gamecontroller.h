#pragma once
#include <QObject>
#include <QQmlEngine>
#include "gamemodel/gamemodel.h"

class GameController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int theme READ theme WRITE setTheme NOTIFY themeChanged)
public:
    enum GameTheme {
      Dark,
      Light
    };

    explicit GameController(GameTheme theme = Dark, QObject* parent = nullptr);

    static void registerMe(const std::string& moduleName);

    int theme() const;
    void setTheme(int newTheme);

    Q_INVOKABLE void switchTheme();
    Q_INVOKABLE GameModel* gameModel();

signals:
    void themeChanged();

private:
    GameModel m_gameModel;
    GameTheme m_theme;
};
