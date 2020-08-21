#pragma once
#include <iostream>
#include <amp.h>
#include <mysql/mysql.h>

using namespace std;


class DB_Connector{
public:
    DB_Connector();
    ~DB_Connector();

    
    bool findTrain(string station, string freight, int cars_count);
    bool send(string station, string freight, int cars_count);
    bool receive(string station, string freight, int cars_count);

private:
    MYSQL* connection, mysql;
};

