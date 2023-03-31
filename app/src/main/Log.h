#pragma once

#include <android/log.h>



#define LOGD(...)   __android_log_print(ANDROID_LOG_DEBUG, "NDKTemplateMinimal", __VA_ARGS__)
#define LOGW(...)   __android_log_print(ANDROID_LOG_WARN, "NDKTemplateMinimal", __VA_ARGS__)
#define LOGE(...)   __android_log_print(ANDROID_LOG_ERROR, "NDKTemplateMinimal", __VA_ARGS__)
#define LOGF(...)   __android_log_print(ANDROID_LOG_FATAL, "NDKTemplateMinimal", __VA_ARGS__)