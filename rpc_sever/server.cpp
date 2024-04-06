#include "greeter.grpc.pb.h"
#include <grpcpp/grpcpp.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;


// Extend the generated service base class
class GreeterServiceImpl final : public Greeter::Service {
    Status SayHello(ServerContext* context, const HelloRequest* request,
        HelloReply* reply) override {
        std::string prefix("Hello  from server");
        std::cout<<"size:"<<request->num_size()<<"\n";
        std::cout<<"first"<<request->num()[0];
        
        reply->set_message(prefix + request->name());
        return Status::OK;
    }
};
class CalcServiceImpl final :public Calc::Service
{
    Status GetSum(ServerContext* context, const ::SndNum* request, ::RecvNum* response) override
    {
        int sum=request->num1() + request->num2();
        response->set_num(sum);
        std::cout << "num:\t" << sum << "\n";
        return Status::OK;
    }
     
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    GreeterServiceImpl service;
    CalcServiceImpl calcService;
    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case, it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    builder.RegisterService(&calcService);
    // Finally, assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to return.
    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();
    return 0;
}
