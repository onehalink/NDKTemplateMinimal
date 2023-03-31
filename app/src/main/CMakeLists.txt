cmake_minimum_required(VERSION 3.20.0)


set(TARGET_NAME "NDKTemplateMinimal")

set(CMAKE_C_STANDARD 11)

message(${CMAKE_SYSTEM_NAME})

# set Engine
include("Engine.cmake")


set(
        ALL_SOURCE_FILES
        EntryPoint.c
        AppThread.c
        Application.c
)

add_library(
        ${TARGET_NAME}
        SHARED
        ${ALL_SOURCE_FILES}
)

target_link_libraries(
        ${TARGET_NAME}
        PRIVATE

        ${ENGINE_TARGET_NAME}

        # OS dependencies
        android
        log
)

target_include_directories(
        ${TARGET_NAME}
        PRIVATE
        ${ENGINE_INCLUDE_DIR}
        "${CMAKE_ANDROID_NDK}/sources"
)