#include <iostream>
#include <time.h>
#include "GreenHouse.h"

using namespace std;

void Process(GreenHouse &obj){
    double timer = clock();
    
    cout << "Welcome to GreenHouse simulator, author: Oleh Lamzin!\n";
    cout << "If you need some help, just print \"help\"\n";
    
    while(obj.isWorking())
    {
        if ((clock() - timer)/CLOCKS_PER_SEC >= obj.getRefreshTime())
        {
            timer = clock();
            obj.UpdateParam();
            cout << "\nUpdating...";
            cout << obj.ReportWorking();
        }
    }
}

void MessageHandler(GreenHouse &obj) {
    std::string s;
    while(true){
        getline(std::cin, s);
        if (s == "help"){
            cout << "Available commands:\n";
            
            cout << "    \"help\" - help,\n";
            cout << "    \"-w on\" or \"window on\" - open window,\n";
            cout << "    \"-w off\" or \"window off\" - close window,\n";
            
            cout << "    \"-heat on\" or \"heater on\" - turn on heater,\n";
            cout << "    \"-heat off\" or \"heater off\" - turn off heater,\n";

            cout << "    \"-hum on\" or \"humidifier on\" - turn on humidifier,\n";
            cout << "    \"-hum off\" or \"humidifier off\" - turn off humidifier,\n";
            
            cout << "    \"-r\" or \"report\" - current params,\n";
            cout << "    \"exit\" - exit simulator.\n";
        }
        else if (s == "exit"){
            cout << obj.ReportWorking();
            cout << "See you soon!\n";  
            obj.ShutDown();
            return;
        }
        else if (s == "-r"  || s == "report") cout << obj.ReportWorking();
            
        else if (s == "-w on" || s == "window on") cout << obj.DeviceWindowOn();
        else if (s == "-w off" || s == "window off") cout << obj.DeviceWindowOff();
        
        else if (s == "-heat on" || s == "heater on") cout << obj.DeviceHeaterOn();
        else if (s == "-heat off" || s == "heater off") cout << obj.DeviceHeaterOff();
        
        else if (s == "-hum on" || s == "humidifier on") cout << obj.DeviceHumidifierOn();
        else if (s == "-hum off" || s == "humidifier off") cout << obj.DeviceHumidifierOff();
        
        else cout << "\nCommand not found, try again...\n";
    }
}
