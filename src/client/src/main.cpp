#include <grpc/grpc.h>
#include <grpcpp/create_channel.h>
#include <location_data.grpc.pb.h>
#include <location_service.grpc.pb.h>
#include <location_subscription.grpc.pb.h>

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using SubscriberStubPtr = std::unique_ptr<location::SubscriberProvider::Stub>;
using ZoneRequestorStubPtr = std::unique_ptr<location::ZoneRequestor::Stub>;
using TriggerZoneManagerStubPtr = std::unique_ptr<location::TriggerZoneManager::Stub>;
using TriggerProcessorStubPtr = std::unique_ptr<location::TriggerProcessor::Stub>;
using json = nlohmann::json;

std::string ReadJson() {
    std::ifstream file("config.json");
    if (file.is_open()) {
	json j;
	file >> j;

	std::string remote_ip = j["grpc"]["remote_ip"].get<std::string>();
	int remote_port = j["grpc"]["remote_port"].get<int>();

	std::string remote_address = remote_ip + ":" + std::to_string(remote_port);

	return remote_address;

    } else {
	std::cerr << "Failed to open JSON file: config.json" << std::endl;
	return "";
    }
}

void SetSubscriber(const SubscriberStubPtr& stub, const location::Subscriber& subscriber) {
    location::SetSubscriberReply reply;
    ClientContext context;
    Status status = stub->SetSubscriber(&context, subscriber, &reply);
    std::cout << "SetSubscriber: " << reply.code() << std::endl;
}

void GetSubscriber(const ZoneRequestorStubPtr& stub, const location::SubscriberId& subscriberId) {
    location::SubscriberReply reply;
    ClientContext context;
    Status status = stub->GetSubscriber(&context, subscriberId, &reply);
    std::cout << "GetSubscriber: " << reply.code() << std::endl;
}

void GetSubscriberZones(const ZoneRequestorStubPtr& stub, const location::SubscriberId& subscriberId) {
    location::SubscriberZonesReply reply;
    ClientContext context;
    Status status = stub->GetSubscriberZones(&context, subscriberId, &reply);
    std::cout << "GetSubscriberZones: " << reply.code() << std::endl;
}

void GetSubscribersInZone(const ZoneRequestorStubPtr& stub, const location::ZoneId& zoneId) {
    location::SubscribersInZoneReply reply;
    ClientContext context;
    Status status = stub->GetSubscribersInZone(&context, zoneId, &reply);
    std::cout << "GetSubscribersInZone: " << reply.code() << std::endl;
}

int AddZoneTrigger(const TriggerZoneManagerStubPtr& stub, const location::ZoneTrigger& trigger) {
    location::NewTriggerReply reply;
    ClientContext context;
    Status status = stub->AddZoneTrigger(&context, trigger, &reply);
    std::cout << "AddZoneTrigger: " << reply.code() << ", TriggerID: " << reply.triggerid() << std::endl;
    return reply.triggerid();
}

void RemoveZoneTrigger(const TriggerZoneManagerStubPtr& stub, const location::TriggerId& triggerId) {
    location::RemoveTriggerReply reply;
    ClientContext context;
    Status status = stub->RemoveZoneTrigger(&context, triggerId, &reply);
    std::cout << "RemoveZoneTrigger: " << reply.code() << std::endl;
}

void GetZoneTriggers(const TriggerZoneManagerStubPtr& stub, const location::Empty& request) {
    location::GetZoneTriggersReply reply;
    ClientContext context;
    Status status = stub->GetZoneTriggers(&context, request, &reply);
    std::cout << "GetZoneTriggers: " << reply.triggers_size() << std::endl;
}

int AddProximityTrigger(const TriggerZoneManagerStubPtr& stub, const location::ProximityTrigger& trigger) {
    location::NewTriggerReply reply;
    ClientContext context;
    Status status = stub->AddProximityTrigger(&context, trigger, &reply);
    std::cout << "AddProximityTrigger: " << reply.code() << ", TriggerID: " << reply.triggerid() << std::endl;
	return reply.triggerid();
}

void RemoveProximityTrigger(const TriggerZoneManagerStubPtr& stub, const location::TriggerId& triggerId) {
    location::RemoveTriggerReply reply;
    ClientContext context;
    Status status = stub->RemoveProximityTrigger(&context, triggerId, &reply);
    std::cout << "RemoveProximityTrigger: " << reply.code() << std::endl;
}

void GetProximityTriggers(const TriggerZoneManagerStubPtr& stub, const location::Empty& request) {
    location::GetProximityTriggersReply reply;
    ClientContext context;
    Status status = stub->GetProximityTriggers(&context, request, &reply);
    std::cout << "GetProximityTriggers: " << reply.triggers_size() << std::endl;
}

void ZoneTriggerEvent(const TriggerProcessorStubPtr& stub, const location::TriggerId& triggerId) {
    location::Empty reply;
    ClientContext context;
    Status status = stub->ZoneTriggerEvent(&context, triggerId, &reply);
}

void ProximityTriggerEvent(const TriggerProcessorStubPtr& stub, const location::TriggerId& triggerId) {
    location::Empty reply;
    ClientContext context;
    Status status = stub->ProximityTriggerEvent(&context, triggerId, &reply);
}

int main() {
    location::Subscriber sub1, sub2;
    sub1.set_id("1");
    sub1.set_x(30);
    sub1.set_y(44);

    sub2.set_id("2");
    sub2.set_x(3);
    sub2.set_y(6);

    location::SubscriberId subId;
    subId.set_id("1");

    location::ZoneTrigger zoneTrig;
    zoneTrig.set_event(location::ZoneTrigger::Event::ZoneTrigger_Event_ENTER);
    zoneTrig.set_subscriberid("1");
    zoneTrig.set_zoneid(1);

    location::ProximityTrigger proxTrig;
    proxTrig.set_user1id("1");
    proxTrig.set_user2id("2");
    proxTrig.set_distance(10);

    location::ZoneId zoneId;
    zoneId.set_id(1);

    location::TriggerId proxTrigId;
    location::TriggerId zoneTrigId;

    auto channel = grpc::CreateChannel(ReadJson(), grpc::InsecureChannelCredentials());

    SubscriberStubPtr subStub = location::SubscriberProvider::NewStub(channel);
    ZoneRequestorStubPtr zoneStub = location::ZoneRequestor::NewStub(channel);
    TriggerZoneManagerStubPtr trigStub = location::TriggerZoneManager::NewStub(channel);
    TriggerProcessorStubPtr procStub = location::TriggerProcessor::NewStub(channel);

    zoneTrigId.set_triggerid( AddZoneTrigger(trigStub, zoneTrig));
    GetZoneTriggers(trigStub, location::Empty{});

    proxTrigId.set_triggerid( AddProximityTrigger(trigStub, proxTrig));
    GetProximityTriggers(trigStub, location::Empty{});

    sub1.set_x(3);
    sub1.set_y(4);

    SetSubscriber(subStub, sub1);
    ZoneTriggerEvent(procStub, zoneTrigId);

    SetSubscriber(subStub, sub2);
    ProximityTriggerEvent(procStub, proxTrigId);

    GetSubscriber(zoneStub, subId);
    GetSubscriberZones(zoneStub, subId);
    GetSubscribersInZone(zoneStub, zoneId);

    RemoveProximityTrigger(trigStub, proxTrigId);
    RemoveZoneTrigger(trigStub, zoneTrigId);

    return 0;
}
