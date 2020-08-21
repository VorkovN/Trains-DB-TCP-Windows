#include "DB_Connector.h"


DB_Connector::DB_Connector() {
	mysql_init(&mysql);
    connection = mysql_real_connect(&mysql, "localhost",
        "vorkov2", "*****", "Trains", 3306, 0, 0);
    if (connection == NULL) {
        throw exception("Error connection to database");
    }
}

DB_Connector::~DB_Connector(){
    mysql_close(connection);
}

bool DB_Connector::findTrain(string station, string freight, int cars_count) {

    const char* ch = ("SELECT Quantity FROM stations WHERE Station = '" + station + "' AND Freight = '" + freight + "' AND Cars_count = " + to_string(cars_count)).c_str();

    if (mysql_query(connection, ch) != 0) {
        cout << "Find error" << endl;
        return false;
    }
    MYSQL_RES* result = mysql_store_result(connection);
    MYSQL_ROW row = mysql_fetch_row(result);
    if (atoi(row[0]) < 1) {
        cout << "Find error" << endl;
        return false;
    }
    mysql_free_result(result);

    return true;
};

bool DB_Connector::send(string station, string freight, int cars_count) {

    const char* ch = ("UPDATE stations SET Quantity = Quantity - 1 WHERE Station = '" + station + "' AND Freight = '" + freight + "' AND Cars_count = " + to_string(cars_count)).c_str();

    if (mysql_query(connection, ch) != 0) {
        cout << "Send error" << endl;
        return false;
    }
    if (mysql_affected_rows(&mysql) != 1) cout << "Send error 2" << endl;

    return true;
};

bool DB_Connector::receive(string station, string freight, int cars_count) {

    const char* ch = ("UPDATE stations SET Quantity = Quantity + 1 WHERE Station = '" + station + "' AND Freight = '" + freight + "' AND Cars_count = " + to_string(cars_count) ).c_str();

    if (mysql_query(connection, ch) != 0) {
        cout << "Receive error" << endl;
        return false;
    }
    if (mysql_affected_rows(&mysql) != 1) {
        const char* insert = ("INSERT INTO stations (Station, Freight, Cars_count, Quantity) VALUES('" + station + "', '" + freight + "', " + to_string(cars_count) + ", 1);").c_str();
        if (mysql_query(connection, insert) != 0) {
            cout << "Insert error" << endl;
            return false;
        }
        if (mysql_affected_rows(&mysql) != 1) cout << "Insert error 2" << endl;
    }

    return true;
};
