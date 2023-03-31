set(ENGINE_TARGET_NAME "Engine")

set(ENGINE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${ENGINE_TARGET_NAME}/Source/")
set(ENGINE_INCLUDE_DIR "${ENGINE_SOURCE_DIR}Include/")
set(ENGINE_RUNTIME_DIR "${ENGINE_SOURCE_DIR}Runtime/")


set(
        ENGINE_INCLUDE_HEADER_FILES
        ${ENGINE_INCLUDE_DIR}Engine.h
)


set(
        ENGINE_CORE_HEADER_FILES

        # Base
        ${ENGINE_RUNTIME_DIR}Core/Base/Enum.h
        ${ENGINE_RUNTIME_DIR}Core/Base/Micro.h
        ${ENGINE_RUNTIME_DIR}Core/Base/Type.h
        # Container
        ${ENGINE_RUNTIME_DIR}Core/Container/DynamicArray.h
        ${ENGINE_RUNTIME_DIR}Core/Container/LinkedList.h
        ${ENGINE_RUNTIME_DIR}Core/Container/LinkedListNode.h
        # Mathematics
        ${ENGINE_RUNTIME_DIR}Core/Mathematics/Color.h
        ${ENGINE_RUNTIME_DIR}Core/Mathematics/Math.h
        ${ENGINE_RUNTIME_DIR}Core/Mathematics/Matrix3.h
        ${ENGINE_RUNTIME_DIR}Core/Mathematics/Matrix3Extension.h
        ${ENGINE_RUNTIME_DIR}Core/Mathematics/Matrix4.h
        ${ENGINE_RUNTIME_DIR}Core/Mathematics/Matrix4Extension.h
        ${ENGINE_RUNTIME_DIR}Core/Mathematics/Vector2.h
        ${ENGINE_RUNTIME_DIR}Core/Mathematics/Vector3.h
        ${ENGINE_RUNTIME_DIR}Core/Mathematics/Vector4.h
        # String
        ${ENGINE_RUNTIME_DIR}Core/String/StringConverter.h
        ${ENGINE_RUNTIME_DIR}Core/String/Unicode.h
        # System
        ${ENGINE_RUNTIME_DIR}Core/System/Allocator.h
        ${ENGINE_RUNTIME_DIR}Core/System/HeapMemory.h
        ${ENGINE_RUNTIME_DIR}Core/System/Memory.h
        ${ENGINE_RUNTIME_DIR}Core/System/Timer.h

        # Header files as module's container
        ${ENGINE_RUNTIME_DIR}Core/Base.h
)

set(
        ENGINE_CORE_SOURCE_FILES

        # Base
        # not existed
        # Container
        ${ENGINE_RUNTIME_DIR}Core/Container/DynamicArray.c
        ${ENGINE_RUNTIME_DIR}Core/Container/LinkedList.c
        ${ENGINE_RUNTIME_DIR}Core/Container/LinkedListNode.c
        # Mathematics
        ${ENGINE_RUNTIME_DIR}Core/Mathematics/Color.c
        ${ENGINE_RUNTIME_DIR}Core/Mathematics/Math.c
        ${ENGINE_RUNTIME_DIR}Core/Mathematics/Matrix3.c
        ${ENGINE_RUNTIME_DIR}Core/Mathematics/Matrix3Extension.c
        ${ENGINE_RUNTIME_DIR}Core/Mathematics/Matrix4.c
        ${ENGINE_RUNTIME_DIR}Core/Mathematics/Matrix4Extension.c
        ${ENGINE_RUNTIME_DIR}Core/Mathematics/Vector2.c
        ${ENGINE_RUNTIME_DIR}Core/Mathematics/Vector3.c
        ${ENGINE_RUNTIME_DIR}Core/Mathematics/Vector4.c
        # String
        ${ENGINE_RUNTIME_DIR}Core/String/StringConverter.c
        ${ENGINE_RUNTIME_DIR}Core/String/Unicode.c
        # System
        ${ENGINE_RUNTIME_DIR}Core/System/Allocator.c
        ${ENGINE_RUNTIME_DIR}Core/System/HeapMemory.c
        ${ENGINE_RUNTIME_DIR}Core/System/Memory.c
        ${ENGINE_RUNTIME_DIR}Core/System/Timer.c
)

set(
        ENGINE_FUNCTION_HEADER_FILES

        # Render
        ${ENGINE_RUNTIME_DIR}Function/Render/Serface.h
        ${ENGINE_RUNTIME_DIR}Function/Render/ImmediateModeUI/AsciiGlyphInfo.h
        ${ENGINE_RUNTIME_DIR}Function/Render/ImmediateModeUI/AsciiLibrary.h
        ${ENGINE_RUNTIME_DIR}Function/Render/ImmediateModeUI/Text.h
)

set(
        ENGINE_FUNCTION_SOURCE_FILES

        # Render
        ${ENGINE_RUNTIME_DIR}Function/Render/Serface.c
        ${ENGINE_RUNTIME_DIR}Function/Render/ImmediateModeUI/AsciiGlyphInfo.c
        ${ENGINE_RUNTIME_DIR}Function/Render/ImmediateModeUI/Text.c
)

set(
        ENGINE_PLATFORM_SPECIAL_HEADER_FILES
        ""
)

set(
        ENGINE_PLATFORM_SPECIAL_SOURCE_FILES
        ""
)

set(
        ENGINE_PLATFORM_HEADER_FILES

        # HAL
        #
        # SAL
        #
        # Windows, Linux and so on..
        ${ENGINE_PLATFORM_SPECIAL_HEADER_FILES}
)

set(
        ENGINE_PLATFORM_SOURCE_FILES

        # HAL
        #
        # SAL
        #
        # Windows, Linux and so on..
        ${ENGINE_PLATFORM_SPECIAL_HEADER_FILES}
)


set(
        ENGINE_RESOURCE_HEADER_FILES
        ${ENGINE_RUNTIME_DIR}Resource/Bitmap.h
        ${ENGINE_RUNTIME_DIR}Resource/Wave.h
)

set(
        ENGINE_RESOURCE_SOURCE_FILES
        ${ENGINE_RUNTIME_DIR}Resource/Bitmap.c
        ${ENGINE_RUNTIME_DIR}Resource/Wave.c
)

set(
        ENGINE_ALL_SOURCE_FILES

        ${ENGINE_INCLUDE_HEADER_FILES}

        # Core
        ${ENGINE_CORE_HEADER_FILES}
        ${ENGINE_CORE_SOURCE_FILES}
        # Function
        ${ENGINE_FUNCTION_HEADER_FILES}
        ${ENGINE_FUNCTION_SOURCE_FILES}
        # Platform
        ${ENGINE_PLATFORM_HEADER_FILES}
        ${ENGINE_PLATFORM_SOURCE_FILES}
        # Resource
        ${ENGINE_RESOURCE_HEADER_FILES}
        ${ENGINE_RESOURCE_SOURCE_FILES}

        # Header files as module's container
        ${ENGINE_RUNTIME_DIR}Core.h
)

# for some IDEs(as Visual Studio)
source_group(TREE "${ENGINE_SOURCE_DIR}../" FILES ${ENGINE_ALL_SOURCE_FILES})


add_library(
        ${ENGINE_TARGET_NAME}
        SHARED
        ${ENGINE_ALL_SOURCE_FILES}
)


target_link_libraries(
        ${ENGINE_TARGET_NAME}
        PRIVATE
        m # for <math.h>
        # OS dependencies
        android
)

target_include_directories(
        ${ENGINE_TARGET_NAME}
        PRIVATE
        "${CMAKE_ANDROID_NDK}/sources"
)