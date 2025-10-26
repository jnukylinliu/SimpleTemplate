#ifndef SHAREDSTATUS_H
#define SHAREDSTATUS_H


struct SharedStatus {
    bool videoFinished;   // 视频是否播放完
    int progress;         // 视频播放进度 0~100
};



#endif // SHAREDSTATUS_H
