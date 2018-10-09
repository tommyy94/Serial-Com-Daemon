#pragma once
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <iostream>


class Database
{
private:
	sql::Driver *m_driver;
	sql::Connection *m_con;
	sql::Statement *m_stmt;
	
	std::string m_host = "tcp://127.0.0.1:3306";
	std::string m_user = "root";
	std::string m_pw = "";
	std::string m_db = "home_automation";
	
	void con_init(void);
	void exception_handler(sql::SQLException &e);
	
public:
	Database(std::string host, std::string user, std::string pw, std::string db);
	void send_query(std::string query);
};
