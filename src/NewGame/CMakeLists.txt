file(GLOB_RECURSE MODULE_SOURCES CONFIGURE_DEPENDS *.cpp *.hpp)

add_library(NewGame STATIC ${MODULE_SOURCES})

target_include_directories(NewGame
    PUBLIC ${CMAKE_SOURCE_DIR}/src
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)
