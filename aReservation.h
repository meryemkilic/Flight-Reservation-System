#ifndef ARESERVATION_H
#define ARESERVATION_H

#include "aFlight.h"
#include "aPerson.h"

typedef enum TicketType
{
    ECONOMY,
    FIRST_CLASS
} TicketType;

typedef struct Reservation
{
    int reservationId;
    float price;
    Flight *flight;
    Passenger *passenger;
    TicketType ticketType;
    bool isCheckIn;
    bool isFlightFull;
} Reservation;


extern Reservation reservations[100];
extern int reservationCount;
float calculateReservationPrice(Flight *flight, Passenger passenger, TicketType ticketType);
Reservation* findReservationById(int reservationId);
Reservation createReservation(Flight *flight, Passenger *passenger, TicketType ticketType);
void deleteReservation(int reservationId);
void confirmCheckIn(int reservationId);
int generateReservationId();
#endif