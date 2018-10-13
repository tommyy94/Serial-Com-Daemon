#pragma once
#include <boost/format.hpp>


class Temperature
{
	float m_celsius;
	float m_fahrenheit;
	float m_kelvin;
	
public:
	void convert_to_temperature(int adc_value);
	std::string form_query(void);
};


#define MAX_VOLTAGE 1023
#define VREF 3.3

// TODO: Fix formulas
#define CONVERT_TO_VOLTAGE(adc_value) ((adc_value) / MAX_VOLTAGE * VREF)
#define CONVERT_TO_CELSIUS(voltage) (((voltage) - 500) / 10.0)
#define CONVERT_TO_FAHRENHEIT(celsius) (((celsius) * 9.0 / 5.0) + 32)
#define CONVERT_TO_KELVIN(celsius) ((celsius) + 273.15)
