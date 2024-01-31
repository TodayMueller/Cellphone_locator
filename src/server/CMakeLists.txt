find_package(Threads)

include(FetchContent)

FetchContent_Declare(
    googletest 
    URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
    )
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
    json 
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.3
)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG        v1.13.0
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(
    hiredis
    GIT_REPOSITORY https://github.com/redis/hiredis.git
    GIT_TAG        v1.2.0
    )
FetchContent_MakeAvailable(hiredis)


set(SOURCES
    src/Zone.cpp
    src/Subscriber.cpp
    src/Zone.h
    src/Subscriber.h
    src/Locator_server.cpp
    src/Locator_server.h
    src/Logger.cpp
    src/Logger.h
    src/ProximityTrigger.h
    src/ProximityTrigger.cpp
    src/ZoneTrigger.h
    src/ZoneTrigger.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_executable(locator_server ${SOURCES} src/main.cpp)
target_link_libraries(locator_server
    PRIVATE
        myproto
        nlohmann_json::nlohmann_json
        spdlog::spdlog
        hiredis::hiredis
)

add_executable(test_locator_server ${SOURCES}
    src/tests/unitTests.cpp)
target_link_libraries(test_locator_server PRIVATE gtest_main
    nlohmann_json::nlohmann_json
    spdlog::spdlog 
    hiredis::hiredis
)

include(GoogleTest)
gtest_discover_tests(test_locator_server)
