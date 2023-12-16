#ifndef APERSON_H
#define APERSON_H

#include <stdbool.h>

typedef enum PassengerType
{
    ADULT,
    CHILD
} PassengerType;

typedef struct Customer
{
    char username[30];
    char password[30];
    int id;
    char name[30];
    char email[30];
    char phone[20];
    bool isManager;
} Customer;

typedef struct Passenger
{
    char name[30];
    char surname[30];
    int id;
    char phone[20];
    Customer *customer;
    PassengerType passengerType;
} Passenger;

extern Customer customers[100];
extern int customerCount;
extern Passenger passengers[100];
extern int passengerCount;

Customer createCustomer(char *username, char *password, char *name, char *email, char *phone, bool isManager);
Passenger createPassenger(char *name, char *surname, char *phone, Customer *customer, PassengerType passengerType);
void deleteCustomer(int deletedCustomerId);
void deletePassenger(int deletedPassengerId);
Passenger *findPassengerById(int passengerId);
int generateCustomerId();

#endif