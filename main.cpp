#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <iostream>

int main() {
    try {
        sql::mysql::MySQL_Driver* driver;
        sql::Connection* con;

        // Initialize the MySQL driver
        driver = sql::mysql::get_mysql_driver_instance();

        // Connect to the database
        con = driver->connect("tcp://127.0.0.1:3306", "user", "password");

        // Set the schema (select the database)
        con->setSchema("testdb");

        // Query the database
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM your_table");

        // Print the results
        while (res->next()) {
            std::cout << "Column Value: " << res->getString("column_name") << std::endl;
        }

        delete res;
        delete stmt;
        delete con;

    }
    catch (sql::SQLException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
