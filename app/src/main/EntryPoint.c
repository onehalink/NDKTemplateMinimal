#include "AppThread.h"

#include <android/native_activity.h>

#include <pthread.h>



static Runtime runtime;


static void OnStart(ANativeActivity* activity)
{
    LOGD("Function [%s] had been invoked", __FUNCTION__ );
}

static void OnResume(ANativeActivity* activity)
{
    LOGD("Function [%s] had been invoked", __FUNCTION__ );
}

static void* OnSaveInstanceState(ANativeActivity* activity, size_t* outputSavedInstanceStateSize)
{
    LOGD("Function [%s] had been invoked", __FUNCTION__ );

    return NULL;
}

static void OnPause(ANativeActivity* activity)
{
    LOGD("Function [%s] had been invoked", __FUNCTION__ );
}

static void OnStop(ANativeActivity* activity)
{
    LOGD("Function [%s] had been invoked", __FUNCTION__ );
}

static void OnDestroy(ANativeActivity* activity)
{
    LOGD("Function [%s] had been invoked", __FUNCTION__ );

    runtime.wantToQuit = OnAppQuit();
}

static void OnWindowFocusChanged(ANativeActivity* activity, int isFocused)
{
    LOGD("Function [%s] had been invoked", __FUNCTION__ );
}

static void OnNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window)
{
    LOGD("Function [%s] had been invoked", __FUNCTION__ );

    ANativeWindow_setBuffersGeometry(
            window,
            ANativeWindow_getWidth(window),
            ANativeWindow_getHeight(window),
            WINDOW_FORMAT_RGBA_8888
    );

    runtime.window = window;
}

static void OnNativeWindowResized(ANativeActivity* activity, ANativeWindow* window)
{
    LOGD("Function [%s] had been invoked", __FUNCTION__ );

    int width   = ANativeWindow_getWidth(window);
    int height  = ANativeWindow_getHeight(window);

    OnAppResize(width, height);

    LOGD("Resolution: %dx%d", width, height);
}

static void OnNativeWindowRedrawNeeded(ANativeActivity* activity, ANativeWindow* window)
{
    LOGD("Function [%s] had been invoked", __FUNCTION__ );
}

static void OnNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window)
{
    LOGD("Function [%s] had been invoked", __FUNCTION__ );
}

static void OnInputQueueCreated(ANativeActivity* activity, AInputQueue* queue)
{
    LOGD("Function [%s] had been invoked", __FUNCTION__ );
}

static void OnInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue)
{
    LOGD("Function [%s] had been invoked", __FUNCTION__ );
}

static void OnContentRectChanged(ANativeActivity* activity, const ARect* rect)
{
    LOGD("Function [%s] had been invoked", __FUNCTION__ );
}

static void OnConfigurationChanged(ANativeActivity* activity, const ARect* rect)
{
    LOGD("Function [%s] had been invoked", __FUNCTION__ );
}

static void OnLowMemory(ANativeActivity* activity)
{
    LOGD("Function [%s] had been invoked", __FUNCTION__ );
}


// Similar as "main"
void ANativeActivity_onCreate(ANativeActivity* activity, void* SavedInstanceState, size_t savedInstanceStateSize)
{
    LOGD("Startup");


    activity->callbacks->onStart                    = OnStart;
    activity->callbacks->onResume                   = OnResume;
    activity->callbacks->onSaveInstanceState        = OnSaveInstanceState;
    activity->callbacks->onPause                    = OnPause;
    activity->callbacks->onStop                     = OnStop;
    activity->callbacks->onDestroy                  = OnDestroy;
    activity->callbacks->onWindowFocusChanged       = OnWindowFocusChanged;
    activity->callbacks->onNativeWindowCreated      = OnNativeWindowCreated;
    activity->callbacks->onNativeWindowResized      = OnNativeWindowResized;
    activity->callbacks->onNativeWindowRedrawNeeded = OnNativeWindowRedrawNeeded;
    activity->callbacks->onNativeWindowDestroyed    = OnNativeWindowDestroyed;
    activity->callbacks->onInputQueueCreated        = OnInputQueueCreated;
    activity->callbacks->onInputQueueDestroyed      = OnInputQueueDestroyed;
    activity->callbacks->onContentRectChanged       = OnContentRectChanged;
    activity->callbacks->onConfigurationChanged     = OnConfigurationChanged;
    activity->callbacks->onLowMemory                = OnLowMemory;


    {
        runtime.activity    = activity;
        runtime.window      = NullPointer;

        runtime.configuration   = NullPointer;
        runtime.looper          = NullPointer;
        runtime.inputQueue      = NullPointer;

        runtime.isReady         = False;
        runtime.wantToQuit      = False;
    }


    {
        pthread_t       thread;
        pthread_attr_t  attribute;

        pthread_attr_init(&attribute);
        pthread_attr_setdetachstate(&attribute, PTHREAD_CREATE_DETACHED);
        pthread_create(&thread, &attribute, AppThread, &runtime);
        pthread_attr_destroy(&attribute);
    }
}