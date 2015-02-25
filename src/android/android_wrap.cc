#if defined(__ANDROID__)

#include "env-inl.h"
#include <android/log.h>

using namespace v8;
using node::Environment;

/**
 * [The guide](https://github.com/rukamir/GoogleV8Tutorials/blob/master/DefiningJSObjectsInCpp/main.cpp)
 * [Lifesaver](http://luismreis.github.io/node-bindings-guide/docs/arguments.html)
 */

/**
 * Usage:
 * * 
 * See ./libs/android.js
 *
 */

namespace node {

namespace android {

/* Evidently v8 has already implemented this ... see platform-posix.cc */
static void AndroidLogcat(const FunctionCallbackInfo<Value>& args) {
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
}    

void Initialize(Handle<Object> target,
                Handle<Value> unused,
                Handle<Context> context) {
  Environment* env = Environment::GetCurrent(context);
  env->SetMethod(target, "android_logcat", AndroidLogcat);
  // TODO add other android related native nodejs stuff you might need
}

}} // namespace node.android

NODE_MODULE_CONTEXT_AWARE_BUILTIN(android, node::android::Initialize) /* Declare outside the namespace */
#endif /* __ANDROID__ */
