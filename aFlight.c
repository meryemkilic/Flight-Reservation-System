#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "aFlight.h"

Flight flights[100];
int flightCount = 0;
static const char *const airlineCompany[] = {[PEGASUS] = "Pegasus", [TURKISH_AIRLINES] = "Turkish Airlines", [ANADOLU_JET] = "Anadolu Jet"};

int generateFlightId()
{
    static int lastFlightId = 2000;
    return ++lastFlightId;
}

Flight createFlight(char *date, char *time, int capacity, float baseFare, char *departureCity, char *arrivalCity, AirlineCompany airlineCompany, bool isDelayed)
{
    Flight f;
    f.flightId = generateFlightId();
    strcpy(f.date, date);
    strcpy(f.time, time);
    f.capacity = capacity;
    f.baseFare = baseFare;
    strcpy(f.departureCity, departureCity);
    strcpy(f.arrivalCity, arrivalCity);
    f.airlineCompany = airlineCompany;
    f.isDelayed = isDelayed;
    flights[flightCount] = f;
    flightCount++;
    return f;
}
void deleteFlight(int deletedFlightId)
{
    int foundIndex = -1;
    bool thereIsNoReservation = false;
    int delay;
    for (int i = 0; i < reservationCount; i++)
    {
        if (reservations[i].flight->flightId == deletedFlightId)
        {
            thereIsNoReservation = true;
            break;
        }
    }

    if (!thereIsNoReservation)
    {
        for (int j = 0; j < flightCount; j++)
        {
            if (flights[j].flightId == deletedFlightId)
            {
                foundIndex = j;
                break;
            }
        }

        if (foundIndex == -1)
        {
            printf("Flight with ID %d not found.\n", deletedFlightId);
            return;
        }
        for (int j = foundIndex; j < flightCount - 1; j++)
        {
            flights[j] = flights[j + 1];
        }

        flightCount--;
    }
    else
    {
        printf("\nYou cannot cancel this flight because this flight has checked-in passengers.\n");
        printf("\nDo you want to delay the flight? (1: Yes 0: No)   ");
        scanf("%d", &delay);
        if (delay == 1)
        {
            Flight *f = findFlightById(deletedFlightId);
            f->isDelayed = true;
            printf("The flight was delayed.");
        }
    }
}

bool updateFlight(Flight *flight, char *newDate, char *newTime)
{
    if (flight != NULL)
    {
        strcpy(flight->date, newDate);
        strcpy(flight->time, newTime);
        return true;
    }
    return false;
}

Flight *findFlightById(int flightId)
{
    for (int i = 0; i < flightCount; i++)
    {
        if (flights[i].flightId == flightId)
        {
            return &flights[i];
        }
    }
    return NULL;
}
