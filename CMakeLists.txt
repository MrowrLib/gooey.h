cmake_minimum_required(VERSION 3.21)
project(micro_ui VERSION 0.1.0 LANGUAGES CXX)
set(namespace MrowrLib)

option(BUILD_EXAMPLE "Build the example target" ON)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    install(DIRECTORY include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
endif()

install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${namespace}::
    DESTINATION share/${PROJECT_NAME}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

string(CONCAT config_cmake_in
    "@PACKAGE_INIT@\n"
    "include(CMakeFindDependencyMacro)\n"
    "find_dependency(_Log_ CONFIG)\n"
    "include(\"\${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}Targets.cmake\")\n"
)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake.in" "${config_cmake_in}")

configure_package_config_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION share/${PROJECT_NAME}
    PATH_VARS CMAKE_INSTALL_PREFIX
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION share/${PROJECT_NAME}
)

if(BUILD_EXAMPLE)
    find_package(string_format CONFIG REQUIRED)

    # -- [qt]
    find_package(Qt6 COMPONENTS Core Widgets REQUIRED)
    add_executable(Qt-Example Example.cpp)
    target_compile_features(Qt-Example PRIVATE cxx_std_20)
    set_target_properties(Qt-Example PROPERTIES WIN32_EXECUTABLE TRUE)
    target_link_libraries(Qt-Example PRIVATE ${PROJECT_NAME} Qt6::Core Qt6::Widgets MrowrLib::string_format)
endif()
