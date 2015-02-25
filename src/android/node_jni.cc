/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "node.h"
#include "node_jni.h"

#include <string.h>
#include <jni.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <android/log.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

// socket stuff
#include <cutils/sockets.h>

using namespace node;

#if defined(__arm__)
  #if defined(__ARM_ARCH_7A__)
    #if defined(__ARM_NEON__)
      #define ABI "armeabi-v7a/NEON"
    #else
      #define ABI "armeabi-v7a"
    #endif
  #else
   #define ABI "armeabi"
  #endif
#elif defined(__i386__)
   #define ABI "x86"
#elif defined(__mips__)
   #define ABI "mips"
#else
   #define ABI "unknown"
#endif

/**
 * Ol' dirty trick to convert const char* to char*
 */
union charunion {
  char *chr;
  const char* cchr;
};

using namespace node;


#ifdef __cplusplus
extern "C" {
#endif
    
#ifndef MAX_LOG_MESSAGE_LENGTH
#  define MAX_LOG_MESSAGE_LENGTH 256
#endif    

static void ThrowException(
        JNIEnv* env,
        const char* className,
        const char* message)
{
    // Get the exception class
    jclass clazz = env->FindClass(className);

    // If exception class is found
    if (NULL != clazz)
    {
        // Throw exception
        env->ThrowNew(clazz, message);

        // Release local class reference
        env->DeleteLocalRef(clazz);
    }
}
    
static void AndroidThrowErrnoException(
 // name clash with node_internals.h
        JNIEnv* env,
        const char* className,
        int errnum)
{
    char buffer[MAX_LOG_MESSAGE_LENGTH];

    // Get message for the error number
    if (-1 == strerror_r(errnum, buffer, MAX_LOG_MESSAGE_LENGTH))
    {
        strerror_r(errno, buffer, MAX_LOG_MESSAGE_LENGTH);
    }

    // Throw exception
    ThrowException(env, className, buffer);
}

JNIEXPORT jint JNICALL Java_nl_sison_android_nodejs_repl_NodeJNI_start
  (JNIEnv *env, jclass clazz, jint jargc, jobjectArray jargv)
{
    
    int len = env->GetArrayLength(jargv); // should be equal to argc

    char** argv = new char*[len]; // in hindsight, I should've consted this, instead of pulling the enum trick, doh
    jstring* jstringArr = new jstring[len];


    // type conversion, wow
    fprintf(stdout, "argc:%i\n", (int) jargc);
    for (int i=0; i<len; i++) {
        jstringArr[i] = (jstring) env->GetObjectArrayElement(jargv, i);
        charunion char_union;
        char_union.cchr = env->GetStringUTFChars(jstringArr[i], 0);
        argv[i] = char_union.chr;

        // debug
        fprintf(stdout, "%s\n", argv[i]); // stdout is /dev/null on Android        
    }

    // capture exit result
    int returnValue = node::Start((int) jargc, argv);
    // TODO jint is a typedef for long on an arm64/amd64 and how about endianness? Phrack it. Just cast.
    // figure out with macros later

    for (int i=0; i<len; i++) {
        // prevent memory leaks
        env->ReleaseStringUTFChars(jstringArr[i], argv[i]);
    }
    
    // deallocate arrays
    delete argv;
    delete jstringArr;

    return returnValue;
}

/**
 * 
 * API_LEVEL 21 has more low level control, whereas all implementations <= 21
 * have netlink default as an underlying implementation underneath LocalSocket{,Server}.
 * 
 * Since LocalSocketServer doesn't readily expose bind and the function params,
 * it's very very very difficult to guarantee non-fragmentation of
 * and enforce the filesystem namespace and socket stream
 * implementation across the versions.
 * 
 * So, I reused the API_LEVEL 21 implementation by borrowing cutils.
 * 
 */
JNIEXPORT jint JNICALL Java_nl_sison_android_nodejs_repl_NodeJNI_createLocalSocket
(JNIEnv *env, jclass clazz, jstring jname)
{
    // TODO figure out if this needs to be manually collected
    const char* name = env->GetStringUTFChars(jname, 0);
    int localSocket = socket_local_server(name, ANDROID_SOCKET_NAMESPACE_FILESYSTEM, SOCK_STREAM);
  
    if (-1 == localSocket)
    {
        AndroidThrowErrnoException(env, "java/io/IOException", localSocket);
    }
 
    
    fprintf(stdout, "AF_LOCAL socket created, bound and listening: %s", name);
    
    env->ReleaseStringUTFChars(jname, name);
    
    return localSocket; // int to create file descriptor
}


#ifdef __cplusplus
}
#endif

