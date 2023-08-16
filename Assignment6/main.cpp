/******************************************************************************
 Name: Daniel Witoslawski
 NSHE ID: 2000889468
 Assignment 6:
 Input:
 Output:
 *******************************************************************************/

#include "priorityQ.h"
#include "priorityQ.cpp"
#include <iostream>
#include <string>

int main() {

    std::string racer;
    int rank = 0, numRacers = 0, intervalCounter = 0;
    double distance;
    priorityQ<std::string, double> marioKart;
    unordered_map<std::string, bool> updatedRacer, finishedRace;
    unordered_map<int, int> intervalMap;

    std::cin >> racer;
    for (int i = 0; i < racer.length(); i++)
        racer[i] = toupper(racer[i]);

    while(racer != "END")
    {
        marioKart.push_back(racer, 50);
        std::cin >> racer;
        for (int i = 0; i < racer.length(); i++)
            racer[i] = toupper(racer[i]);
        numRacers++;
    }

    while(numRacers > 0)
    {
        intervalCounter++;
        std::cout << "\nInterval " << intervalCounter << endl << endl;

        updatedRacer.clear();

        while (marioKart.get_front_priority() <= 0)
        {
            std::cout << ++rank << " " << marioKart.get_front_key() << endl << endl;
            finishedRace[marioKart.get_front_key()] = true;
            marioKart.pop_front();
            if(--numRacers == 0)
                break;
        }

        while(true)
        {
            getline(std::cin, racer);
            if (racer.empty())
                getline(std::cin, racer);
            if(racer == "DONE" || racer.empty())
                break;
            for (int i = 0; i < racer.length(); i++)
                racer[i] = toupper(racer[i]);

            if(finishedRace[racer])
            {
                std::cout << "Racer has already finished the race!" << endl << endl;
                continue;
            }

            if (updatedRacer[racer])
            {
                std::cout << "Already updated " << racer << " in this interval!" << endl << endl;
                if (intervalMap[intervalCounter] == numRacers)
                    break;
                else continue;
            }

            updatedRacer[racer] = true;
            std::cin >> distance;
            marioKart.decrease_priority(racer, distance);
            std::cout << "Updating " << racer << endl;
            intervalMap[intervalCounter] += 1;
            if (intervalMap[intervalCounter] == numRacers)
                break;
        }
    }

    return 0;
}
