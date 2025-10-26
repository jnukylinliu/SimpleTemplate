#include "SplashVideoWidget.h"
#include <QPainter>
#include <QDebug>
#include <QFile>
#include <QCoreApplication>



SplashVideoWidget::SplashVideoWidget(QWidget *parent)
    : QWidget(parent), sharedMem("SplashSharedMem"),
    fmtCtx(nullptr), codecCtx(nullptr),
    frame(nullptr), frameRGB(nullptr),
    packet(nullptr), swsCtx(nullptr),
    videoStreamIndex(-1), totalFrames(0), currentFrameIndex(0),
    videoPlaying(false)
{
    setWindowFlag(Qt::FramelessWindowHint);
    setFixedSize(800, 450);

    progressBar = new QProgressBar(this);
    progressBar->setGeometry(0, height() * 3 / 4, width(), 20);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    progressBar->setTextVisible(true);
    progressBar->setFormat("%p%");
    progressBar->setStyleSheet(
        "QProgressBar {"
        "  border: 2px solid #444;"       // 边框颜色
        "  border-radius: 10px;"          // 圆角
        "  text-align: center;"           // 文字居中
        "  height: 20px;"                 // 高度
        "  color: #FFD700;"               // 文字颜色（亮金色）
        "  background: #333;"             // 背景颜色（深灰）
        "  font-size: 16px;"      // 文字大小，可调
        "}"
        "QProgressBar::chunk {"
        "  background-color: qlineargradient("
        "    x1:0, y1:0, x2:1, y2:0,"
        "    stop:0 #112e34, stop:1 #112e34);" // 渐变填充色，浅蓝到深蓝
        "  border-radius: 10px;"           // 填充圆角
        "}"
        );


    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SplashVideoWidget::decodeNextFrame);

    initSharedMemory();
}

SplashVideoWidget::~SplashVideoWidget()
{
    if(timer) timer->stop();
    if(frameRGB) av_frame_free(&frameRGB);
    if(frame) av_frame_free(&frame);
    if(packet) av_packet_free(&packet);
    if(codecCtx) avcodec_free_context(&codecCtx);
    if(fmtCtx) avformat_close_input(&fmtCtx);
    if(swsCtx) sws_freeContext(swsCtx);
}

void SplashVideoWidget::play(const QString &file)
{
    videoPath = file;
    if(!QFile::exists(file)) {
        qDebug() << "Video file not found:" << file;
        finishVideo();
        return;
    }

    //av_register_all();

    if(avformat_open_input(&fmtCtx, file.toUtf8().data(), nullptr, nullptr) != 0) {
        qDebug() << "Cannot open video file";
        finishVideo();
        return;
    }

    if(avformat_find_stream_info(fmtCtx, nullptr) < 0) {
        qDebug() << "Cannot find stream info";
        finishVideo();
        return;
    }

    // 找到视频流
    for(int i=0;i<fmtCtx->nb_streams;i++){
        if(fmtCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO){
            videoStreamIndex = i;
            break;
        }
    }

    if(videoStreamIndex == -1){
        qDebug() << "No video stream";
        finishVideo();
        return;
    }

    AVCodecParameters *codecPar = fmtCtx->streams[videoStreamIndex]->codecpar;
    const AVCodec *codec = avcodec_find_decoder(codecPar->codec_id);
    if(!codec){
        qDebug() << "Codec not found";
        finishVideo();
        return;
    }

    codecCtx = avcodec_alloc_context3(codec);
    avcodec_parameters_to_context(codecCtx, codecPar);
    if(avcodec_open2(codecCtx, codec, nullptr) < 0){
        qDebug() << "Cannot open codec";
        finishVideo();
        return;
    }

    frame = av_frame_alloc();
    frameRGB = av_frame_alloc();
    int numBytes = av_image_get_buffer_size(AV_PIX_FMT_RGB24, codecCtx->width, codecCtx->height, 1);
    uint8_t *buffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));
    av_image_fill_arrays(frameRGB->data, frameRGB->linesize, buffer, AV_PIX_FMT_RGB24, codecCtx->width, codecCtx->height, 1);

    swsCtx = sws_getContext(codecCtx->width, codecCtx->height, codecCtx->pix_fmt,
                            codecCtx->width, codecCtx->height, AV_PIX_FMT_RGB24,
                            SWS_BILINEAR, nullptr, nullptr, nullptr);

    packet = av_packet_alloc();
    totalFrames = fmtCtx->streams[videoStreamIndex]->nb_frames;
    if(totalFrames == 0) totalFrames = 100; // 防止为0，按经验估算
    currentFrameIndex = 0;

    videoPlaying = true;
    timer->start(30); // 每 30ms 解码一帧
}

void SplashVideoWidget::decodeNextFrame()
{
    if(!videoPlaying) return;

    int ret = av_read_frame(fmtCtx, packet);
    if(ret < 0){
        finishVideo();
        return;
    }

    if(packet->stream_index == videoStreamIndex){
        ret = avcodec_send_packet(codecCtx, packet);
        if(ret < 0){
            av_packet_unref(packet);
            return;
        }

        while(avcodec_receive_frame(codecCtx, frame) == 0){
            sws_scale(swsCtx, frame->data, frame->linesize, 0, codecCtx->height,
                      frameRGB->data, frameRGB->linesize);

            currentFrame = QImage(frameRGB->data[0], codecCtx->width, codecCtx->height, QImage::Format_RGB888).copy();
            update();

            // 更新进度条和共享内存
            currentFrameIndex++;
            int percent = (int)(currentFrameIndex * 100 / totalFrames);
            if(percent>100) percent=100;
            progressBar->setValue(percent);

            sharedMem.lock();
            SharedStatus *status = (SharedStatus*)sharedMem.data();
            status->progress = percent;
            sharedMem.unlock();
        }
    }
    av_packet_unref(packet);
}

void SplashVideoWidget::finishVideo()
{
    videoPlaying = false;
    timer->stop();

    progressBar->setValue(100);
    sharedMem.lock();
    SharedStatus *status = (SharedStatus*)sharedMem.data();
    status->videoFinished = true;
    status->progress = 100;
    sharedMem.unlock();

    emit videoFinished();
}

void SplashVideoWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(!currentFrame.isNull()){
        painter.drawImage(rect(), currentFrame);
    } else {
        painter.fillRect(rect(), Qt::black);
    }
}

bool SplashVideoWidget::initSharedMemory()
{
    // 如果共享内存已存在，则提示并退出
    if (!sharedMem.create(sizeof(SharedStatus))) {
        QMessageBox::warning(nullptr, "提示", "程序已在运行中！");
        exit(0);
    }

    // 初始化共享数据
    sharedMem.lock();
    SharedStatus *status = reinterpret_cast<SharedStatus*>(sharedMem.data());
    status->videoFinished = false;
    status->progress = 0;
    sharedMem.unlock();

    qDebug() << "Shared memory initialized.";

    return true;
}
