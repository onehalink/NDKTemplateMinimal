#include "Application.h"



static Serface RenderingSerface;


Void OnAppInit(Void* userParam)
{
    FMemory.Clear( &RenderingSerface, sizeof(Serface) );
}

Void OnAppResize(SizeType width, SizeType height)
{
    FSerface.Destruct(&RenderingSerface);
    RenderingSerface = FSerface.Construct(width, height);
}

Bool OnAppQuit()
{
    return True;
}

Void OnUpdate(RealType deltaTime)
{
    LOGD("frame time: %f FPS: %d ", deltaTime, CAST(SizeType, 1 / deltaTime));
}

Void OnRender(Void* RenderTarget)
{
    // frame start
    Color clearColor = FColor.Cyan;
    FSerface.ClearColor(&RenderingSerface, &clearColor);

    // do your rendering work here(by updating "RenderingSerface")
    {

    }

    // frame end
    //FSerface.FlipVertical(&RenderingSerface);
    FSerface.CopyTo(&RenderingSerface, RenderTarget);
}