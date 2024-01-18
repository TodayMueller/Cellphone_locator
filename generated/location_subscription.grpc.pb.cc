// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: location_subscription.proto

#include "location_subscription.pb.h"
#include "location_subscription.grpc.pb.h"

#include <functional>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/impl/client_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/sync_stream.h>
namespace location {

static const char* TriggerZoneManager_method_names[] = {
  "/location.TriggerZoneManager/AddZoneTrigger",
  "/location.TriggerZoneManager/RemoveZoneTrigger",
  "/location.TriggerZoneManager/GetZoneTriggers",
  "/location.TriggerZoneManager/AddProximityTrigger",
  "/location.TriggerZoneManager/RemoveProximityTrigger",
  "/location.TriggerZoneManager/GetProximityTriggers",
};

std::unique_ptr< TriggerZoneManager::Stub> TriggerZoneManager::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< TriggerZoneManager::Stub> stub(new TriggerZoneManager::Stub(channel, options));
  return stub;
}

TriggerZoneManager::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_AddZoneTrigger_(TriggerZoneManager_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_RemoveZoneTrigger_(TriggerZoneManager_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_GetZoneTriggers_(TriggerZoneManager_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_AddProximityTrigger_(TriggerZoneManager_method_names[3], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_RemoveProximityTrigger_(TriggerZoneManager_method_names[4], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_GetProximityTriggers_(TriggerZoneManager_method_names[5], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status TriggerZoneManager::Stub::AddZoneTrigger(::grpc::ClientContext* context, const ::location::ZoneTrigger& request, ::location::NewTriggerReply* response) {
  return ::grpc::internal::BlockingUnaryCall< ::location::ZoneTrigger, ::location::NewTriggerReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_AddZoneTrigger_, context, request, response);
}

void TriggerZoneManager::Stub::async::AddZoneTrigger(::grpc::ClientContext* context, const ::location::ZoneTrigger* request, ::location::NewTriggerReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::location::ZoneTrigger, ::location::NewTriggerReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_AddZoneTrigger_, context, request, response, std::move(f));
}

void TriggerZoneManager::Stub::async::AddZoneTrigger(::grpc::ClientContext* context, const ::location::ZoneTrigger* request, ::location::NewTriggerReply* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_AddZoneTrigger_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::location::NewTriggerReply>* TriggerZoneManager::Stub::PrepareAsyncAddZoneTriggerRaw(::grpc::ClientContext* context, const ::location::ZoneTrigger& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::location::NewTriggerReply, ::location::ZoneTrigger, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_AddZoneTrigger_, context, request);
}

::grpc::ClientAsyncResponseReader< ::location::NewTriggerReply>* TriggerZoneManager::Stub::AsyncAddZoneTriggerRaw(::grpc::ClientContext* context, const ::location::ZoneTrigger& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncAddZoneTriggerRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status TriggerZoneManager::Stub::RemoveZoneTrigger(::grpc::ClientContext* context, const ::location::TriggerId& request, ::location::RemoveTriggerReply* response) {
  return ::grpc::internal::BlockingUnaryCall< ::location::TriggerId, ::location::RemoveTriggerReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_RemoveZoneTrigger_, context, request, response);
}

void TriggerZoneManager::Stub::async::RemoveZoneTrigger(::grpc::ClientContext* context, const ::location::TriggerId* request, ::location::RemoveTriggerReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::location::TriggerId, ::location::RemoveTriggerReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_RemoveZoneTrigger_, context, request, response, std::move(f));
}

void TriggerZoneManager::Stub::async::RemoveZoneTrigger(::grpc::ClientContext* context, const ::location::TriggerId* request, ::location::RemoveTriggerReply* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_RemoveZoneTrigger_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::location::RemoveTriggerReply>* TriggerZoneManager::Stub::PrepareAsyncRemoveZoneTriggerRaw(::grpc::ClientContext* context, const ::location::TriggerId& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::location::RemoveTriggerReply, ::location::TriggerId, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_RemoveZoneTrigger_, context, request);
}

::grpc::ClientAsyncResponseReader< ::location::RemoveTriggerReply>* TriggerZoneManager::Stub::AsyncRemoveZoneTriggerRaw(::grpc::ClientContext* context, const ::location::TriggerId& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncRemoveZoneTriggerRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status TriggerZoneManager::Stub::GetZoneTriggers(::grpc::ClientContext* context, const ::location::Empty& request, ::location::GetZoneTriggersReply* response) {
  return ::grpc::internal::BlockingUnaryCall< ::location::Empty, ::location::GetZoneTriggersReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_GetZoneTriggers_, context, request, response);
}

void TriggerZoneManager::Stub::async::GetZoneTriggers(::grpc::ClientContext* context, const ::location::Empty* request, ::location::GetZoneTriggersReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::location::Empty, ::location::GetZoneTriggersReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetZoneTriggers_, context, request, response, std::move(f));
}

void TriggerZoneManager::Stub::async::GetZoneTriggers(::grpc::ClientContext* context, const ::location::Empty* request, ::location::GetZoneTriggersReply* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetZoneTriggers_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::location::GetZoneTriggersReply>* TriggerZoneManager::Stub::PrepareAsyncGetZoneTriggersRaw(::grpc::ClientContext* context, const ::location::Empty& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::location::GetZoneTriggersReply, ::location::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_GetZoneTriggers_, context, request);
}

::grpc::ClientAsyncResponseReader< ::location::GetZoneTriggersReply>* TriggerZoneManager::Stub::AsyncGetZoneTriggersRaw(::grpc::ClientContext* context, const ::location::Empty& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncGetZoneTriggersRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status TriggerZoneManager::Stub::AddProximityTrigger(::grpc::ClientContext* context, const ::location::ProximityTrigger& request, ::location::NewTriggerReply* response) {
  return ::grpc::internal::BlockingUnaryCall< ::location::ProximityTrigger, ::location::NewTriggerReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_AddProximityTrigger_, context, request, response);
}

void TriggerZoneManager::Stub::async::AddProximityTrigger(::grpc::ClientContext* context, const ::location::ProximityTrigger* request, ::location::NewTriggerReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::location::ProximityTrigger, ::location::NewTriggerReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_AddProximityTrigger_, context, request, response, std::move(f));
}

void TriggerZoneManager::Stub::async::AddProximityTrigger(::grpc::ClientContext* context, const ::location::ProximityTrigger* request, ::location::NewTriggerReply* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_AddProximityTrigger_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::location::NewTriggerReply>* TriggerZoneManager::Stub::PrepareAsyncAddProximityTriggerRaw(::grpc::ClientContext* context, const ::location::ProximityTrigger& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::location::NewTriggerReply, ::location::ProximityTrigger, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_AddProximityTrigger_, context, request);
}

::grpc::ClientAsyncResponseReader< ::location::NewTriggerReply>* TriggerZoneManager::Stub::AsyncAddProximityTriggerRaw(::grpc::ClientContext* context, const ::location::ProximityTrigger& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncAddProximityTriggerRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status TriggerZoneManager::Stub::RemoveProximityTrigger(::grpc::ClientContext* context, const ::location::TriggerId& request, ::location::RemoveTriggerReply* response) {
  return ::grpc::internal::BlockingUnaryCall< ::location::TriggerId, ::location::RemoveTriggerReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_RemoveProximityTrigger_, context, request, response);
}

void TriggerZoneManager::Stub::async::RemoveProximityTrigger(::grpc::ClientContext* context, const ::location::TriggerId* request, ::location::RemoveTriggerReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::location::TriggerId, ::location::RemoveTriggerReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_RemoveProximityTrigger_, context, request, response, std::move(f));
}

