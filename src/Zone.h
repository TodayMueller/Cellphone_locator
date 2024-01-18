#pragma once

#include <nlohmann/json.hpp>
#include <string>

class Zone {
public:
  Zone();
  Zone(const nlohmann::json &j);
  Zone(int newId, const std::string &newName, int newX, int newY,
       int newRadius);

  int getId() const;
  std::string getName() const;
  int getX() const;
  int getY() const;
  int getRadius() const;

private:
  int id;
  std::string name;
  int x, y, radius;
};