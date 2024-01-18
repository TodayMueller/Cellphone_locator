cmake_minimum_required(VERSION 3.8)
project(locator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

set(FETCHCONTENT_PROTOBUF_TAG v3.12.4)
set(FETCHCONTENT_GRPC_TAG v1.55.0)

FetchContent_Declare(
    protobuf
    GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
    GIT_TAG ${FETCHCONTENT_PROTOBUF_TAG}
)
FetchContent_MakeAvailable(protobuf)

set(ABSL_ENABLE_INSTALL ON)
FetchContent_Declare(
    gRPC
    GIT_REPOSITORY https://github.com/grpc/grpc
    GIT_TAG ${FETCHCONTENT_GRPC_TAG}
)
FetchContent_MakeAvailable(gRPC)

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS
    ${CMAKE_CURRENT_SOURCE_DIR}/protos/location_data.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/protos/location_service.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/protos/location_subscription.proto
)

protobuf_generate_grpc_cpp(GRPC_SRCS GRPC_HDRS
    ${CMAKE_CURRENT_SOURCE_DIR}/protos/location_data.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/protos/location_service.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/protos/location_subscription.proto
)

FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.9.2
)
FetchContent_MakeAvailable(spdlog)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.json ${CMAKE_CURRENT_BINARY_DIR}/config.json COPYONLY)

protobuf_generate_grpc_cpp(
    PROTO_SRCS
    PROTO_HDRS
    location_data.proto
    location_service.proto
    location_subscription.proto
)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_BINARY_DIR}/config.json
    ${PROTO_SRCS}
    ${PROTO_HDRS}
    "main.cpp"
    "Zone.cpp"
    "Subscriber.cpp"
    "Zone.h"
    "Subscriber.h"
    "Locator.cpp"
    "Locator.h"
    "Logger.cpp"
    "Logger.h"
    "ProximityTrigger.h"
    "ProximityTrigger.cpp"
    "ZoneTrigger.h"
    "ZoneTrigger.cpp"
)

add_library(location_proto ${PROTO_SRCS} ${PROTO_HDRS} ${GRPC_SRCS} ${GRPC_HDRS})
target_include_directories(location_proto PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

add_executable(locator ${SOURCES})
target_link_libraries(locator
    PRIVATE
    nlohmann_json::nlohmann_json
    spdlog::spdlog
    location_proto
    protobuf::libprotobuf
    gRPC::grpc++
)
