#if defined(__ANDROID__)

#include <node.h>
#include <android/log.h>
using namespace v8;

/**
 * [Lifesaver](http://luismreis.github.io/node-bindings-guide/docs/arguments.html)
 */

/**
 * Usage:
 * * 
 * See ./libs/android_logcat.js
 *
 */

/* In case an extra serving of boilerplate is required to be a bad-ass programmer */
/*
    #include <node.h>

    using namespace v8;

    void Method(const FunctionCallbackInfo<Value>& args) {
      Isolate* isolate = Isolate::GetCurrent();
      HandleScope scope(isolate);
      args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
    }

    void init(Handle<Object> exports) {
      NODE_SET_METHOD(exports, "hello", Method);
    }

    NODE_MODULE(addon, init)
*/

// Shamelessly stolen from v8::shell.cc
// Extracts a C string from a V8 Utf8Value.
const char* ToCString(const v8::String::Utf8Value& value) {
  return *value ? *value : "<string conversion failed>";
}

/**
 * See args? That's variadic, varargic, varargy..., varorgy, var orgy.
 */ 
void _AndroidLogcat(android_LogPriority priority, const char* tag, const char* format, /* const char* input */ va_list args)
{
    /* TODO generate every permutation of String, Number, Object, Boolean, Arrays... hm, say 8 positions */
    /* hm... or treat everything as a string, then format will be pointless */
    __android_log_vprint(priority, tag, format, /*input*/ args);
}

/**
 * TODO fake var orgy play with format in javascript, if possible; PhD applicants may only apply.
 */ 
void AndroidLogcat(const FunctionCallbackInfo<Value>& args) {
      Isolate* isolate = Isolate::GetCurrent();
      HandleScope scope(isolate);
      
      /* TODO This has be an int, also do bounds-checking */
      // or... static_cast<android_LogPriority>(args[0]->Uint32Value())
      const int priority = static_cast<int>(args[0]->NumberValue());
      
      /* TODO 0 to 8 (actually til 7), if exceeded throw exception */
      /* TODO if double or other type, throw exception */
      
      /* This must be a char* */
      String::Utf8Value p_tag(args[1]->ToString());
      const char* tag = *p_tag;
      /* TODO if non-string or other type, throw exception */
      
      /* Let's cheat, fake var orgy in js? */
      const char* format = "%s";
      
      /* The incoming string */
      String::Utf8Value p_input(args[2]->ToString());
      const char* input = *p_input;
      /* TODO if non-string or other type, throw exception */
      
      /* TODO if less than three parameters, throw exception */
      
      __android_log_print(priority, tag, format, input);
      //_AndroidLogcat(priority, tag, format, input);
}    



/* Evidently v8 has already implemented this ... see platform-posix.cc */
/*
void OS::Print(const char* format, ...) {
  va_list args;
  va_start(args, format);
  VPrint(format, args);
  va_end(args);
}


void OS::VPrint(const char* format, va_list args) {
#if defined(ANDROID) && !defined(V8_ANDROID_LOG_STDOUT)
  __android_log_vprint(ANDROID_LOG_INFO, LOG_TAG, format, args);
#else
  vprintf(format, args);
#endif
}


void OS::FPrint(FILE* out, const char* format, ...) {
  va_list args;
  va_start(args, format);
  VFPrint(out, format, args);
  va_end(args);
}


void OS::VFPrint(FILE* out, const char* format, va_list args) {
#if defined(ANDROID) && !defined(V8_ANDROID_LOG_STDOUT)
  __android_log_vprint(ANDROID_LOG_INFO, LOG_TAG, format, args);
#else
  vfprintf(out, format, args);
#endif
}


void OS::PrintError(const char* format, ...) {
  va_list args;
  va_start(args, format);
  VPrintError(format, args);
  va_end(args);
}
*/

void Init(Handle<Object> exports) {
  NODE_SET_METHOD(exports, "__android_logcat", AndroidLogcat);
}


NODE_MODULE_CONTEXT_AWARE_BUILTIN(android_logcat, Init) /* Declare outside the namespace */


#endif /* __ANDROID__ */
