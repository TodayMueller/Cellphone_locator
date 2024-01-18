#include "ZoneTrigger.h"

ZoneTrigger::ZoneTrigger(std::string subscriber_id, int zone_id, event event0)
    : subscriber_id(subscriber_id), zone_id(zone_id), event0(event0) {
  static int nextID = 1;
  id = nextID++;
}

int ZoneTrigger::getID() const { return id; }

const std::string &ZoneTrigger::getSubID() const { return subscriber_id; }

int ZoneTrigger::getZoneID() const { return zone_id; }

ZoneTrigger::event ZoneTrigger::getEvent() const { return event0; }

void ZoneTrigger::setSubID(const std::string &sub_id) {
  subscriber_id = sub_id;
}

void ZoneTrigger::setZoneID(int new_zone_id) { zone_id = new_zone_id; }

void ZoneTrigger::setEvent(event new_event) { event0 = new_event; }
