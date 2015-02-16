#ifndef ANDROID_LOG_H_
#define ANDROID_LOG_H_

#include <android/log.h>

#ifndef LOG_TAG
#define LOG_TAG "iojs/android"
#endif /* LOG_TAG */

/**
 * Logging on android
 */

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,   LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,   LOG_TAG, __VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARNING, LOG_TAG, __VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFORMATION, LOG_TAG, __VA_ARGS__)

/*
#define fprintf(pipe,...) \
    if (pipe == stdout) \
        __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__); \
    else if (pipe == stderr) \
        __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__); \
    else \
        fprintf(pipe,__VA_ARGS__)
*/        

/* I don't think it's necessary to also redefine snprintf or printf */

#endif /* ANDROID_LOG_H_ */
