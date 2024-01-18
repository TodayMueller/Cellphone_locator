#include "Zone.h"
#include <nlohmann/json.hpp>

Zone::Zone() {}

Zone::Zone(const nlohmann::json &j) {
  j.at("id").get_to(id);
  j.at("name").get_to(name);
  j.at("x").get_to(x);
  j.at("y").get_to(y);
  j.at("radius").get_to(radius);
}

Zone::Zone(int newId, const std::string &newName, int newX, int newY,
           int newRadius)
    : id(newId), name(newName), x(newX), y(newY), radius(newRadius) {}

int Zone::getId() const { return id; }

std::string Zone::getName() const { return name; }

int Zone::getX() const { return x; }

int Zone::getY() const { return y; }

int Zone::getRadius() const { return radius; }
