//******************************************************************************
//*                                                                            *
//* Lab Greenhouse                                                             *
//* URL = "http://unicyb.kiev.ua/~tkarnaukh/Programming/Semestr2/Lab%201.pdf"  *
//*                                                                            *
//*                                                                            *
//* Author: Lamzin Oleh, K12                                                   *
//* Time: 16.03.2015                                                           *
//*                                                                            *
//******************************************************************************

#include <iostream>
#include <thread>

#include "GreenHouse.h" 
#include "GreenHouseThread.h"

int main() {

    GreenHouse green_house;
    
    //Create thread, user's message handler
    std::thread mes(MessageHandler, std::ref(green_house));
    
    //Create thread, where we measure the time and do the update
    std::thread proc(Process, std::ref(green_house));
    
    mes.join();
    proc.join();
    return 0;
}
