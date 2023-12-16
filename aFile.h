#ifndef AFILE_H
#define AFILE_H

#include "aPerson.h"
#include "aFlight.h"
#include "aReservation.h"

void writeCustomersToFile();
void readCustomersFromFile();
void deleteCustomerFromFile(int deletedCustomerId);

void writeReservationsToFile();
void readReservationsFromFile();
void deleteReservationFromFile(int deletedReservationId);
void createTicket(const Reservation *reservation);

void writeFlightsToFile();
void readFlightsFromFile();
void deleteFlightFromFile(int deletedFlightId);

#endif
