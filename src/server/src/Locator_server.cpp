#include "Locator_server.h"

Locator::Locator() { redis = redisConnect("127.0.0.1", 6379); }

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
		    logger->warn("load: Invalid zone data in JSON. Details: {}", e.what());
		}
	    }
	} else {
	    logger->warn("load: 'zones' array not found or invalid in JSON.");
	}
    } catch (const std::exception &e) {
	logger->error("load: Error reading JSON: {}", e.what());
    }
}

void Locator::GetFromDB() {
    std::string subId, proxSub1, proxSub2, zoneSub;
    int subX, subY, proxDist, zoneId, zoneEvent;
    ZoneTrigger::event event;

    redisReply *keysReply = (redisReply *)redisCommand(redis, "KEYS Prox*");

    for (size_t i = 0; i < keysReply->elements; ++i) {
	redisReply *keyReply = keysReply->element[i];
	std::string key = keyReply->str;

	redisReply *ProxTrigReply = (redisReply *)redisCommand(redis, "HVALS %s", key.c_str());

	proxSub1 = ProxTrigReply->element[1]->str;
	proxSub2 = ProxTrigReply->element[2]->str;
	proxDist = std::stoi(ProxTrigReply->element[3]->str);

	ProximityTrigger proxTrigger(proxSub1, proxSub2, proxDist);
	proxTriggers[proxTrigger.getID()] = proxTrigger;

	freeReplyObject(ProxTrigReply);
    }

    keysReply = (redisReply *)redisCommand(redis, "KEYS Zone*");

    for (size_t i = 0; i < keysReply->elements; ++i) {
	redisReply *keyReply = keysReply->element[i];
	std::string key = keyReply->str;

	redisReply *ZoneTrigReply = (redisReply *)redisCommand(redis, "HVALS %s", key.c_str());

	zoneSub = ZoneTrigReply->element[1]->str;
	zoneId = std::stoi(ZoneTrigReply->element[2]->str);
	zoneEvent = std::stoi(ZoneTrigReply->element[3]->str);

	switch (zoneEvent) {
	    case 0:
		event = ZoneTrigger::event::ENTER;
		break;
	    case 1:
		event = ZoneTrigger::event::EXIT;
		break;
	    case 2:
		event = ZoneTrigger::event::ALL;
		break;
	}

	ZoneTrigger zoneTrigger(zoneSub, zoneId, event);
	zoneTriggers[zoneTrigger.getID()] = zoneTrigger;

	freeReplyObject(ZoneTrigReply);
    }

    keysReply = (redisReply *)redisCommand(redis, "KEYS Sub*");

    for (size_t i = 0; i < keysReply->elements; ++i) {
	redisReply *keyReply = keysReply->element[i];
	std::string key = keyReply->str;

	redisReply *subscriberReply = (redisReply *)redisCommand(redis, "HVALS %s", key.c_str());

	subId = subscriberReply->element[0]->str;
	subX = std::stoi(subscriberReply->element[1]->str);
	subY = std::stoi(subscriberReply->element[2]->str);

	SetSubscriber(subId, subX, subY);

	freeReplyObject(subscriberReply);
    }

    freeReplyObject(keysReply);
}

void Locator::SetSubscriber(const std::string &id, int x, int y) {
    auto logger = logger1.getLogger();
    logger->info("SetSubscriber: Subscriber with ID '{}' at ({}, {}).", id, x, y);

    tempProxTrigId = 0;
    tempZoneTrigId = 0;

    zoneTrigProc(id,x,y);

    auto it = subscribers.find(id);
    if (it == subscribers.end()) {
	Subscriber newSubscriber(id, x, y);
	subscribers[id] = newSubscriber;
    } else {
	it->second.setX(x);
	it->second.setY(y);
    }

    redisReply *reply = (redisReply *)redisCommand(redis, "HMSET Subscriber:%s id %s x %d y %d", id.c_str(), id.c_str(), x, y);
    freeReplyObject(reply);

    proxTrigProc(id);
}

