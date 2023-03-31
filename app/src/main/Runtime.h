#pragma once

#include "Engine.h"

#include "Log.h"



typedef struct
{
    Void* activity;   // A pointer to a ANativeActivity instance
    Void* window;     // A pointer to a ANativeWindow instance

    Void* configuration;    // A pointer to a AConfiguration instance
    Void* looper;           // A pointer to a ALooper instance
    Void* inputQueue;       // A pointer to a AInputQueue instance

    Bool isReady;       // A flag to confirm if some resources had been gained
    Bool wantToQuit;    // A flag to confirm if should exit this app
}
Runtime;