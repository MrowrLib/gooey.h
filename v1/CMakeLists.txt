cmake_minimum_required(VERSION 3.21)
project(gooey VERSION 0.1.0 LANGUAGES CXX)
set(namespace MrowrLib)

option(BUILD_EXAMPLE "Build the example target" ON)
option(BUILD_EXAMPLE_QT "Build the Qt example" OFF) # turn on to enable Qt
option(BUILD_EXAMPLE_NANA "Build the Nana example" OFF)
option(BUILD_EXAMPLE_WX "Build the wxWidgets example" OFF)

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

    add_executable(Example Example.cpp)
    target_compile_features(Example PRIVATE cxx_std_20)
    set_target_properties(Example PROPERTIES WIN32_EXECUTABLE TRUE)
    target_link_libraries(Example PRIVATE ${PROJECT_NAME} string_format::string_format)

    if(nana IN_LIST VCPKG_MANIFEST_FEATURES)
        find_package(unofficial-nana CONFIG REQUIRED)
        target_link_libraries(Example PRIVATE unofficial::nana::nana)
    endif()

    if(wxwidgets IN_LIST VCPKG_MANIFEST_FEATURES)
        find_package(wxWidgets CONFIG REQUIRED)
        target_link_libraries(Example PRIVATE wx::core wx::base)
    endif()
endif()
