#pragma once
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <iostream>

#include <boost/format.hpp>


class Database
{
private:
	sql::Driver *m_driver;
	sql::Connection *m_con;
	sql::Statement *m_stmt;
	
	std::string m_host;
	std::string m_user;
	std::string m_pw;
	std::string m_db;
	
	void Init(void);
	void ExceptionHandler(sql::SQLException &e);
    void FormQuery(void);
	
public:
	Database(std::string host, std::string user, std::string pw, std::string db);
	void SendQuery(std::string query);
};
