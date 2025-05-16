#include "videoplayer.h"
#include <QMediaPlayer>
#include <QVideoSink>
#include <QDebug>

VideoPlayer::VideoPlayer(QObject *parent)
    : QObject(parent)
    , m_player(new QMediaPlayer(this))
    , m_videoSink(nullptr)
    , m_isLoading(false)
{
    connect(m_player, &QMediaPlayer::mediaStatusChanged,
            this, &VideoPlayer::handleMediaStatusChanged);
    connect(m_player, &QMediaPlayer::errorOccurred,
            this, &VideoPlayer::handleError);
    m_player->setLoops(QMediaPlayer::Infinite);
    m_player->setAudioOutput(nullptr);  // Disable audio
}

VideoPlayer::~VideoPlayer()
{
    delete m_player;
}

QUrl VideoPlayer::source() const
{
    return m_source;
}

void VideoPlayer::setSource(const QUrl &source)
{
    if (m_source != source) {
        m_source = source;
        m_isLoading = true;
        m_error.clear();
        emit loadingChanged();
        emit errorChanged();
        
        // Reset player state before loading new source
        m_player->stop();
        m_player->setSource(source);
        emit sourceChanged();
    }
}

bool VideoPlayer::isPlaying() const
{
    return m_player->playbackState() == QMediaPlayer::PlayingState;
}

QVideoSink* VideoPlayer::videoSink() const
{
    return m_videoSink;
}

void VideoPlayer::setVideoSink(QVideoSink* sink)
{
    if (m_videoSink != sink) {
        m_videoSink = sink;
        m_player->setVideoSink(sink);
        emit videoSinkChanged();
    }
}

bool VideoPlayer::isLoading() const
{
    return m_isLoading;
}

QString VideoPlayer::error() const
{
    return m_error;
}

void VideoPlayer::play()
{
    if (!m_error.isEmpty()) {
        // If there was an error, try to reload the source
        m_player->setSource(m_source);
    }
    m_player->play();
    emit playingChanged();
}

void VideoPlayer::stop()
{
    m_player->stop();
    emit playingChanged();
}

void VideoPlayer::handleMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    switch (status) {
        case QMediaPlayer::LoadingMedia:
            m_isLoading = true;
            emit loadingChanged();
            break;
        case QMediaPlayer::LoadedMedia:
            m_isLoading = false;
            emit loadingChanged();
            m_player->play();
            break;
        case QMediaPlayer::EndOfMedia:
            m_player->play();  // Restart since we're in infinite loop mode
            break;
        case QMediaPlayer::InvalidMedia:
            m_isLoading = false;
            m_error = "The video file appears to be corrupted or in an unsupported format.";
            emit loadingChanged();
            emit errorChanged();
            break;
        case QMediaPlayer::NoMedia:
            m_isLoading = false;
            emit loadingChanged();
            break;
        case QMediaPlayer::StalledMedia:
            // Try to recover from stalled state
            m_player->stop();
            m_player->setSource(m_source);
            m_player->play();
            break;
        default:
            break;
    }
}

void VideoPlayer::handleError(QMediaPlayer::Error error, const QString &errorString)
{
    m_isLoading = false;
    
    // Check for FFmpeg-specific errors
    if (errorString.contains("Demuxing failed") || 
        errorString.contains("Immediate exit requested")) {
        m_error = "Failed to load the video. The file might be corrupted or in an unsupported format.";
    }
    else if (errorString.contains("Packet corrupt") || 
             errorString.contains("Invalid NAL unit size") ||
             errorString.contains("missing picture in access unit") ||
             errorString.contains("partial file")) {
        m_error = "The video file is corrupted or incomplete. Please try a different video file.";
    }
    // Handle other common errors
    else {
        switch (error) {
            case QMediaPlayer::ResourceError:
                m_error = "Could not load the video file. The file might be corrupted or in an unsupported format.";
                break;
            case QMediaPlayer::FormatError:
                m_error = "The video format is not supported. Please ensure the video is in H.264 or H.265 format.";
                break;
            case QMediaPlayer::NetworkError:
                m_error = "Network error while loading the video.";
                break;
            case QMediaPlayer::AccessDeniedError:
                m_error = "Access to the video file was denied.";
                break;
            default:
                m_error = "An error occurred while playing the video: " + errorString;
                break;
        }
    }
    
    qDebug() << "VideoPlayer error:" << errorString;
    emit loadingChanged();
    emit errorChanged();
} 