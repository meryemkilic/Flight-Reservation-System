#ifndef AFLIGHT_H
#define AFLIGHT_H
#pragma once


typedef enum AirlineCompany
{
    PEGASUS,
    TURKISH_AIRLINES,
    ANADOLUJET
} AirlineCompany;

typedef struct City
{
    char cityName[30];
    int cityCode;
} City;

typedef struct
{
    int flightId;
    char date[20];
    char time[10];
    int capacity;
    float baseFare;
    City departureCity;
    City arrivalCity;
    AirlineCompany airlineCompany;
} Flight;

void printFlights(Flight *flight);
void displayFlight(Flight *flights);
Flight createFlight(int flightCode, char date[], char time[], int capacity, float baseFare, City departureCity, City arrivalCity, enum AirlineCompany airlineCompany);
void listFlightsbyCity(Flight *flights, City departureCity, City arrivalCity);
void listFlightsbyDate(Flight *flights, char date[]);
Flight listFlightsbyAirlineCompany(Flight *flights, enum AirlineCompany airlineCompany);
void listFlightsbyDateAndCity(Flight *flights, char date[], City departureCity, City arrivalCity);
void updateFlightAndWriteToFile(Flight flight);
void updateFlight(Flight flight, char date[], char time[], int capacity, float baseFare, City departureCity, City arrivalCity, enum AirlineCompany airlineCompany);
void deleteFlightFromFile(Flight *flight);
void deleteFlight(Flight flights, int flightCode, Reservation reservations);
void deleteReservationsForFlight(Reservation reservations[], int flightCode);
const char *airlineCompanyToString(enum AirlineCompany airlineCompany);

#endif