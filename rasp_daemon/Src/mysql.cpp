#include "mysql.h"


Database::Database(std::string host, std::string user, std::string pw, std::string db)
{
	m_host = host;
	m_user = user;
	m_pw = pw;
	m_db = db;
}


void Database::con_init(void)
{
	try
	{
		// Create a connection
		m_driver = get_driver_instance();
		m_con = m_driver->connect(m_host, m_user, m_pw);
		// Connect to the MySQL database
		m_con->setSchema(m_db);
	}
	catch (sql::SQLException &e)
	{
		exception_handler(e);
	}
}


void Database::send_query(std::string query)
{
	con_init();
	
	try
	{
		m_stmt = m_con->createStatement();
		m_stmt->execute(query);
	}
	catch(sql::SQLException &e)
	{
		exception_handler(e);
	}
	
	delete m_stmt;
	delete m_con;
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
