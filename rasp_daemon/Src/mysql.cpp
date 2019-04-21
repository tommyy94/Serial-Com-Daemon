#include "mysql.h"


Database::Database(std::string host, std::string user, std::string pw, std::string db)
{
	m_host = host;
	m_user = user;
	m_pw = pw;
	m_db = db;
}


void Database::Init(void)
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
		ExceptionHandler(e);
	}
}


void Database::SendQuery(std::string query)
{
	Init();
	
	try
	{
		m_stmt = m_con->createStatement();
		m_stmt->execute(query);
	}
	catch(sql::SQLException &e)
	{
		ExceptionHandler(e);
	}
	
	delete m_stmt;
	delete m_con;
}


void Database::ExceptionHandler(sql::SQLException &e)
{
	std::cout << "# ERR: SQLException in " << __FILE__;
	std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
	std::cout << "# ERR: " << e.what();
	std::cout << " (MySQL error code: " << e.getErrorCode();
	std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    std::exit(EXIT_FAILURE);
}


void Database::FormQuery(void)
{
//    std::string query = "INSERT INTO temperature (celsius, fahrenheit, kelvin) VALUES (%f, %f, %f)";
//    boost::format fmt = boost::format(query) % m_celsius % m_fahrenheit % m_kelvin;
//    std::string full_query = fmt.str();
//    return full_query;
}
