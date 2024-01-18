#pragma once

#include <string>

class Subscriber {
public:
  Subscriber();
  Subscriber(const std::string &newId, int newX, int newY);

  int getX() const;
  int getY() const;
  std::string getId() const;

  void setId(const std::string &newId);
  void setX(int newX);
  void setY(int newY);

private:
  std::string id;
  int x, y;
};
