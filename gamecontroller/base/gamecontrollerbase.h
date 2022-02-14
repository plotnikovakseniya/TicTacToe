#pragma once
#include <QObject>
#include <QQmlEngine>

class GameControllerBase : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int theme READ theme WRITE setTheme NOTIFY themeChanged)
public:
    enum GameTheme {
      Dark,
      Light
    };

    explicit GameControllerBase(GameTheme theme = Dark, QObject* parent = nullptr);

    static void registerMe(const std::string& moduleName);

    int theme() const;
    QString themeName() const;
    void setTheme(int newTheme);

signals:
    void themeChanged();

private:
    GameTheme m_theme;
};
