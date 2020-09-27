#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observer.h"

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	std::string type;
};

class CDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << data.type << " station" << std::endl;
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class CStats
{
public:
	CStats(std::string type):type(type) {};
	~CStats() {};

	void UpdateStats(double data)
	{
		if (minValue> data)
		{
			minValue = data;
		}
		if (maxValue < data)
		{
			maxValue = data;
		}
		accValue += data;
		++countAcc;
		PrintStats();
	};


private:
	double CalcAvg()
	{
		return accValue / countAcc;
	}

	void PrintStats()
	{
		std::cout << "Max " << type << " " << maxValue << std::endl;
		std::cout << "Min " << type << " " << minValue << std::endl;
		std::cout << "Average " << type << " " << CalcAvg() << std::endl;
		std::cout << "----------------" << std::endl;
	}

	double minValue = std::numeric_limits<double>::infinity();
	double maxValue = -std::numeric_limits<double>::infinity();
	double accValue = 0;
	unsigned countAcc = 0;
	std::string type;
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << data.type << " station" << std::endl;
		Temperature.UpdateStats(data.temperature);
		Humidity.UpdateStats(data.humidity);
		Pressure.UpdateStats(data.pressure);
		
	}


	CStats Temperature = CStats("Temp");
	CStats Humidity = CStats("Hum");
	CStats Pressure = CStats("Pressure");

};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	CWeatherData(std::string type) :type(type) {};
	// Температура в градусах Цельсия
	double GetTemperature()const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
	{
		return m_pressure;
	}

	std::string GetType()const
	{
		return type;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.type = GetType();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	std::string type;
};