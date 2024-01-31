#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>
#include <location_data.grpc.pb.h>  //.
#include <location_data.pb.h>
#include <location_service.grpc.pb.h>
#include <location_service.pb.h>  //.
#include <location_subscription.grpc.pb.h>
#include <location_subscription.pb.h>  //.

#include <iostream>
#include <nlohmann/json.hpp>

#include "Locator_server.h"
#include "Subscriber.h"
#include "ZoneTrigger.h"

using json = nlohmann::json;

Locator locator;

std::string ReadJson() {
    std::ifstream file("config.json");
    if (file.is_open()) {
	json j;
	file >> j;

	std::string local_ip = j["grpc"]["local_ip"].get<std::string>();
	int local_port = j["grpc"]["local_port"].get<int>();

	std::string local_address = local_ip + ":" + std::to_string(local_port);

	return local_address;

    } else {
	std::cerr << "Failed to open JSON file: config.json" << std::endl;
	return "";
    }
}

class SubscriberProviderService final : public location::SubscriberProvider::Service {
   public:
    virtual ::grpc::Status SetSubscriber(::grpc::ServerContext *context, const ::location::Subscriber *request,
					 ::location::SetSubscriberReply *response) {
	locator.SetSubscriber(request->id(), request->x(), request->y());
	response->set_code(location::StatusCode::SUCCESS);
	return grpc::Status::OK;
    }
};

class ZoneRequestorService final : public location::ZoneRequestor::Service {
   public:
    virtual ::grpc::Status GetSubscriber(::grpc::ServerContext *context, const ::location::SubscriberId *request,
					 ::location::SubscriberReply *response) {
	std::optional<Subscriber> subscriber;
	subscriber = locator.GetSubscriber(request->id());
	location::Subscriber *sub = new location::Subscriber();
	sub->set_id(subscriber->getId());
	sub->set_x(subscriber->getX());
	sub->set_y(subscriber->getY());
	response->set_allocated_subscriber(sub);
	response->set_code(location::StatusCode::SUCCESS);
	return grpc::Status::OK;
    }

    virtual ::grpc::Status GetSubscriberZones(::grpc::ServerContext *context, const ::location::SubscriberId *request,
					      ::location::SubscriberZonesReply *response) {
	std::vector<int> zones = locator.GetZoneSub(request->id());
	for (int zone_id : zones) {
	    location::ZoneId *zone = response->add_zones();
	    zone->set_id(zone_id);
	}
	response->set_code(location::StatusCode::SUCCESS);
	return grpc::Status::OK;
    }

    virtual ::grpc::Status GetSubscribersInZone(::grpc::ServerContext *context, const ::location::ZoneId *request,
						::location::SubscribersInZoneReply *response) {
	std::vector<std::string> subs = locator.GetSubsInZone(request->id());
	for (std::string i : subs) {
	    location::SubscriberId *subId = response->add_subscribers();
	    subId->set_id(i);
	}
	response->set_code(location::StatusCode::SUCCESS);
	return grpc::Status::OK;
    }
};

class TriggerZoneManagerService final : public location::TriggerZoneManager::Service {
   public:
    virtual ::grpc::Status AddZoneTrigger(::grpc::ServerContext *context, const ::location::ZoneTrigger *request,
					  ::location::NewTriggerReply *response) override {
	int id;
	switch (request->event()) {
	    case location::ZoneTrigger::Event::ZoneTrigger_Event_ALL: {
		id = locator.AddZoneTrigger(request->subscriberid(), request->zoneid(), ZoneTrigger::event::ALL);
		break;
	    }
	    case location::ZoneTrigger::Event::ZoneTrigger_Event_ENTER: {
		id = locator.AddZoneTrigger(request->subscriberid(), request->zoneid(), ZoneTrigger::event::ENTER);
		break;
	    }
	    case location::ZoneTrigger::Event::ZoneTrigger_Event_EXIT: {
		id = locator.AddZoneTrigger(request->subscriberid(), request->zoneid(), ZoneTrigger::event::EXIT);
		break;
	    }
	}
	response->set_code(location::StatusCode::SUCCESS);
	response->set_triggerid(id);
	return grpc::Status::OK;
    }

