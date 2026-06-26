file(GLOB_RECURSE MODULE_SOURCES CONFIGURE_DEPENDS *.cpp *.hpp)

add_executable(scenario_runner ${MODULE_SOURCES})

target_link_libraries(scenario_runner PRIVATE NewGame io)

set_target_properties(scenario_runner PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release"
)