void TriggerZoneManager::Stub::async::RemoveProximityTrigger(::grpc::ClientContext* context, const ::location::TriggerId* request, ::location::RemoveTriggerReply* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_RemoveProximityTrigger_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::location::RemoveTriggerReply>* TriggerZoneManager::Stub::PrepareAsyncRemoveProximityTriggerRaw(::grpc::ClientContext* context, const ::location::TriggerId& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::location::RemoveTriggerReply, ::location::TriggerId, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_RemoveProximityTrigger_, context, request);
}

::grpc::ClientAsyncResponseReader< ::location::RemoveTriggerReply>* TriggerZoneManager::Stub::AsyncRemoveProximityTriggerRaw(::grpc::ClientContext* context, const ::location::TriggerId& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncRemoveProximityTriggerRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status TriggerZoneManager::Stub::GetProximityTriggers(::grpc::ClientContext* context, const ::location::Empty& request, ::location::GetProximityTriggersReply* response) {
  return ::grpc::internal::BlockingUnaryCall< ::location::Empty, ::location::GetProximityTriggersReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_GetProximityTriggers_, context, request, response);
}

void TriggerZoneManager::Stub::async::GetProximityTriggers(::grpc::ClientContext* context, const ::location::Empty* request, ::location::GetProximityTriggersReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::location::Empty, ::location::GetProximityTriggersReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetProximityTriggers_, context, request, response, std::move(f));
}

