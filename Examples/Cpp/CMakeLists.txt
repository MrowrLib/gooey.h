# Just add one...

add_executable(EmptyWindow "Example - Empty Window.cpp")
target_link_libraries(EmptyWindow PRIVATE gooey gooey-base gooey-qt)
target_include_directories(EmptyWindow PRIVATE .)
target_compile_definitions(EmptyWindow PRIVATE GOOEY_USE_QT)
