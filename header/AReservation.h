#ifndef RESERVATION_H
#define RESERVATION_H
#pragma once
#include "aPerson.h"
#include "aPayment.h"

enum TicketType
{
    BUSINESS,
    ECONOMY,
    FIRST_CLASS
} TicketType;

typedef struct
{
    int reservationId;
    Flight flight;
    Passenger passenger;
    enum TicketType ticketType;
    float calculatedFare;
    bool isCheckIn;
} Reservation;

Reservation createReservation(int reservationId, Flight flight, Passenger passenger, enum TicketType ticketType, float calculatedFare, bool isCheckIn);
void deleteReservation(Reservation reservation[], int deletedReservationId);
float calculateFare(Reservation reservation);
/*
float calculateFare(Passenger passenger);
void printReservation(Passenger *passenger, Reservation *reservation);
Reservation createReservation(Flight flight, enum TicketType ticketType, Passenger passenger);
void displayReservation(Passenger *passenger);
void addReservationToPassenger(Passenger passenger, const Reservation reservation);
void performCheckIn(Passenger passenger, int seatNumber);
void displayCheckInDetails(const Passenger *passenger, int reservationCode);
void pay(Payment payment, Reservation reservation);
*/
#endif