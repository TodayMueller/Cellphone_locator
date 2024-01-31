#pragma once

#include <hiredis.h>
#include <math.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>

#include "Logger.h"
#include "ProximityTrigger.h"
#include "Subscriber.h"
#include "Zone.h"
#include "ZoneTrigger.h"

class Locator {
   public:
    Locator();

    std::unordered_map<std::string, Subscriber> subscribers;
    std::unordered_map<int, Zone> zones;
    std::unordered_map<int, ProximityTrigger> proxTriggers;
    std::unordered_map<int, ZoneTrigger> zoneTriggers;
    std::unordered_map<int, std::vector<std::string>> subInZone;
    Logger logger1 = Logger("config.json");

    int tempZoneTrigId;
    int tempProxTrigId;

    void SetSubscriber(const std::string &id, int x, int y);

    std::optional<Subscriber> GetSubscriber(const std::string &);

    void from_json(const nlohmann::json &j, Zone &zone);
    void load(const std::string &filename);
    void GetFromDB();

    void AddZone(int id, std::string name, int x, int y, int radius);

    std::vector<std::string> GetSubsInZone(int zoneId);
    std::vector<int> GetZoneSub(const std::string &);

    int AddProxTrigger(std::string sub1, std::string sub2, int distance);
    int AddZoneTrigger(std::string subID, int zoneID, ZoneTrigger::event event0);

    void RemoveZoneTrigger(int id);
    void RemoveProxTrigger(int id);

    bool isPointInside(int pointX, int pointY, int centerX, int centerY, int radius);
    bool isPointInsideTrigger(int x, int y, const ZoneTrigger &trigger);

    void zoneTrigProc(const std::string &id, int x, int y);
    void proxTrigProc(const std::string &id);

    ~Locator();

   private:
    redisContext *redis;
};