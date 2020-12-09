//
// Created by lerakrya on 09.12.2020.
//

#include "/home/lerakrya/Документы/GitHub/noskool-server_users/ServerUsers/project/includes/Server.h"

int main(int argc, char* argv[])
{
    std::cout << "hello";
    try
    {

        boost::asio::io_service io_service;

        Server s(io_service, 8081);

        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}