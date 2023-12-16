#ifndef AFILE_H
#define AFILE_H

#include "aPerson.h"
#include "aFlight.h"
#include "aReservation.h"
void writeCustomersToFile(int customerId);
void readCustomersFromFile();
void deleteCustomerFromFile(int deletedCustomerId);

void writeReservationsToFile(int reservationId);
void readReservationsFromFile();
void deleteReservationFromFile(int deletedReservationId);

void writeFlightsToFile(int flightId);
void readFlightsFromFile();
void deleteFlightFromFile(int deletedFlightId);

#endif
