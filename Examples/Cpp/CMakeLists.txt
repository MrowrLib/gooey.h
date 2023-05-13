# Just add one...

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

add_library(HelloWorld SHARED "Example - Empty Window.cpp")
target_link_libraries(HelloWorld PRIVATE gooey gooey-base gooey-qt Qt6::Core Qt6::Widgets)
target_include_directories(HelloWorld PRIVATE .)
target_compile_definitions(HelloWorld PRIVATE GOOEY_USE_QT)

set(SO_PATH "${CMAKE_BINARY_DIR}/Examples/Cpp/libHelloWorld.so")

# After build, copy the .so to the android-build/libs/arm64-v8a folder
add_custom_command(
    TARGET "HelloWorld"
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${SO_PATH}" "${CMAKE_SOURCE_DIR}/android-build/libs/arm64-v8a/libHelloWorld_arm64-v8a.so"
    COMMENT "Copying .so to android-build/libs/arm64-v8a"
    VERBATIM
)