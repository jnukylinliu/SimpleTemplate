#ifndef SPLASHVIDEOWIDGET_H
#define SPLASHVIDEOWIDGET_H

#include <QWidget>
#include <QProgressBar>
#include <QSharedMemory>
#include <QImage>
#include <QTimer>
#include <QMessageBox>

extern "C" {
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libavutil/avutil.h>
}

#include "SharedStatus.h"

class SplashVideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SplashVideoWidget(QWidget *parent = nullptr);
    ~SplashVideoWidget();
    void play(const QString &filePath);

    bool initSharedMemory();

    QProgressBar* getProgressBar() const { return progressBar; }

signals:
    void videoFinished();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void decodeNextFrame();
    void finishVideo();


    QImage currentFrame;
    QProgressBar *progressBar;
    QSharedMemory sharedMem;
    QTimer *timer;

    // FFmpeg
    AVFormatContext *fmtCtx;
    AVCodecContext *codecCtx;
    AVFrame *frame;
    AVFrame *frameRGB;
    AVPacket *packet;
    struct SwsContext *swsCtx;
    int videoStreamIndex;
    int totalFrames;
    int currentFrameIndex;
    bool videoPlaying;
    QString videoPath;
};

#endif // SPLASHVIDEOWIDGET_H
