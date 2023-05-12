project(gooey-qt VERSION 0.0.1)

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)
target_link_libraries(${PROJECT_NAME} INTERFACE gooey-base Qt6::Core Qt6::Widgets)
