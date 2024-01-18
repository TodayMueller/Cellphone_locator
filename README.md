# protei

# Project XYZ Locator

XYZ Locator is a C++ project designed to manage and locate subscribers within zones. It provides functionalities to add and retrieve subscribers, define zones, and set triggers for specific events. The project utilizes [nlohmann/json](https://github.com/nlohmann/json), [Google Test (gtest)](https://github.com/google/googletest), and [spdlog](https://github.com/gabime/spdlog) to enhance testing and logging capabilities.

## Features

- **Subscriber Management:** Add and retrieve subscribers based on their unique IDs.
- **Zone Management:** Add and load zones with specific coordinates and radii.
- **Proximity Triggers:** Define triggers based on the proximity of subscribers.
- **Zone Triggers:** Set triggers for subscribers entering or exiting specific zones.

## Code Overview

The project includes a `Locator` class with methods for managing subscribers, zones, and triggers. Here are some key methods:

### `GetSubscriber`

Retrieve a subscriber based on their ID.

### `SetSubscriber`

Set the coordinates for a subscriber and handle zone triggers and proximity triggers accordingly.

### `load`

Load zones from a JSON file and add them to the project.

### `AddZone`

Add a new zone with a unique ID, name, and coordinates.

### `AddProxTrigger`

Add a proximity trigger between two subscribers.

### `AddZoneTrigger`

Add a zone trigger for a subscriber entering or exiting a specific zone.

### `GetSubsInZone`

Retrieve a list of subscriber IDs within a specified zone.

### `GetZoneSub`

Retrieve a list of zone IDs containing a specific subscriber.

### `isPointInside`

Check if a point is inside a specified circle defined by its center and radius.

### `isPointInsideTrigger`

Check if a point is inside the zone associated with a specific trigger.

## Dependencies

- [nlohmann/json](https://github.com/nlohmann/json): A JSON library for C++.
- [Google Test (gtest)](https://github.com/google/googletest): A testing framework for C++.
- [spdlog](https://github.com/gabime/spdlog): A fast C++ logging library.

## Usage

Feel free to integrate this project into your C++ applications for subscriber and zone management. Make sure to include the required dependencies in your build system.

