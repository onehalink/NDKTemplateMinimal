#include "AppThread.h"

#include <android/native_window.h>



Void* AppThread(Void* userParam)
{
    LOGD("Function [%s] had been invoked", __FUNCTION__ );

    Runtime* runtime = CAST(Runtime*, userParam);

    // wait
    while( !runtime->isReady )
    {
        if( !runtime->activity )
            continue;

        if( !runtime->window )
            continue;

        runtime->isReady = True;
    }

    OnAppInit(userParam);

    // main loop
    {
        Timer timer         = FTimer.Construct();
        RealType timestep   = 0;

        while( !runtime->wantToQuit )
        {
            OnUpdate(timestep);
            //OnRender(NullPointer);

            {
                ANativeWindow* window = CAST( ANativeWindow*, runtime->window );

                ANativeWindow_Buffer buffer;

                ANativeWindow_lock(window, &buffer, NullPointer);

                OnRender(buffer.bits);

                ANativeWindow_unlockAndPost(window);
            }

            timestep = FTimer.Elapsed(&timer);
            FTimer.Reset(&timer);
        };
    }


    return NullPointer;
}