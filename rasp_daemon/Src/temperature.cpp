#include "temperature.h"


void Temperature::convert_to_temperature(int adc_value)
{
	float voltage = CONVERT_TO_VOLTAGE((float)adc_value);
	m_celsius = CONVERT_TO_CELSIUS(voltage);
	m_fahrenheit = CONVERT_TO_FAHRENHEIT(m_celsius);
	m_kelvin = CONVERT_TO_KELVIN(m_celsius);
}


std::string Temperature::form_query(void)
{
	std::string query = "INSERT INTO temperature (celsius, fahrenheit, kelvin) VALUES (%f, %f, %f)";
	boost::format fmt = boost::format(query) % m_celsius % m_fahrenheit % m_kelvin;
	std::string full_query = fmt.str();
	return full_query;
}
