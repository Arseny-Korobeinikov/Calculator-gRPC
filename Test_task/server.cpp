#include <iostream>
#include <regex>
#include <sstream>
#include <grpcpp/grpcpp.h>
#include "calculator.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using calculator::Calculator;
using calculator::Expression;
using calculator::Result;

class CalculatorServiceImpl final : public Calculator::Service {
public:
    Status Compute(ServerContext* context, const Expression* request, Result* response) override {
        std::string expr = request->expression();
        std::regex regex_pattern(R"(\s*(-?\d+(\.\d+)?)\s*([\+\-\*/])\s*(-?\d+(\.\d+)?)\s*)");

        std::smatch match;
        if (!std::regex_match(expr, match, regex_pattern)) {
            response->set_success(false);
            response->set_message("Error: incorrect expression!");
            return Status::OK;
        }

        double num1 = std::stod(match[1].str());
        std::string operation = match[3].str();
        double num2 = std::stod(match[4].str());

        double result;
        if (operation == "+") {
            result = num1 + num2;
        }
        else if (operation == "-") {
            result = num1 - num2;
        }
        else if (operation == "*") {
            result = num1 * num2;
        }
        else { 
            if (num2 == 0) {
                response->set_success(false);
                response->set_message("Error: division by zero!");
                return Status::OK;
            }
            result = num1 / num2; //There can be no other operation here.
        }

        response->set_success(true);
        response->set_message("OK");
        response->set_value(result);
        return Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    CalculatorServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "The server is running on " << server_address << std::endl;
    server->Wait();
}

int main() {
    RunServer();
    return 0;
}
