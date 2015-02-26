#ifndef ANDROID_LOG_H_
#define ANDROID_LOG_H_

#include "android/log.h"

#ifdef fprintf
#  undef fprintf
#endif /* fprintf */


#ifndef LOGCAT_TAG
#define LOGCAT_TAG "android+iojs"
#endif /* LOGCAT_TAG */

/**
 * Logging on android
 */

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,      LOGCAT_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,      LOGCAT_TAG, __VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARNING,    LOGCAT_TAG, __VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFORMATION,LOGCAT_TAG, __VA_ARGS__)

/**
 * To make this work:
 * 1. Make sure the actual code that the macro will perform on
 * will apply naturally, i.e. it will find the correct pattern to match on in a single line.
 * TODO determine if the previous statement is true
 * 2. You have the correct std, that supports variadic args.
 * i.e. use --std=c99, not --std=gnu89
 * 3. Read this: https://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html
 * 4. Don't use a fucking buggy compiler... dammit.
 */
/* The following is broken on libuv for some reason... */
/*
#define fprintf(pipe,...) \
    do {
        if (pipe == stdout) \
            __android_log_print(ANDROID_LOG_INFO,LOGCAT_TAG,__VA_ARGS__); \
        else if (pipe == stderr) \
            __android_log_print(ANDROID_LOG_ERROR,LOGCAT_TAG,__VA_ARGS__); \
        else \
            fprintf(pipe,__VA_ARGS__); \
    } while (0)
*/
/*
#define fprintf(stderr,...) __android_log_print(ANDROID_LOG_ERROR, LOGCAT_TAG, __VA_ARGS__)
#define fprintf(stdout,...) __android_log_print(ANDROID_LOG_INFO,  LOGCAT_TAG, __VA_ARGS__)
*/
#define fprintf(stderr,...) LOGE(__VA_ARGS__)
#define fprintf(stdout,...) LOGD(__VA_ARGS__)



/* I don't think it's necessary to also redefine snprintf or printf */

#endif /* ANDROID_LOG_H_ */
