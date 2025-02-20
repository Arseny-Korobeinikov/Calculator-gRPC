#include <iostream>
#include <grpcpp/grpcpp.h>
#include "calculator.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using calculator::Calculator;
using calculator::Expression;
using calculator::Result;

class CalculatorClient {
public:
    CalculatorClient(std::shared_ptr<Channel> channel)
        : stub_(Calculator::NewStub(channel)) {
    }

    void Compute(const std::string& expression) {
        Expression request;
        request.set_expression(expression);

        Result response;
        ClientContext context;

        Status status = stub_->Compute(&context, request, &response);

        if (!status.ok()) {
            std::cerr << "Error: couldn't connect to the server!" << std::endl;
            std::cerr << "gRPC status: " << status.error_message() << std::endl;
            return;
        }

        if (status.ok() && response.success()) {
            std::cout << "Result: " << response.value() << std::endl;
        }
        else {
            std::cerr << response.message() << std::endl;
        }
    }

private:
    std::unique_ptr<Calculator::Stub> stub_;
};

int main() {
    CalculatorClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    while (true) {
        std::string input;
        std::cout << "Enter an expression (If you want to finish, enter \"exit\"): ";
        std::getline(std::cin, input);
        if (input == "exit") break;
        client.Compute(input);
    }
    return 0; // is optional, compiler will substitute it automatically.
}
