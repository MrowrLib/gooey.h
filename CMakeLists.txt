cmake_minimum_required(VERSION 3.21)

project(gooey-project LANGUAGES CXX)

# add_executable("TESTING" Examples/Cpp/Test.cpp)

add_subdirectory(gooey)
add_subdirectory(gooey-base)
add_subdirectory(gooey-qt)
add_subdirectory(Examples)

set(JDK_PATH "C:/Program Files/Java/jdk-19")

# To create your own key: keytool -genkey -v -keystore my-release-key.jks -keyalg RSA -keysize 2048 -validity 10000 -alias my-alias

add_custom_target(
    "GenerateAndRunAndroid"
    COMMAND androiddeployqt.exe --output "${CMAKE_SOURCE_DIR}/android-build" --verbose --input "${CMAKE_SOURCE_DIR}/android_deployment_settings.json" --gradle --release
    COMMAND apksigner sign --ks "${CMAKE_SOURCE_DIR}/android-testing-key.jks" --ks-pass pass:testing --key-pass pass:testing --out signed-apk.apk "${CMAKE_SOURCE_DIR}/android-build/build/outputs/apk/release/android-build-release-unsigned.apk"
    COMMAND adb install "${CMAKE_SOURCE_DIR}/build/Android/signed-apk.apk"
    COMMAND adb shell am start -n org.qtproject.example.HelloWorld/org.qtproject.qt.android.bindings.QtActivity
    VERBATIM
)
