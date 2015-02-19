#include <node.h>
#include <android/log.h>

#if defined(__ANDROID__)

/**
 * Usage:
 *
 * var log = require('android.logcat');
 * var TAG = 'somescript.js';
 * log.d(TAG, 'something happened...');
 * log.e(TAG, 'it was terrible...');
 * log.w(TAG, 'may it never happen again...');
 * log.d(TAG, 'And nevermore...');
 *
 */

#define ALOGD(...) __android_log_print(ANDROID_LOG_DEBUG, __VA_ARGS__)
#define ALOGE(...) __android_log_print(ANDROID_LOG_DEBUG, __VA_ARGS__)
#define ALOGW(...) __android_log_print(ANDROID_LOG_DEBUG, __VA_ARGS__)
#define ALOGI(...) __android_log_print(ANDROID_LOG_DEBUG, __VA_ARGS__)

using namespace v8;

void ErrorCheck(const FunctionCallbackInfo<Value>& args, Isolate& isolate, HandleScope& scope)
{
  if (args.Length() < 2) {
    isolate.ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong number of arguments: you must provide a TAG and the logging string.")));
    return;
  }

  if (!args[0]->IsString() || !args[1]->IsString()) {
    isolate.ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong argument types, both must be strings. Until I learn how to do variadics and translate that to C++...")));
    return;
  }
}

void AndroidLogD(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ErrorCheck(args, isolate, scope);

  ALOGD(args[0]->StringValue(), args[1]->StringValue());
}

void AndroidLogE(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ErrorCheck(args, isolate, scope);

  ALOGE(args[0]->StringValue(), args[1]->StringValue());
}

void AndroidLogW(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ErrorCheck(args, isolate, scope);

  ALOGW(args[0]->StringValue(), args[1]->StringValue());
}

void AndroidLogI(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ErrorCheck(args, isolate, scope);

  ALOGI(args[0]->StringValue(), args[1]->StringValue());
}

void Init(Handle<Object> exports) {
  NODE_SET_METHOD(exports, "d", AndroidLogD);
  NODE_SET_METHOD(exports, "e", AndroidLogE);
  NODE_SET_METHOD(exports, "w", AndroidLogW);
  NODE_SET_METHOD(exports, "i", AndroidLogI);
}

NODE_MODULE_CONTEXT_AWARE_BUILTIN(android.logcat, Init)

#endif /* __ANDROID__ */
