#pragma once
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <iostream>


class Database
{
	sql::Driver *m_driver;
	sql::Connection *m_con;
	sql::Statement *m_stmt;
	
public:
	Database();
	~Database();
	void con_init();
	void send_query(std::string query);
	void exception_handler(sql::SQLException &e);
};
