#include "mysql.h"




Database::Database()
{
	m_driver = get_driver_instance();
}


Database::~Database()
{
	delete m_stmt;
	delete m_con;
}


void Database::con_init()
{
	try
	{
		/* Create a connection */
		m_con = m_driver->connect("tcp://127.0.0.1:3306", "root", "root");
		/* Connect to the MySQL test database */
		m_con->setSchema("name");
	}
	catch (sql::SQLException &e)
	{
		exception_handler(e);
	}
	
}


void Database::send_query(std::string query)
{
	try
	{
		m_stmt = m_con->createStatement();
		m_stmt->execute(query);
	}
	catch(sql::SQLException &e)
	{
		exception_handler(e);
	}
}


void Database::exception_handler(sql::SQLException &e)
{
	std::cout << "# ERR: SQLException in " << __FILE__;
	std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
	std::cout << "# ERR: " << e.what();
	std::cout << " (MySQL error code: " << e.getErrorCode();
	std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	exit(EXIT_FAILURE);
}
