#pragma once

#include <string>

class ProximityTrigger {
public:
  ProximityTrigger(std::string subscriber1_id, std::string subscriber2_id,
                   int distance);
  ProximityTrigger() = default;

  int getID() const;
  std::string getSubscriber1ID() const;
  std::string getSubscriber2ID() const;
  int getDistance() const;

  void setSubscriber1ID(const std::string &sub1_id);
  void setSubscriber2ID(const std::string &sub2_id);
  void setDistance(int new_distance);

private:
  int id;
  std::string subscriber1_id;
  std::string subscriber2_id;
  int distance;
};