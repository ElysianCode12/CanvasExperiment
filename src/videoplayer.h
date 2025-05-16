#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QVideoSink>
#include <QUrl>

class VideoPlayer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(bool playing READ isPlaying NOTIFY playingChanged)
    Q_PROPERTY(QVideoSink* videoSink READ videoSink WRITE setVideoSink NOTIFY videoSinkChanged)
    Q_PROPERTY(bool isLoading READ isLoading NOTIFY loadingChanged)
    Q_PROPERTY(QString error READ error NOTIFY errorChanged)

public:
    explicit VideoPlayer(QObject *parent = nullptr);
    ~VideoPlayer();

    QUrl source() const;
    void setSource(const QUrl &source);
    bool isPlaying() const;
    QVideoSink* videoSink() const;
    void setVideoSink(QVideoSink* sink);
    bool isLoading() const;
    QString error() const;

public slots:
    void play();
    void stop();

signals:
    void sourceChanged();
    void playingChanged();
    void videoSinkChanged();
    void loadingChanged();
    void errorChanged();

private slots:
    void handleMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void handleError(QMediaPlayer::Error error, const QString &errorString);

private:
    QMediaPlayer* m_player;
    QVideoSink* m_videoSink;
    QUrl m_source;
    bool m_isLoading;
    QString m_error;
};

#endif // VIDEOPLAYER_H 