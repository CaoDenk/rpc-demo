#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include "greeter.grpc.pb.h" // Include the generated header from your .proto file

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;


class GreeterClient {
public:
    GreeterClient(std::shared_ptr<Channel> channel)
        : stub_(Greeter::NewStub(channel)) {}

    // Assembles the client's payload, sends it and presents the response back
    // from the server.
    std::string SayHello(const std::string& user) {
        // Data we are sending to the server.
        HelloRequest request;
        request.set_name(user);

        // Container for the data we expect from the server.
        HelloReply reply;

        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        ClientContext context;

        // The actual RPC.
        Status status = stub_->SayHello(&context, request, &reply);
        
        // Act upon its status.
        if (status.ok()) {
            return reply.message();
        }
        else {
            std::cout << "RPC failed. Error: " << status.error_message() << std::endl;
            return "RPC failed";
        }
    }

private:
    std::unique_ptr<Greeter::Stub> stub_;
};

class CalcClient
{
public:
    CalcClient(std::shared_ptr<Channel> channel)
        : stub_(Calc::NewStub(channel)) {}
    int getsum(int num1,int num2)
    {
        SndNum sndnum;
        sndnum.set_num1(num1);
        sndnum.set_num2(num2);
        ClientContext ctx;
        RecvNum rcv;
        auto status=stub_->GetSum(&ctx, sndnum, &rcv);
        if (status.ok())
        {
            return rcv.num();
        }
        else
        {
            throw std::runtime_error::runtime_error(status.error_message());
        }
    }

private:
    std::unique_ptr<Calc::Stub> stub_;
};

int main(int argc, char** argv) {
    // Instantiate the client. It requires a channel, out of which the actual RPCs
    // are created. This channel models a connection to an endpoint (in this case,
    // localhost on port 50051). We indicate that the channel isn't authenticated
    // (use of InsecureChannelCredentials()).
    GreeterClient greeter(grpc::CreateChannel(
        "localhost:50051", grpc::InsecureChannelCredentials()));
    std::string user("world");
    std::string reply = greeter.SayHello(user);  // The client calls SayHello


    CalcClient c(grpc::CreateChannel( "localhost:50051", grpc::InsecureChannelCredentials()));

    std::cout<< "add res:" << c.getsum(200, 500)<<"\n";

    std::cout << "Greeter received: " << reply << std::endl;

    return 0;
}
