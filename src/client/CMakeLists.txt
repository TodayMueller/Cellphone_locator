find_package(Threads)

include(FetchContent)

FetchContent_Declare(
    json 
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.3
)
FetchContent_MakeAvailable(json)

set(SOURCES
    src/main.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_executable(locator_client ${SOURCES})
target_link_libraries(locator_client
    PRIVATE
        myproto
        nlohmann_json::nlohmann_json
)
