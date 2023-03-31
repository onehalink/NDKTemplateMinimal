#pragma once

#include "Runtime.h"



Void OnAppInit(Void* userParam);
Void OnAppResize(SizeType width, SizeType height);
Bool OnAppQuit();


Void OnUpdate(RealType deltaTime);
Void OnRender(Void* RenderTarget);