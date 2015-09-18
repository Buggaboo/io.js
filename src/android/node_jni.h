#include <jni.h>
/* Header for class nl_sison_android_iojs_IoJsJni */

#ifndef _Included_nl_sison_android_iojs_IoJsJni
#define _Included_nl_sison_android_iojs_IoJsJni
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     nl_sison_android_iojs_IoJsJni
 * Method:    start
 * Signature: (I[Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_nl_sison_android_iojs_IoJsJni_start
  (JNIEnv *, jclass, jint, jobjectArray);

// prefix Android, in case of nameclash with node_internals.h
static void AndroidThrowErrnoException(
        JNIEnv*,
        const char*,
        int); 

static void ThrowException(
        JNIEnv*,
        const char*,
        const char*);
  
JNIEXPORT jint JNICALL Java_nl_sison_android_iojs_IoJsJni_createLocalSocketServer
(JNIEnv *, jclass, jstring);

#ifdef __cplusplus
}
#endif
#endif
