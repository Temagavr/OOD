#include "WeatherData.h"

int main()
{
	
	CWeatherData wdIn("In");
	CWeatherData wdOut("Out");

	CDisplay display;
	wdIn.RegisterObserver(display, 3);
	wdOut.RegisterObserver(display, 1);

	CStatsDisplay statsDisplay;
	wdIn.RegisterObserver(statsDisplay, 1);

	CStatsDisplay ss;
	wdIn.RegisterObserver(ss, 2);

	wdIn.SetMeasurements(3, 0.7, 760);
	wdIn.SetMeasurements(4, 0.8, 761);

	wdIn.RemoveObserver(statsDisplay);
	wdIn.RemoveObserver(statsDisplay);

	wdIn.SetMeasurements(10, 0.8, 761);
	wdOut.SetMeasurements(-10, 0.8, 761);
	return 0;
}