void Locator::zoneTrigProc(const std::string &id, int x, int y) {
    auto logger = logger1.getLogger();
    for (const auto &pair : zoneTriggers) {
	const ZoneTrigger &trigger = pair.second;

	if (trigger.getSubID() == id) {
	    const auto &subZones = GetZoneSub(trigger.getSubID());
	    auto subZonesIt = std::find(subZones.begin(), subZones.end(), trigger.getZoneID());

	    switch (trigger.getEvent()) {
		case ZoneTrigger::event::ENTER:
		    if (subZonesIt == subZones.end() && isPointInsideTrigger(x, y, trigger)) {
			tempZoneTrigId = trigger.getID();
			logger->info("TriggerZone: ENTER trigger for Subscriber {} in Zone {}.", id, trigger.getZoneID());
			logger->debug("TriggerZone: Finished the function.");
		    }
		    break;

		case ZoneTrigger::event::EXIT:
		    if (subZonesIt != subZones.end() && !isPointInsideTrigger(x, y, trigger)) {
			tempZoneTrigId = trigger.getID();
			logger->info("TriggerZone: EXIT trigger for Subscriber {} in Zone {}.", id, trigger.getZoneID());
			logger->debug("TriggerZone: Finished the function.");
		    }
		    break;

		case ZoneTrigger::event::ALL:
		    if ((subZonesIt == subZones.end() && isPointInsideTrigger(x, y, trigger)) ||
			(subZonesIt != subZones.end() && !isPointInsideTrigger(x, y, trigger))) {
			tempZoneTrigId = trigger.getID();
			logger->info("TriggerZone: ENTER/EXIT trigger for Subscriber {} in Zone {}.", id, trigger.getZoneID());
			logger->debug("TriggerZone: Finished the function.");
		    }
		    break;
	    }
	}
    }
}

bool Locator::isPointInsideTrigger(int x, int y, const ZoneTrigger &trigger) {
    auto zoneIt = zones.find(trigger.getZoneID());
    if (zoneIt != zones.end()) {
	const Zone &zone = zoneIt->second;
	return isPointInside(x, y, zone.getX(), zone.getY(), zone.getRadius());
    }
    return false;
}

bool Locator::isPointInside(int pointX, int pointY, int centerX, int centerY, int radius) {
    double distance = std::hypot(pointX - centerX, pointY - centerY);
    return distance <= radius;
}

void Locator::proxTrigProc(const std::string &id) {
    auto logger = logger1.getLogger();

    for (const auto &pair : proxTriggers) {
	const ProximityTrigger &trigger = pair.second;

	if (trigger.getSubscriber1ID() == id || trigger.getSubscriber2ID() == id) {
	    auto sub1It = subscribers.find(trigger.getSubscriber1ID());
	    auto sub2It = subscribers.find(trigger.getSubscriber2ID());

	    if (sub1It != subscribers.end() && sub2It != subscribers.end()) {
		const Subscriber &sub1 = sub1It->second;
		const Subscriber &sub2 = sub2It->second;

		double distanceBetweenPoints = std::hypot(sub2.getX() - sub1.getX(), sub2.getY() - sub1.getY());

		if (distanceBetweenPoints <= trigger.getDistance()) {
		    tempProxTrigId = trigger.getID();
		    logger->info(
			"ProximityTrigger: Triggered for Subscribers {} and {} at "
			"distance {} or closer.",
			trigger.getSubscriber1ID(), trigger.getSubscriber2ID(), trigger.getDistance());
		    logger->debug("ProximityTrigger: Finished the function.");
		}
	    } else {
		logger->warn(
		    "ProximityTrigger: One or both Subscribers not found for Trigger "
		    "with IDs {} and {}.",
		    trigger.getSubscriber1ID(), trigger.getSubscriber2ID());
	    }
	}
    }
}

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

