#include "ProximityTrigger.h"

ProximityTrigger::ProximityTrigger(std::string subscriber1_id, std::string subscriber2_id, int distance)
    : subscriber1_id(subscriber1_id), subscriber2_id(subscriber2_id), distance(distance) {
    std::hash<std::string> hasher;
    std::hash<int> hasher_int;
    size_t id_hash = hasher(subscriber1_id) ^ hasher(subscriber2_id) ^ hasher_int(distance);
    id = static_cast<uint16_t>(id_hash);
}

int ProximityTrigger::getID() const { return id; }

std::string ProximityTrigger::getSubscriber1ID() const { return subscriber1_id; }

std::string ProximityTrigger::getSubscriber2ID() const { return subscriber2_id; }

int ProximityTrigger::getDistance() const { return distance; }

void ProximityTrigger::setSubscriber1ID(const std::string &sub1_id) { subscriber1_id = sub1_id; }

void ProximityTrigger::setSubscriber2ID(const std::string &sub2_id) { subscriber2_id = sub2_id; }

void ProximityTrigger::setDistance(int new_distance) { distance = new_distance; }