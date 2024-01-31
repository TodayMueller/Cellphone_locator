#pragma once

#include <functional>
#include <string>

class ZoneTrigger {
   public:
    enum class event { ENTER, EXIT, ALL };

    ZoneTrigger(std::string subscriber_id, int zone_id, event event0);

    ZoneTrigger() = default;

    int getID() const;
    const std::string &getSubID() const;
    int getZoneID() const;
    event getEvent() const;

    void setSubID(const std::string &sub_id);
    void setZoneID(int zone_id);
    void setEvent(event event0);

   private:
    uint16_t id;
    std::string subscriber_id;
    int zone_id;
    event event0;
};