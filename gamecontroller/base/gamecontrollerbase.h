#pragma once
#include <QObject>
#include <QQmlEngine>

class GameControllerBase : public QObject
{
    Q_OBJECT
public:
    GameControllerBase(QObject* parent = nullptr);

    static void registerMe(const std::string& moduleName);

    enum GameTheme {
      Dark,
      Light
    };

    /*Q_INVOKABLE*/ GameTheme theme() const;
    void setTheme(GameTheme newTheme);

private:
    GameTheme m_theme;
};
