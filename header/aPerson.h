#ifndef PERSON_H
#define PERSON_H
#pragma once
#include "aFlight.h"

typedef enum PassengerType
{
    STUDENT,
    ADULT,
    CHILD
} PassengerType;

typedef struct
{
    char name[30];
    char surname[30];
    int id;
    char phone[20];
    PassengerType passengerType;
    Reservation reservation;
} Passenger;

typedef struct
{
    char username[30];
    char password[30];
    int id;
    char name[30];
    char email[30];
    char phone[20];
    bool isManager;
    Passenger *(*getAllPassengers)(struct Customer *customer);

} Customer;


Customer createCustomer(char *username, char *password, int id, char *name, char *email, char *phone, bool isManager);
Passenger *getAllPassengers(Customer *customer);
/*
void updateCustomerInfo(Customer *customer, char name[], char email[], char phone[]);
void deleteCustomer(Customer *customer);
Passenger createPassenger(Customer customer, char name[], char surname[], char ID[], char phone[], PassengerType passengerType);
*/
#endif
