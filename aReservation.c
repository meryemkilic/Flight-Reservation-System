#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "aReservation.h"

Reservation reservations[100];
int reservationCount = 0;
static const char *const ticketTypes[] = {[ECONOMY] = "Economy", [FIRST_CLASS] = "First Class"};

int generateReservationId() {
    static int lastReservationId = 3000;
    return ++lastReservationId;
}

float calculateReservationPrice(Flight *flight, Passenger passenger, TicketType ticketType)
{
    float baseFare = flight->baseFare;

    if (passenger.passengerType == CHILD)
    {
        baseFare *= 0.8;
    }

    if (ticketType == FIRST_CLASS)
    {
        baseFare *= 1.2;
    }

    return baseFare;
}

Reservation createReservation(Flight *flight, Passenger *passenger, TicketType ticketType)
{
    Reservation r;
    r.reservationId = generateReservationId();
    r.flight = flight;
    r.passenger = passenger;
    r.ticketType = ticketType;
    r.isCheckIn = false;
    r.isFlightFull = false;
    r.price = calculateReservationPrice(flight, *passenger, ticketType);

    reservations[reservationCount] = r;
    reservationCount++;

    return r;
}

void deleteReservation(int reservationId)
{
    int foundIndex = -1;
    
    for (int i = 0; i < reservationCount; i++)
    {
        if (reservations[i].reservationId == reservationId)
        {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1)
    {
        printf("Reservation with ID %d not found.\n", reservationId);
        return;
    }

    if (reservations[foundIndex].isCheckIn)
    {
        printf("Cannot cancel reservation with check-in.\n");
        return;
    }

    for (int j = foundIndex; j < reservationCount - 1; j++)
    {
        reservations[j] = reservations[j + 1];
    }

    reservationCount--;
    return;
}


void confirmCheckIn(int reservationId)
{
    for (int i = 0; i < reservationCount; i++)
    {
        if (reservations[i].reservationId == reservationId)
        {
            reservations[i].isCheckIn = true;
            return; 
        }
    }
    printf("Reservation not found\n");
}
Reservation* findReservationById(int reservationId) {
    for (int i = 0; i < sizeof(reservations) / sizeof(reservations[0]); ++i) {
        if (reservations[i].reservationId == reservationId) {
            return &reservations[i];
        }
    }
    return NULL;
}