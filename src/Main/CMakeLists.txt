file(GLOB_RECURSE MODULE_SOURCES CONFIGURE_DEPENDS *.cpp *.hpp)

add_executable(sw_battle_test ${MODULE_SOURCES})

target_link_libraries(sw_battle_test PRIVATE game)

set_target_properties(sw_battle_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release"
)
