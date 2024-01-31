# Project XYZ Locator

XYZ Locator is a C++ project designed to manage and locate subscribers within zones. It provides functionalities to add and retrieve subscribers, define zones, and set triggers for specific events.

## Features

- **Subscriber Management:** Add and retrieve subscribers based on their unique IDs.
- **Zone Management:** Add and load zones with specific coordinates and radii.
- **Proximity Triggers:** Define triggers based on the proximity of subscribers.
- **Zone Triggers:** Set triggers for subscribers entering or exiting specific zones.

## Libraries

This project utilizes several libraries to facilitate its functionality. These libraries include:

- **gRPC**: A modern, open-source remote procedure call (RPC) framework that can run anywhere.
- **Hiredis**: A minimalistic C client library for Redis.
- **spdlog**: A header-only logging library for C++.
- **nlohmann_json**: A JSON library for modern C++.
- **gtest**: A C++ testing framework.

## Project Overview

This project is divided into two main parts: the client-side and the server-side. It utilizes Redis as a database.

### Client-side

The client-side implementation includes functionality for interacting with the server and utilizing various features provided by the server.

### Server-side

The server-side implementation is responsible for handling requests from clients, managing data stored in Redis, and performing various operations. It interacts with the database and executes business logic accordingly.

## Usage

To use this project, follow these steps:

1. Clone the repository to your local machine.
2. Ensure you have all the necessary dependencies installed (gRPC, Hiredis, spdlog, nlohmann_json, gtest).
3. Build the project using CMake.
4. Run the server-side component.
5. Utilize the client-side component as needed.

## Testing

For testing the server, a target `test_locator_server` is provided.

## Contributing

Contributions to this project are welcome. Please follow the standard guidelines for contributing, including creating descriptive pull requests and adhering to the project's coding style.
