#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aPerson.h"

Customer customers[100];
int customerCount = 0;
Passenger passengers[100];
int passengerCount = 0;
static const char *const passengerTypeNames[] = {"Adult", "Child"};

int generateCustomerId()
{
    static int lastCustomerId = 1000;
    return ++lastCustomerId;
}
Customer createCustomer(char *username, char *password, char *name, char *email, char *phone, bool isManager)
{
    Customer c;
    strcpy(c.username, username);
    strcpy(c.password, password);
    c.id = generateCustomerId();
    strcpy(c.name, name);
    strcpy(c.email, email);
    strcpy(c.phone, phone);
    c.isManager = isManager;
    customers[customerCount] = c;
    customerCount++;
    return c;
}

Passenger createPassenger(char *name, char *surname, char *phone, Customer *customer, PassengerType passengerType)
{
    Passenger p;
    strcpy(p.name, name);
    strcpy(p.surname, surname);
    p.id = generateCustomerId();
    strcpy(p.phone, phone);
    p.customer = customer;
    p.passengerType = passengerType;
    passengers[passengerCount] = p;
    passengerCount++;

    return p;
}

void deleteCustomer(int deletedCustomerId)
{
    int foundIndex = -1;

    for (int i = 0; i < customerCount; i++)
    {
        if (customers[i].id == deletedCustomerId)
        {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1)
    {
        printf("Customer with ID %d not found.\n", deletedCustomerId);
        return;
    }

    for (int j = foundIndex; j < customerCount - 1; j++)
    {
        customers[j] = customers[j + 1];
    }

    customerCount--;
    return;
}

void deletePassenger(int deletedPassengerId)
{
    int foundIndex = -1;
    for (int i = 0; i < passengerCount; i++)
    {
        if (passengers[i].id == deletedPassengerId)
        {
            foundIndex = i;
            break;
        }
    }
    if (foundIndex == -1)
    {
        printf("Passenger with ID %d not found.\n", deletedPassengerId);
        return;
    }
    for (int j = foundIndex; j < passengerCount - 1; j++)
    {
        passengers[j] = passengers[j + 1];
    }

    passengerCount--;
    return;
}

Passenger *findPassengerById(int passengerId)
{
    for (int i = 0; i < passengerCount; i++)
    {
        if (passengers[i].id == passengerId)
        {
            return &passengers[i];
        }
    }
    return NULL;
}
