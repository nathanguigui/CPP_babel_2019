#include "Server.hpp"

/*int main()
{
  try
  {
    boost::asio::io_context io_context;
    Server server(io_context);
    server.run();
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}*/

int main(int argc, char *argv[])
{
 try
   {
   boost::asio::io_service io_service;  
   Server server(io_service);
   io_service.run();
   }
 catch(std::exception& e)
   {
   std::cerr << e.what() << std::endl;
   }
 return 0;
}