#pragma once

#include <QObject>
#include <QQmlEngine>

class ClientSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int theme READ theme WRITE setTheme NOTIFY themeChanged)
public:
    enum GameTheme {
      Dark,
      Light
    };

    ClientSettings(ClientSettings &other) = delete;
    void operator=(const ClientSettings &) = delete;

    static void registerMe(const std::string& moduleName);
    static ClientSettings* getClientSettings(GameTheme theme = GameTheme::Dark);

    Q_INVOKABLE void switchTheme();
    void setTheme(int newTheme);
    int theme() const;


signals:
    void themeChanged();

protected:
    explicit ClientSettings(const GameTheme& theme = GameTheme::Dark, QObject *parent = nullptr);

private:
    static ClientSettings* m_clientSettings;
    GameTheme m_theme;
    int m_lang;
};
