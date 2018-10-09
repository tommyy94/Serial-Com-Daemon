#include "datetime.h"


std::string get_timestamp(void)
{
	constexpr int BUFSIZE = 16;
	char buffer[BUFSIZE];
	typedef std::chrono::system_clock Clock;
	
	auto now = Clock::now();
	std::time_t now_c = Clock::to_time_t(now);
	struct tm *parts = std::localtime(&now_c);

	//TODO: Fix timestamp formatting for SQL
	strftime(buffer, sizeof(buffer), "%H:%M:%S %d.%m.%Y", parts);
	return buffer;
}
