file(GLOB_RECURSE MODULE_SOURCES CONFIGURE_DEPENDS *.cpp *.hpp)

add_library(io STATIC ${MODULE_SOURCES})

target_include_directories(io
    PUBLIC ${CMAKE_SOURCE_DIR}/src
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/System
)
