#include <string>
#include "GreenHouse.h"

GreenHouse::GreenHouse() :
        param_humidity(HUMIDITY_INITIAL),
        param_temperature(TEMPERATURE_INITIAL),
        param_working(true),
        device_window(false), device_heater(false), device_humidifier(false){}

GreenHouse::GreenHouse(double temp, double hum) :
        param_humidity(hum),
        param_temperature(temp),
        param_working(true),
        device_window(false), device_heater(false), device_humidifier(false){}

bool GreenHouse::isWorking(){
    return this->param_working;
}

double GreenHouse::getRefreshTime(){
    return this->TIME_REFRESH;
}

void GreenHouse::ShutDown(){
    this->param_working = false;
}

std::string GreenHouse::DeviceWindowOn() {
    if (this->device_window) return "\nSorry, window is already open!\n";
    else return this->device_window = true, "\nOk, window will be open after update!\n";
}

std::string GreenHouse::DeviceWindowOff() {
    if (!this->device_window) return "\nSorry, window is already closed!\n";
    else return this->device_window = false, "\nOk, window will be closed after update!\n";
}

std::string GreenHouse::DeviceHeaterOn() {
    if (this->device_heater) return "\nSorry, heater is already on!\n";
    else return this->device_heater = true, "\nOk, heater will be turn on after update!\n";
}

std::string GreenHouse::DeviceHeaterOff() {
    if (!this->device_heater) return "\nSorry, heater is already off!\n";
    else return this->device_heater = false, "\nOk, heater will be turn off after update!\n";
}

std::string GreenHouse::DeviceHumidifierOn() {
    if (this->device_humidifier) return "\nSorry, humidifier is already on!\n";
    else return this->device_humidifier = true, "\nOk, humidifier will be turn on after update!\n";
}

std::string GreenHouse::DeviceHumidifierOff() {
    if (!this->device_humidifier) return "\nSorry, humidifier is already off!\n";
    else return this->device_humidifier = false, "\nOk, humidifier will be turn off after update!\n";
}

void GreenHouse::UpdateParam() {
    if (this->param_working) {
        this->param_humidity    += DEVICE_NONE_HUMIDIFIER_CHANGE;
        this->param_temperature += DEVICE_NONE_TEMPERATURE_CHANGE;

        if (this->device_humidifier) {
            this->param_humidity    += DEVICE_HUMIDIFIER_HUMIDIFIER_CHANGE;
            this->param_temperature += DEVICE_HUMIDIFIER_TEMPERATURE_CHANGE;
        }

        if (this->device_heater) {
            this->param_humidity    += DEVICE_HEATER_HUMIDIFIER_CHANGE;
            this->param_temperature += DEVICE_HEATER_TEMPERATURE_CHANGE;
        }

        if (this->device_window) {
            this->param_humidity    += DEVICE_WINDOW_HUMIDIFIER_CHANGE;
            this->param_temperature += DEVICE_WINDOW_TEMPERATURE_CHANGE;
        }

        this->param_working =  this->param_humidity >= HUMIDITY_MIN
                            && this->param_humidity <= HUMIDITY_MAX
                            && this->param_temperature >= TEMPERATURE_MIN
                            && this->param_temperature <= TEMPERATURE_MAX;
    }
}

std::string GreenHouse::ReportWorking() {
    std::string report = "";

    report += "\n**********************************\n";
    report += (this->param_working) ? "GreenHouse: I'm still working!\n" : "GreenHouse: I'm out of order!\n";
    report += "   Temperature = " + std::to_string(this->param_temperature) + ".\n";
    report += "   Humidity    = " + std::to_string(this->param_humidity) + ".\n";

    report += "\n";
    if (this->param_temperature < this->TEMPERATURE_MIN) report += "Temperature is too low.\n";
    if (this->param_temperature > this->TEMPERATURE_MAX) report += "Temperature is too high.\n";
    if (this->param_humidity < this->HUMIDITY_MIN) report += "The air is too dry.\n";
    if (this->param_humidity > this->HUMIDITY_MAX) report += "The air is too humid.\n";
    
    report += "\n";
    report += (this->device_heater) ? "Heater is turn on.\n" : "Heater is turn off.\n";
    report += (this->device_humidifier) ? "Humidifier is turn on.\n" : "Humidifier is turn off.\n";
    report += (this->device_window) ? "Window is open.\n" : "Window is closed.\n";
    report += "**********************************\n";

    return report;
}
