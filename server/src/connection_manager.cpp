#include "../includes/Server.hpp"

std::set<connection_handler::pointer> connections_;

void connection_manager::start(connection_handler::pointer c) 
{
    connections_.insert(c);
    c->start();
}

void connection_manager::stop(connection_handler::pointer c) 
{
    connections_.erase(c);
}

void connection_manager::stop_all() 
{
    connections_.clear();
}