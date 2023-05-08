project(HelloWorld)

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

add_executable(${PROJECT_NAME} HelloWorld.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Gooey Gooey.Qt)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
