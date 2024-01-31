#include "ZoneTrigger.h"

ZoneTrigger::ZoneTrigger(std::string subscriber_id, int zone_id, event event0)
    : subscriber_id(subscriber_id), zone_id(zone_id), event0(event0) {
    std::hash<std::string> hasher;
    std::hash<int> hasher_int;
    std::hash<int> hasher_event;
    size_t id_hash = hasher(subscriber_id) ^ hasher_int(zone_id) ^ hasher_event(static_cast<int>(event0));
    id = static_cast<uint16_t>(id_hash);
}

int ZoneTrigger::getID() const { return id; }

const std::string &ZoneTrigger::getSubID() const { return subscriber_id; }

int ZoneTrigger::getZoneID() const { return zone_id; }

ZoneTrigger::event ZoneTrigger::getEvent() const { return event0; }

void ZoneTrigger::setSubID(const std::string &sub_id) { subscriber_id = sub_id; }

void ZoneTrigger::setZoneID(int new_zone_id) { zone_id = new_zone_id; }

void ZoneTrigger::setEvent(event new_event) { event0 = new_event; }