/**
 *  @file   Voice.h
 *  @brief  语音处理
 *  @author  stanjiang
 *  @date    2018-12-21
 */


#ifndef PROJ_ANDROID_VOICE_H
#define PROJ_ANDROID_VOICE_H

extern "C"
{
    // 语音识别
    void onSpeechRecognizer(const char* data);

};

#endif //PROJ_ANDROID_VOICE_H
