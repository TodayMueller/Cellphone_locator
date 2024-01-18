#include "Locator.h"

std::optional<Subscriber> Locator::GetSubscriber(const std::string &id) {
  auto it = subscribers.find(id);
  auto logger = logger1.getLogger();

  if (it != subscribers.end()) {
    logger->info("GetSubscriber: Subscriber with ID '{}' found.", id);
    return it->second;
  } else {
    logger->warn("GetSubscriber: Subscriber with ID '{}' not found.", id);
    return std::nullopt;
  }
}

void Locator::SetSubscriber(const std::string &id, int x, int y) {
  auto logger = logger1.getLogger();

  logger->info("SetSubscriber: Subscriber with ID '{}' at ({}, {}).", id, x, y);

  for (const auto &pair : zoneTriggers) {
    const ZoneTrigger &trigger = pair.second;

    if (trigger.getSubID() == id) {
      const auto &subZones = GetZoneSub(trigger.getSubID());
      auto subZonesIt =
          std::find(subZones.begin(), subZones.end(), trigger.getZoneID());

      switch (trigger.getEvent()) {
      case ZoneTrigger::event::ENTER:
        if (subZonesIt == subZones.end() &&
            isPointInsideTrigger(x, y, trigger)) {
          logger->info(
              "TriggerZone: ENTER trigger for Subscriber {} in Zone {}.", id,
              trigger.getZoneID());
          logger->debug("TriggerZone: Finished the function.");
        }
        break;

      case ZoneTrigger::event::EXIT:
        if (subZonesIt != subZones.end() &&
            !isPointInsideTrigger(x, y, trigger)) {
          logger->info(
              "TriggerZone: EXIT trigger for Subscriber {} in Zone {}.", id,
              trigger.getZoneID());
          logger->debug("TriggerZone: Finished the function.");
        }
        break;

      case ZoneTrigger::event::ALL:
        if ((subZonesIt == subZones.end() &&
             isPointInsideTrigger(x, y, trigger)) ||
            (subZonesIt != subZones.end() &&
             !isPointInsideTrigger(x, y, trigger))) {
          logger->info(
              "TriggerZone: ENTER/EXIT trigger for Subscriber {} in Zone {}.",
              id, trigger.getZoneID());
          logger->debug("TriggerZone: Finished the function.");
        }
        break;
      }
    }
  }

  auto it = subscribers.find(id);

  if (it == subscribers.end()) {
    Subscriber newSubscriber(id, x, y);
    subscribers[id] = newSubscriber;
  } else {
    it->second.setX(x);
    it->second.setY(y);
  }

  for (const auto &pair : proxTriggers) {
    const ProximityTrigger &trigger = pair.second;

    if (trigger.getSubscriber1ID() == id || trigger.getSubscriber2ID() == id) {
      auto sub1It = subscribers.find(trigger.getSubscriber1ID());
      auto sub2It = subscribers.find(trigger.getSubscriber2ID());

      if (sub1It != subscribers.end() && sub2It != subscribers.end()) {
        const Subscriber &sub1 = sub1It->second;
        const Subscriber &sub2 = sub2It->second;

        double distanceBetweenPoints =
            std::hypot(sub2.getX() - sub1.getX(), sub2.getY() - sub1.getY());

        if (distanceBetweenPoints <= trigger.getDistance()) {
          logger->info("ProximityTrigger: Triggered for Subscribers {} and {} "
                       "at distance {} or closer.",
                       trigger.getSubscriber1ID(), trigger.getSubscriber2ID(),
                       trigger.getDistance());
          logger->debug("ProximityTrigger: Finished the function.");
        }
      } else {
        logger->warn("ProximityTrigger: One or both Subscribers not found for "
                     "Trigger with IDs {} and {}.",
                     trigger.getSubscriber1ID(), trigger.getSubscriber2ID());
      }
    }
  }
}

