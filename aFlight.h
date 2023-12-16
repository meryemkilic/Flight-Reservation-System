#include <stdbool.h>
#ifndef AFLIGHT_H
#define AFLIGHT_H

typedef enum AirlineCompany
{
    PEGASUS,
    TURKISH_AIRLINES,
    ANADOLU_JET
} AirlineCompany;

typedef struct Flight
{
    int flightId;
    char date[20];
    char time[10];
    int capacity;
    float baseFare;
    char departureCity[30];
    char arrivalCity[30];
    AirlineCompany airlineCompany;
    bool isDelayed;
} Flight;


extern Flight flights[100];
extern int flightCount;


int generateFlightId();
Flight createFlight(char *date, char *time, int capacity, float baseFare, char *departureCity, char *arrivalCity, AirlineCompany airlineCompany, bool isDelayed);
void deleteFlight(int deletedFlightId);
bool updateFlight(Flight *flight, char *newDate, char *newTime);
Flight *findFlightById(int flightId);
void viewFlightsByCities(char departureCity[], char arrivalCity[]);
#endif