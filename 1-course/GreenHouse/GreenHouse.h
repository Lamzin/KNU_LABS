#pragma once
#include <string>

class GreenHouse
{
    const double
            HUMIDITY_INITIAL    = 50.0f,
            HUMIDITY_MAX        = 70.0f,
            HUMIDITY_MIN        = 40.0f,

            TEMPERATURE_INITIAL = 20.0f,
            TEMPERATURE_MAX     = 40.0f,
            TEMPERATURE_MIN     = 10.0f,

            DEVICE_WINDOW_TEMPERATURE_CHANGE        = -1.0f,
            DEVICE_WINDOW_HUMIDIFIER_CHANGE         = -1.0f,
            DEVICE_HEATER_TEMPERATURE_CHANGE        = 1.51f,
            DEVICE_HEATER_HUMIDIFIER_CHANGE         = 0.5f,
            DEVICE_HUMIDIFIER_TEMPERATURE_CHANGE    = 0.01f,
            DEVICE_HUMIDIFIER_HUMIDIFIER_CHANGE     = 1.0f,
            DEVICE_NONE_TEMPERATURE_CHANGE          = -0.5f,
            DEVICE_NONE_HUMIDIFIER_CHANGE           = -0.5f,
            
            TIME_REFRESH = 3600.0f;

    double param_humidity;
    double param_temperature;
    bool param_working;

    bool device_window, device_heater, device_humidifier;

public:
    GreenHouse();
    GreenHouse(double temp, double hum);

    void UpdateParam();
    bool isWorking();

    std::string DeviceWindowOn();
    std::string DeviceWindowOff();
    std::string DeviceHeaterOn();
    std::string DeviceHeaterOff();
    std::string DeviceHumidifierOn();
    std::string DeviceHumidifierOff();
    std::string ReportWorking();
    
    double getRefreshTime();
    void ShutDown();
};