    virtual ::grpc::Status RemoveZoneTrigger(::grpc::ServerContext *context, const ::location::TriggerId *request,
					     ::location::RemoveTriggerReply *response) {
	locator.RemoveZoneTrigger(request->triggerid());
	response->set_code(location::StatusCode::SUCCESS);
	return grpc::Status::OK;
    }

    virtual ::grpc::Status GetZoneTriggers(::grpc::ServerContext *context, const ::location::Empty *request,
					   ::location::GetZoneTriggersReply *response) override {
	for (const auto &trig : locator.zoneTriggers) {
	    location::ZoneTriggerWithId *withId = response->add_triggers();
	    withId->set_triggerid(trig.second.getID());

	    location::ZoneTrigger *tempTrig = withId->mutable_zonetrigger();
	    tempTrig->set_subscriberid(trig.second.getSubID());
	    tempTrig->set_zoneid(trig.second.getZoneID());

	    switch (trig.second.getEvent()) {
		case ZoneTrigger::event::ALL: {
		    tempTrig->set_event(location::ZoneTrigger::ALL);
		    break;
		}
		case ZoneTrigger::event::ENTER: {
		    tempTrig->set_event(location::ZoneTrigger::ENTER);
		    break;
		}
		case ZoneTrigger::event::EXIT: {
		    tempTrig->set_event(location::ZoneTrigger::EXIT);
		    break;
		}
	    }
	}

	return grpc::Status::OK;
    }

    virtual ::grpc::Status AddProximityTrigger(::grpc::ServerContext *context, const ::location::ProximityTrigger *request,
					       ::location::NewTriggerReply *response) override {
	int id;
	id = locator.AddProxTrigger(request->user1id(), request->user2id(), request->distance());
	response->set_code(location::StatusCode::SUCCESS);
	response->set_triggerid(id);
	return grpc::Status::OK;
    }

    virtual ::grpc::Status RemoveProximityTrigger(::grpc::ServerContext *context, const ::location::TriggerId *request,
						  ::location::RemoveTriggerReply *response) {
	locator.RemoveProxTrigger(request->triggerid());
	response->set_code(location::StatusCode::SUCCESS);
	return grpc::Status::OK;
    }

    virtual ::grpc::Status GetProximityTriggers(::grpc::ServerContext *context, const ::location::Empty *request,
						::location::GetProximityTriggersReply *response) override {
	for (const auto &trig : locator.proxTriggers) {
	    location::ProximityTriggerWithId *withId = response->add_triggers();
	    withId->set_triggerid(trig.second.getID());

	    location::ProximityTrigger *tempTrig = withId->mutable_proximitytrigger();
	    tempTrig->set_user1id(trig.second.getSubscriber1ID());
	    tempTrig->set_user2id(trig.second.getSubscriber2ID());
	    tempTrig->set_distance(trig.second.getDistance());
	}

	return grpc::Status::OK;
    }
};

class TriggerProcessorService final : public location::TriggerProcessor::Service {
   public:
    virtual ::grpc::Status ZoneTriggerEvent(::grpc::ServerContext *context, const ::location::TriggerId *request,
					    ::location::Empty *response) override {
	if (locator.tempZoneTrigId == request->triggerid()) {
	    std::cout << "Zone trigger with ID " << request->triggerid() << " was activated." << std::endl;
	}
	return grpc::Status::OK;
    }

    virtual ::grpc::Status ProximityTriggerEvent(::grpc::ServerContext *context, const ::location::TriggerId *request,
						 ::location::Empty *response) override {
	if (locator.tempProxTrigId == request->triggerid()) {
	    std::cout << "Proximity trigger with ID " << request->triggerid() << " was activated." << std::endl;
	}
	return grpc::Status::OK;
    }
};

int main(int argc, char *argv[]) {
    locator.load("config.json");

    grpc::ServerBuilder builder;
    builder.AddListeningPort(ReadJson(), grpc::InsecureServerCredentials());

    SubscriberProviderService subscriberProviderService;
    builder.RegisterService(&subscriberProviderService);

    ZoneRequestorService zoneRequestorService;
    builder.RegisterService(&zoneRequestorService);

    TriggerZoneManagerService triggerZoneManagerService;
    builder.RegisterService(&triggerZoneManagerService);

    TriggerProcessorService triggerProcessorService;
    builder.RegisterService(&triggerProcessorService);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    server->Wait();

    return 0;
}
