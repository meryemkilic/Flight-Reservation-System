#ifndef AFILE_H
#define AFILE_H

#include "aPerson.h"
#include "aFlight.h"
#include "aReservation.h"

void writeCustomersToFile();
void deleteCustomerFromFile(int deletedCustomerId);

void writeReservationsToFile();
void readReservationsFromFile(const char *RESERVATION_FILE, void (*processReservation)(const Reservation *), Customer *account);
//void readReservationsFromFile(const char *RESERVATION_FILE, Customer *account);
void deleteReservationFromFile(int deletedReservationId);
void createTicket(const Reservation *reservation);

void writeFlightsToFile();
void deleteFlightFromFile(int deletedFlightId);

#endif
