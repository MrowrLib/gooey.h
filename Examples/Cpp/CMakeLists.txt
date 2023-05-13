# NOTE: To create your own key: keytool -genkey -v -keystore my-release-key.jks -keyalg RSA -keysize 2048 -validity 10000 -alias my-alias

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

# Get the names of all of the examples
file(GLOB EXAMPLES_CPP "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Create a target for each example
foreach(EXAMPLE_CPP ${EXAMPLES_CPP})
    get_filename_component(EXAMPLE_FILENAME ${EXAMPLE_CPP} NAME_WE)
    string(REPLACE "Example - " "" EXAMPLE_NAME "${EXAMPLE_FILENAME}")
    string(REPLACE " " "" EXAMPLE_NAME "${EXAMPLE_NAME}")

    add_library("${EXAMPLE_NAME}" SHARED ${EXAMPLE_CPP})
    target_link_libraries("${EXAMPLE_NAME}" PRIVATE gooey gooey-base gooey-qt Qt6::Core Qt6::Widgets)
    target_include_directories("${EXAMPLE_NAME}" PRIVATE .)
    target_compile_definitions("${EXAMPLE_NAME}" PRIVATE GOOEY_USE_QT)

    add_custom_command(
        TARGET ${EXAMPLE_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -DJSON_FILE=${CMAKE_SOURCE_DIR}/android_deployment_settings.json
                             -DNEW_VALUE=${EXAMPLE_NAME}
                             -P "${CMAKE_SOURCE_DIR}/cmake/rewrite_json.cmake"
        COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_SOURCE_DIR}/android-build"
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:${EXAMPLE_NAME}>" "${CMAKE_SOURCE_DIR}/android-build/libs/arm64-v8a/lib${EXAMPLE_NAME}_arm64-v8a.so"
        COMMAND androiddeployqt.exe --output "${CMAKE_SOURCE_DIR}/android-build" --verbose --input "${CMAKE_SOURCE_DIR}/android_deployment_settings.json" --gradle --release
        COMMAND apksigner sign --ks "${CMAKE_SOURCE_DIR}/android-testing-key.jks" --ks-pass pass:testing --key-pass pass:testing --out signed-apk.apk "${CMAKE_SOURCE_DIR}/android-build/build/outputs/apk/release/android-build-release-unsigned.apk"
        COMMAND adb install "${CMAKE_SOURCE_DIR}/build/Android/Examples/Cpp/signed-apk.apk"
        COMMAND adb shell am start -n org.qtproject.example.${EXAMPLE_NAME}/org.qtproject.qt.android.bindings.QtActivity
        VERBATIM
    )
endforeach()
