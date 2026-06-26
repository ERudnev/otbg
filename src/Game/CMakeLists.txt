file(GLOB_RECURSE MODULE_SOURCES CONFIGURE_DEPENDS *.cpp *.hpp)

add_library(game STATIC ${MODULE_SOURCES})

target_include_directories(game
    PUBLIC ${CMAKE_SOURCE_DIR}/src
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(game PUBLIC io)
