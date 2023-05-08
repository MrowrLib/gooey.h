project(HelloWorld)

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

# add_executable(${PROJECT_NAME} HelloWorld.cpp)
add_library(${PROJECT_NAME} SHARED HelloWorld.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Gooey Gooey.Qt)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

set(ANDROID_DEPLOY_QT_EXE "C:/QtFull/Tools/QtDesignStudio/qt6_design_studio_reduced_version/bin/androiddeployqt.exe")
set(JDK_PATH "C:/Program Files/Java/jdk-19")
set(ANDROID_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/android-build")

add_custom_target(${PROJECT_NAME}_APK
    COMMAND ${ANDROID_DEPLOY_QT_EXE} --output ${ANDROID_BUILD_DIR} --no-build --verbose --input ${CMAKE_BINARY_DIR}/Examples/${PROJECT_NAME}/lib${PROJECT_NAME}.so
    COMMAND ${CMAKE_COMMAND} -E env "JAVA_HOME=${JDK_PATH}" ${ANDROID_BUILD_DIR}/gradlew assembleRelease
    WORKING_DIRECTORY ${ANDROID_BUILD_DIR}
    COMMENT "Generating APK..."
    DEPENDS ${PROJECT_NAME}
)