void TriggerZoneManager::Stub::async::GetProximityTriggers(::grpc::ClientContext* context, const ::location::Empty* request, ::location::GetProximityTriggersReply* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetProximityTriggers_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::location::GetProximityTriggersReply>* TriggerZoneManager::Stub::PrepareAsyncGetProximityTriggersRaw(::grpc::ClientContext* context, const ::location::Empty& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::location::GetProximityTriggersReply, ::location::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_GetProximityTriggers_, context, request);
}

::grpc::ClientAsyncResponseReader< ::location::GetProximityTriggersReply>* TriggerZoneManager::Stub::AsyncGetProximityTriggersRaw(::grpc::ClientContext* context, const ::location::Empty& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncGetProximityTriggersRaw(context, request, cq);
  result->StartCall();
  return result;
}

TriggerZoneManager::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      TriggerZoneManager_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< TriggerZoneManager::Service, ::location::ZoneTrigger, ::location::NewTriggerReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](TriggerZoneManager::Service* service,
             ::grpc::ServerContext* ctx,
             const ::location::ZoneTrigger* req,
             ::location::NewTriggerReply* resp) {
               return service->AddZoneTrigger(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      TriggerZoneManager_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< TriggerZoneManager::Service, ::location::TriggerId, ::location::RemoveTriggerReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](TriggerZoneManager::Service* service,
             ::grpc::ServerContext* ctx,
             const ::location::TriggerId* req,
             ::location::RemoveTriggerReply* resp) {
               return service->RemoveZoneTrigger(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      TriggerZoneManager_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< TriggerZoneManager::Service, ::location::Empty, ::location::GetZoneTriggersReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](TriggerZoneManager::Service* service,
             ::grpc::ServerContext* ctx,
             const ::location::Empty* req,
             ::location::GetZoneTriggersReply* resp) {
               return service->GetZoneTriggers(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      TriggerZoneManager_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< TriggerZoneManager::Service, ::location::ProximityTrigger, ::location::NewTriggerReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](TriggerZoneManager::Service* service,
             ::grpc::ServerContext* ctx,
             const ::location::ProximityTrigger* req,
             ::location::NewTriggerReply* resp) {
               return service->AddProximityTrigger(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      TriggerZoneManager_method_names[4],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< TriggerZoneManager::Service, ::location::TriggerId, ::location::RemoveTriggerReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](TriggerZoneManager::Service* service,
             ::grpc::ServerContext* ctx,
             const ::location::TriggerId* req,
             ::location::RemoveTriggerReply* resp) {
               return service->RemoveProximityTrigger(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      TriggerZoneManager_method_names[5],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< TriggerZoneManager::Service, ::location::Empty, ::location::GetProximityTriggersReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](TriggerZoneManager::Service* service,
             ::grpc::ServerContext* ctx,
             const ::location::Empty* req,
             ::location::GetProximityTriggersReply* resp) {
               return service->GetProximityTriggers(ctx, req, resp);
             }, this)));
}

TriggerZoneManager::Service::~Service() {
}

::grpc::Status TriggerZoneManager::Service::AddZoneTrigger(::grpc::ServerContext* context, const ::location::ZoneTrigger* request, ::location::NewTriggerReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status TriggerZoneManager::Service::RemoveZoneTrigger(::grpc::ServerContext* context, const ::location::TriggerId* request, ::location::RemoveTriggerReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status TriggerZoneManager::Service::GetZoneTriggers(::grpc::ServerContext* context, const ::location::Empty* request, ::location::GetZoneTriggersReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status TriggerZoneManager::Service::AddProximityTrigger(::grpc::ServerContext* context, const ::location::ProximityTrigger* request, ::location::NewTriggerReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status TriggerZoneManager::Service::RemoveProximityTrigger(::grpc::ServerContext* context, const ::location::TriggerId* request, ::location::RemoveTriggerReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status TriggerZoneManager::Service::GetProximityTriggers(::grpc::ServerContext* context, const ::location::Empty* request, ::location::GetProximityTriggersReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


static const char* TriggerProcessor_method_names[] = {
  "/location.TriggerProcessor/ZoneTriggerEvent",
  "/location.TriggerProcessor/ProximityTriggerEvent",
};

std::unique_ptr< TriggerProcessor::Stub> TriggerProcessor::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< TriggerProcessor::Stub> stub(new TriggerProcessor::Stub(channel, options));
  return stub;
}

TriggerProcessor::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_ZoneTriggerEvent_(TriggerProcessor_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_ProximityTriggerEvent_(TriggerProcessor_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status TriggerProcessor::Stub::ZoneTriggerEvent(::grpc::ClientContext* context, const ::location::TriggerId& request, ::location::Empty* response) {
  return ::grpc::internal::BlockingUnaryCall< ::location::TriggerId, ::location::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_ZoneTriggerEvent_, context, request, response);
}

void TriggerProcessor::Stub::async::ZoneTriggerEvent(::grpc::ClientContext* context, const ::location::TriggerId* request, ::location::Empty* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::location::TriggerId, ::location::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_ZoneTriggerEvent_, context, request, response, std::move(f));
}

void TriggerProcessor::Stub::async::ZoneTriggerEvent(::grpc::ClientContext* context, const ::location::TriggerId* request, ::location::Empty* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_ZoneTriggerEvent_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::location::Empty>* TriggerProcessor::Stub::PrepareAsyncZoneTriggerEventRaw(::grpc::ClientContext* context, const ::location::TriggerId& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::location::Empty, ::location::TriggerId, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_ZoneTriggerEvent_, context, request);
}

::grpc::ClientAsyncResponseReader< ::location::Empty>* TriggerProcessor::Stub::AsyncZoneTriggerEventRaw(::grpc::ClientContext* context, const ::location::TriggerId& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncZoneTriggerEventRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status TriggerProcessor::Stub::ProximityTriggerEvent(::grpc::ClientContext* context, const ::location::TriggerId& request, ::location::Empty* response) {
  return ::grpc::internal::BlockingUnaryCall< ::location::TriggerId, ::location::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_ProximityTriggerEvent_, context, request, response);
}

void TriggerProcessor::Stub::async::ProximityTriggerEvent(::grpc::ClientContext* context, const ::location::TriggerId* request, ::location::Empty* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::location::TriggerId, ::location::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_ProximityTriggerEvent_, context, request, response, std::move(f));
}

void TriggerProcessor::Stub::async::ProximityTriggerEvent(::grpc::ClientContext* context, const ::location::TriggerId* request, ::location::Empty* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_ProximityTriggerEvent_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::location::Empty>* TriggerProcessor::Stub::PrepareAsyncProximityTriggerEventRaw(::grpc::ClientContext* context, const ::location::TriggerId& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::location::Empty, ::location::TriggerId, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_ProximityTriggerEvent_, context, request);
}

::grpc::ClientAsyncResponseReader< ::location::Empty>* TriggerProcessor::Stub::AsyncProximityTriggerEventRaw(::grpc::ClientContext* context, const ::location::TriggerId& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncProximityTriggerEventRaw(context, request, cq);
  result->StartCall();
  return result;
}

TriggerProcessor::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      TriggerProcessor_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< TriggerProcessor::Service, ::location::TriggerId, ::location::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](TriggerProcessor::Service* service,
             ::grpc::ServerContext* ctx,
             const ::location::TriggerId* req,
             ::location::Empty* resp) {
               return service->ZoneTriggerEvent(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      TriggerProcessor_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< TriggerProcessor::Service, ::location::TriggerId, ::location::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](TriggerProcessor::Service* service,
             ::grpc::ServerContext* ctx,
             const ::location::TriggerId* req,
             ::location::Empty* resp) {
               return service->ProximityTriggerEvent(ctx, req, resp);
             }, this)));
}

TriggerProcessor::Service::~Service() {
}

::grpc::Status TriggerProcessor::Service::ZoneTriggerEvent(::grpc::ServerContext* context, const ::location::TriggerId* request, ::location::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status TriggerProcessor::Service::ProximityTriggerEvent(::grpc::ServerContext* context, const ::location::TriggerId* request, ::location::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace location