void Locator::load(const std::string &inp) {
  auto logger = logger1.getLogger();

  try {
    nlohmann::json json;
    std::ifstream file(inp);
    file >> json;

    if (json.contains("zones") && json["zones"].is_array()) {
      for (const auto &zoneData : json["zones"]) {
        try {
          Zone newZone(zoneData);
          auto it = zones.find(newZone.getId());

          if (it == zones.end()) {
            zones[newZone.getId()] = newZone;
            logger->info("load: Zone loaded with ID '{}'.", newZone.getId());
          }
        } catch (const nlohmann::json::exception &e) {
          logger->warn("load: Invalid zone data in JSON. Details: {}",
                       e.what());
        }
      }
    } else {
      logger->warn("load: 'zones' array not found or invalid in JSON.");
    }
  } catch (const std::exception &e) {
    logger->error("load: Error reading JSON: {}", e.what());
  }
}

void Locator::AddZone(int id, std::string name, int x, int y, int radius) {
  auto it = zones.find(id);
  auto logger = logger1.getLogger();

  if (it == zones.end()) {
    Zone newZone(id, name, x, y, radius);
    zones[id] = newZone;
    logger->debug("AddZone: Zone added with ID '{}'.", id);
  }
}

void Locator::AddProxTrigger(std::string sub1, std::string sub2, int distance) {
  ProximityTrigger proxTrigger(sub1, sub2, distance);
  proxTriggers[proxTrigger.getID()] = proxTrigger;

  auto logger = logger1.getLogger();
  logger->info("AddProxTrigger: ProximityTrigger added with ID '{}'.",
               proxTrigger.getID());
}

void Locator::AddZoneTrigger(std::string subID, int zoneID,
                             ZoneTrigger::event event0) {
  ZoneTrigger zoneTrigger(subID, zoneID, event0);
  zoneTriggers[zoneTrigger.getID()] = zoneTrigger;

  auto logger = logger1.getLogger();
  logger->info("AddZoneTrigger: ZoneTrigger added with ID '{}'.",
               zoneTrigger.getID());
}

std::vector<std::string> Locator::GetSubsInZone(int zoneId) {
  auto logger = logger1.getLogger();

  auto cachedResult = subInZone.find(zoneId);
  if (cachedResult != subInZone.end()) {
    logger->debug("GetSubsInZone: Using cached result for Zone '{}'.", zoneId);
    return cachedResult->second;
  }

  std::vector<std::string> result;
  auto it = zones.find(zoneId);

  if (it != zones.end()) {
    int centerX = it->second.getX();
    int centerY = it->second.getY();
    int radius = it->second.getRadius();
    for (const auto &subscriber : subscribers) {
      int pointX = subscriber.second.getX();
      int pointY = subscriber.second.getY();
      if (isPointInside(pointX, pointY, centerX, centerY, radius)) {
        result.push_back(subscriber.first);
        logger->debug("GetSubsInZone: Subscriber with ID '{}' is in Zone '{}'.",
                      subscriber.first, zoneId);
      }
    }
    subInZone[zoneId] = result;
  }

  return result;
}

std::vector<int> Locator::GetZoneSub(const std::string &subId) {
  std::vector<int> result;
  auto it = subscribers.find(subId);
  auto logger = logger1.getLogger();

  if (it != subscribers.end()) {
    int pointX = it->second.getX();
    int pointY = it->second.getY();
    for (const auto &zone : zones) {
      int centerX = zone.second.getX();
      int centerY = zone.second.getY();
      int radius = zone.second.getRadius();
      if (isPointInside(pointX, pointY, centerX, centerY, radius)) {
        result.push_back(zone.first);
        logger->debug("GetZoneSub: Zone with ID '{}' contains Subscriber '{}'.",
                      zone.first, subId);
      }
    }
  }

  return result;
}

bool Locator::isPointInside(int pointX, int pointY, int centerX, int centerY,
                            int radius) {
  double distance = std::hypot(pointX - centerX, pointY - centerY);
  return distance <= radius;
}

bool Locator::isPointInsideTrigger(int x, int y, const ZoneTrigger &trigger) {
  auto zoneIt = zones.find(trigger.getZoneID());
  if (zoneIt != zones.end()) {
    const Zone &zone = zoneIt->second;
    return isPointInside(x, y, zone.getX(), zone.getY(), zone.getRadius());
  }
  return false;
}