void Locator::AddZone(int id, std::string name, int x, int y, int radius) {
    auto it = zones.find(id);
    auto logger = logger1.getLogger();

    if (it == zones.end()) {
	Zone newZone(id, name, x, y, radius);
	zones[id] = newZone;
	logger->debug("AddZone: Zone added with ID '{}'.", id);
    }
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
		logger->debug("GetSubsInZone: Subscriber with ID '{}' is in Zone '{}'.", subscriber.first, zoneId);
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
		logger->debug("GetZoneSub: Zone with ID '{}' contains Subscriber '{}'.", zone.first, subId);
	    }
	}
    }

    return result;
}

int Locator::AddProxTrigger(std::string sub1, std::string sub2, int distance) {
    ProximityTrigger proxTrigger(sub1, sub2, distance);
    proxTriggers[proxTrigger.getID()] = proxTrigger;

    redisReply *reply = (redisReply *)redisCommand(redis, "HMSET ProximityTrigger:%i id %i idSub1 %s idSub2 %s dist %i",
						   proxTrigger.getID(), proxTrigger.getID(), proxTrigger.getSubscriber1ID().c_str(),
						   proxTrigger.getSubscriber2ID().c_str(), proxTrigger.getDistance());

    freeReplyObject(reply);

    auto logger = logger1.getLogger();
    logger->info("AddProxTrigger: ProximityTrigger added with ID '{}'.", proxTrigger.getID());
    return proxTrigger.getID();
}

int Locator::AddZoneTrigger(std::string subID, int zoneID, ZoneTrigger::event event0) {
    ZoneTrigger zoneTrigger(subID, zoneID, event0);
    zoneTriggers[zoneTrigger.getID()] = zoneTrigger;

    int eventInt;

    switch (event0) {
	case ZoneTrigger::event::ENTER:
	    eventInt = 0;
	    break;
	case ZoneTrigger::event::EXIT:
	    eventInt = 1;
	    break;
	case ZoneTrigger::event::ALL:
	    eventInt = 2;
	    break;
    }

    redisReply *reply = (redisReply *)redisCommand(redis, "HMSET ZoneTrigger:%i id %i idSub %s idZone %i event %i", zoneTrigger.getID(),
						   zoneTrigger.getID(), zoneTrigger.getSubID().c_str(), zoneTrigger.getZoneID(), eventInt);

    freeReplyObject(reply);

    auto logger = logger1.getLogger();
    logger->info("AddZoneTrigger: ZoneTrigger added with ID '{}'.", zoneTrigger.getID());
    return zoneTrigger.getID();
}

void Locator::RemoveProxTrigger(int id) {
    auto it = proxTriggers.find(id);
    if (it != proxTriggers.end()) {
	proxTriggers.erase(it);
	auto logger = logger1.getLogger();
	logger->info("RemoveProxTrigger: ProximityTrigger with ID '{}' removed.", id);

	std::string key = "ProximityTrigger:" + std::to_string(id);
	redisReply *reply = (redisReply *)redisCommand(redis, "DEL %s", key.c_str());
	freeReplyObject(reply);

    } else {
	auto logger = logger1.getLogger();
	logger->warn("RemoveProxTrigger: ProximityTrigger with ID '{}' not found.", id);
    }
}

void Locator::RemoveZoneTrigger(int id) {
    auto it = zoneTriggers.find(id);
    if (it != zoneTriggers.end()) {
	zoneTriggers.erase(it);
	auto logger = logger1.getLogger();
	logger->info("RemoveZoneTrigger: ZoneTrigger with ID '{}' removed.", id);

	std::string key = "ZoneTrigger:" + std::to_string(id);
	redisReply *reply = (redisReply *)redisCommand(redis, "DEL %s", key.c_str());
	freeReplyObject(reply);

    } else {
	auto logger = logger1.getLogger();
	logger->warn("RemoveZoneTrigger: ZoneTrigger with ID '{}' not found.", id);
    }
}

Locator::~Locator() {
    if (redis != NULL) {
	redisFree(redis);
    }
}
