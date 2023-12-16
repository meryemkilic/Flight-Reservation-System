#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "aFile.h"

const char *PASSENGER_FILE = "passengers.txt";
const char *CUSTOMER_FILE = "customers.txt";
const char *RESERVATION_FILE = "reservations.txt";
const char *FLIGHT_FILE = "flights.txt";


void writeCustomersToFile(int customerId)
{
    FILE *file = fopen(CUSTOMER_FILE, "w");
    if (!file)
    {
        perror("Error opening customers file");
        return;
    }

    for (int i = 0; i < customerCount; i++)
    {
        if (customerId == customers[i].id)
        {
            fprintf(file, "%s %s %d %s %s %s %d\n", customers[i].username, customers[i].password, customers[i].id, customers[i].name, customers[i].email, customers[i].phone, customers[i].isManager);
            break;
        }
    }

    fclose(file);
}

void readCustomersFromFile()
{
    FILE *file = fopen(CUSTOMER_FILE, "r");
    if (!file)
    {
        perror("Error opening customers file");
        return;
    }

    while (!feof(file))
    {
        char username[30], password[30], name[30], email[30], phone[20];
        int id, isManager;
        if (fscanf(file, "%s %s %d %s %s %s %d\n", username, password, &id, name, email, phone, &isManager) == 7)
        {
            createCustomer(username, password, name, email, phone, isManager);
        }
    }

    fclose(file);
}

void writeReservationsToFile(int reservationId)
{
    FILE *file = fopen(RESERVATION_FILE, "w");
    if (!file)
    {
        perror("Error opening reservations file");
        return;
    }

    for (int i = 0; i < reservationCount; i++)
    {
        if (reservationId == reservations[i].reservationId)
        {
            fprintf(file, "%d %.2f %d %d %d %d %d\n", reservations[i].reservationId, reservations[i].price, reservations[i].flight->flightId, reservations[i].passenger->id, reservations[i].ticketType, reservations[i].isCheckIn, reservations[i].isFlightFull);
        break;
        }
    }

    fclose(file);
}

void readReservationsFromFile()
{
    FILE *file = fopen(RESERVATION_FILE, "r");
    if (!file)
    {
        perror("Error opening reservations file");
        return;
    }

    while (!feof(file))
    {
        int reservationId, flightId, passengerId, ticketType, isCheckIn, isFlightFull;
        float price;
        if (fscanf(file, "%d %f %d %d %d %d %d\n", &reservationId, &price, &flightId, &passengerId, &ticketType, &isCheckIn, &isFlightFull) == 7)
        {
            Flight *flight = findFlightById(flightId);
            Passenger *passenger = findPassengerById(passengerId);
            if (flight && passenger)
            {
                createReservation(flight, passenger, ticketType);
            }
        }
    }

    fclose(file);
}

void writeFlightsToFile(int flightId)
{
    FILE *file = fopen(FLIGHT_FILE, "w");
    if (!file)
    {
        perror("Error opening flights file");
        return;
    }

    for (int i = 0; i < flightCount; i++)
    {
        if (flightId == flights[i].flightId)
        {
            fprintf(file, "%d %s %s %d %.2f %s %s %d %d\n", flights[i].flightId, flights[i].date, flights[i].time, flights[i].capacity, flights[i].baseFare, flights[i].departureCity, flights[i].arrivalCity, flights[i].airlineCompany, flights[i].isDelayed);
        break;
        }
    }

    fclose(file);
}

void readFlightsFromFile()
{
    FILE *file = fopen(FLIGHT_FILE, "r");
    if (!file)
    {
        perror("Error opening flights file");
        return;
    }

    while (!feof(file))
    {
        int flightId, capacity, airlineCompany, isDelayed;
        float baseFare;
        char date[20], time[10], departureCity[30], arrivalCity[30];
        if (fscanf(file, "%d %s %s %d %f %s %s %d %d\n", &flightId, date, time, &capacity, &baseFare, departureCity, arrivalCity, &airlineCompany, &isDelayed) == 9)
        {
            createFlight(date, time, capacity, baseFare, departureCity, arrivalCity, airlineCompany, isDelayed);
        }
    }

    fclose(file);
}

