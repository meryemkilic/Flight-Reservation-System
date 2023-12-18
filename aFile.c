#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "aFile.h"

const char *PASSENGER_FILE = "passengers.txt";
const char *CUSTOMER_FILE = "customers.txt";
const char *RESERVATION_FILE = "reservations.txt";
const char *FLIGHT_FILE = "flights.txt";

void createTicket(const Reservation *reservation)
{
    char filename[50];
    sprintf(filename, "ticket_%d.txt", reservation->reservationId);

    FILE *file = fopen(filename, "w");
    if (!file)
    {
        perror("Error opening ticket file");
        return;
    }

    fprintf(file, "Reservation ID: %d\n", reservation->reservationId);
    fprintf(file, "Price: %.2f\n", reservation->price);
    fprintf(file, "Flight ID: %d\n", reservation->flight->flightId);
    fprintf(file, "Passenger ID: %d\n", reservation->passenger->id);
    fprintf(file, "Ticket Type: %d\n", reservation->ticketType);
    fprintf(file, "Check-In: %s\n", reservation->isCheckIn ? "Yes" : "No");
    fprintf(file, "Flight Full: %s\n", reservation->isFlightFull ? "Yes" : "No");

    fclose(file);
    printf("Ticket created for Reservation ID %d\n", reservation->reservationId);
    printf("Ticket created successfully. Download the %s file.\n", filename);
}

void writeCustomersToFile()
{
    FILE *file = fopen(CUSTOMER_FILE, "w");
    if (!file)
    {
        perror("Error opening customers file");
        return;
    }

    for (int i = 0; i < customerCount; i++)
    {
        fprintf(file, "%s %s %d %s %s %s %d\n", customers[i].username, customers[i].password, customers[i].id, customers[i].name, customers[i].email, customers[i].phone, customers[i].isManager);
    }

    fclose(file);
}

void writeReservationsToFile()
{
    FILE *file = fopen(RESERVATION_FILE, "w");
    if (!file)
    {
        perror("Error opening reservations file");
        return;
    }

    for (int i = 0; i < reservationCount; i++)
    {

        fprintf(file, "%d %.2f %d %d %d %d %d\n", reservations[i].reservationId, reservations[i].price, reservations[i].flight->flightId, reservations[i].passenger->id, reservations[i].ticketType, reservations[i].isCheckIn, reservations[i].isFlightFull);
    }

    fclose(file);
}

void readReservationsFromFile(const char *RESERVATION_FILE, void (*createTicket)(const Reservation *), Customer *account) {
    FILE *file = fopen(RESERVATION_FILE, "r");
    if (!file) {
        perror("Error opening reservations file");
        return;
    }

    while (1) {
        Reservation *reservation = (Reservation *)malloc(sizeof(Reservation));
        if (!reservation) {
            perror("Memory allocation error");
            fclose(file);
            return;
        }

        int result = fscanf(file, "%d %f %d %d %d %d %d",
                            &reservation->reservationId, &reservation->price,
                            &reservation->flight->flightId, &reservation->passenger->id,
                            &reservation->ticketType, &reservation->isCheckIn,
                            &reservation->isFlightFull);

        if (result == EOF) {
            free(reservation);
            break;
        } else if (result != 7) {  
            fprintf(stderr, "Error reading reservation data\n");
            free(reservation);
            break;
        }

        if (reservation->passenger->customer == account) {
            createTicket(reservation);
        }

        free(reservation);
    }

    fclose(file);
}
/*
void readReservationsFromFile(const char *RESERVATION_FILE, Customer *account) {
    FILE *file = fopen(RESERVATION_FILE, "r");
    if (!file) {
        perror("Error opening reservations file");
        return;
    }

    while (1) {
        Reservation *reservation = (Reservation *)malloc(sizeof(Reservation));
        if (!reservation) {
            perror("Memory allocation error");
            fclose(file);
            return;
        }

        int result = fscanf("%d %.2f %d %d %d %d %d\n", &reservation->reservationId, &reservation->price, 
        &reservation->flight->flightId, &reservation->passenger->id, 
        &reservation->ticketType, &reservation->isCheckIn, &reservation->isFlightFull);

        if (result == EOF) {
            free(reservation);
            break;
        } else if (result != 7) {  
            fprintf(stderr, "Error reading reservation data\n");
            free(reservation);
            break;
        }
    }
    
    fclose(file);
}
*/

void writeFlightsToFile()
{
    FILE *file = fopen(FLIGHT_FILE, "w");
    if (!file)
    {
        perror("Error opening flights file");
        return;
    }

    for (int i = 0; i < flightCount; i++)
    {
        fprintf(file, "%d %s %s %d %.2f %s %s %d %d\n", flights[i].flightId, flights[i].date, flights[i].time, flights[i].capacity, flights[i].baseFare, flights[i].departureCity, flights[i].arrivalCity, flights[i].airlineCompany, flights[i].isDelayed);
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