void deleteFlightFromFile(int deletedFlightId)
{
    FILE *file = fopen(FLIGHT_FILE, "r");
    if (!file)
    {
        perror("Error opening flights file");
        return;
    }

    FILE *tempFile = fopen("temp_flights.txt", "w");
    if (!tempFile)
    {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    while (!feof(file))
    {
        int flightId, capacity, airlineCompany, isDelayed;
        float baseFare;
        char date[20], time[10], departureCity[30], arrivalCity[30];

        if (fscanf(file, "%d %s %s %d %f %s %s %d %d\n", &flightId, date, time, &capacity, &baseFare, departureCity, arrivalCity, &airlineCompany, &isDelayed) == 9)
        {
            if (flightId != deletedFlightId)
            {
                fprintf(tempFile, "%d %s %s %d %.2f %s %s %d %d\n", flightId, date, time, capacity, baseFare, departureCity, arrivalCity, airlineCompany, isDelayed);
            }
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(FLIGHT_FILE);
    rename("temp_flights.txt", FLIGHT_FILE);
}

void deleteCustomerFromFile(int deletedCustomerId)
{
    FILE *file = fopen(CUSTOMER_FILE, "r");
    if (!file)
    {
        perror("Error opening customers file");
        return;
    }

    FILE *tempFile = fopen("temp_customers.txt", "w");
    if (!tempFile)
    {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    while (!feof(file))
    {
        char username[30], password[30], name[30], email[30], phone[20];
        int id, isManager;

        if (fscanf(file, "%s %s %d %s %s %s %d\n", username, password, &id, name, email, phone, &isManager) == 7)
        {
            if (id != deletedCustomerId)
            {
                fprintf(tempFile, "%s %s %d %s %s %s %d\n", username, password, id, name, email, phone, isManager);
            }
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(CUSTOMER_FILE);
    rename("temp_customers.txt", CUSTOMER_FILE);
}

void deleteReservationFromFile(int deletedReservationId)
{
    FILE *file = fopen(RESERVATION_FILE, "r");
    if (!file)
    {
        perror("Error opening reservations file");
        return;
    }

    FILE *tempFile = fopen("temp_reservations.txt", "w");
    if (!tempFile)
    {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    while (!feof(file))
    {
        int reservationId, flightId, passengerId, ticketType, isCheckIn, isFlightFull;
        float price;

        if (fscanf(file, "%d %f %d %d %d %d %d\n", &reservationId, &price, &flightId, &passengerId, &ticketType, &isCheckIn, &isFlightFull) == 7)
        {
            if (reservationId != deletedReservationId)
            {
                fprintf(tempFile, "%d %.2f %d %d %d %d %d\n", reservationId, price, flightId, passengerId, ticketType, isCheckIn, isFlightFull);
            }
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(RESERVATION_FILE);
    rename("temp_reservations.txt", RESERVATION_FILE);
}

/*
void writeFlights(Flight flight)
{
    FILE *file = fopen("Flights.bin", "ab");
    if (file == NULL)
    {
        printf("\nError, opening file for writing");
        return;
    }

    int status = fwrite(&flight, sizeof(Flight), 1, file);
    fclose(file);

    if (status != 1)
    {
        printf("\nError while writing the file");
    }
}

void readFlights()
{

    flightCount = 0;
    FILE *file = fopen("Flights.bin", "rb");
    if (file == NULL)
    {
        printf("\nError, opening file for reading");
        return;
    }
    int i = 0;
    while (fread(&flights[i], sizeof(Flight), 1, file) != 0)
    {
        i++;
        flightCount++;
    }
    fclose(file);
}

void deleteFlightFromFile(int flightId)
{
    FILE *tempFile = fopen("Temp.bin", "ab");

    if (tempFile == NULL)
    {
        printf("\nError opening file for writing");
        return;
    }
    for (int i = 0; i < flightCount; i++)
    {
        if (flightId == flights[i].flightId)
        {
            continue;
        }
        fwrite(&flights[i], sizeof(Flight), 1, tempFile);
    }
    flightCount--;
    fclose(tempFile);
    remove("Flights.bin");
    rename("Temp.bin", "Flights.bin");
    readFlights();
}

Customer *login(char *username, char *password)
{
    for (int i = 0; i < customerCount; i++)
    {
        if (strcmp(customers[i].username, username) == 0 && strcmp(customers[i].password, password) == 0)
        {
            return &customers[i];
        }
    }
    return NULL;
}

void writeReservation(Reservation r)
{

    FILE *file = fopen("Reservations.bin", "ab");

    if (file == NULL)
    {
        printf("\nError opening file for writing");
        return;
    }

    int status = fwrite(&r, sizeof(Reservation), 1, file);
    fclose(file);
    if (status != 1)
    {
        printf("\nError while writing the file");
    }
}

void readReservations(){
    reservationCount=0;
    FILE *file = fopen("Reservations.bin", "rb");
    if (file == NULL)
    {
        printf("\nError, opening file for reading");
        return;
    }
    int i = 0;
    while (fread(&reservations[i], sizeof(Reservation), 1, file) != 0)
    {
        i++;
        reservationCount++;
    }
    fclose(file);
}*/