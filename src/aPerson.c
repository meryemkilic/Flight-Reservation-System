#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../header/aPerson.h"


Customer createCustomer(char username[], char password[], char name[], char email[], char phone[]) {
    Customer customer;
    strcpy(customer.username, username);
    strcpy(customer.password, password);
    strcpy(customer.name, name);
    strcpy(customer.email, email);
    strcpy(customer.phone, phone);
    return customer;
}

void updateCustomerInfo(Customer *customer, char name[], char email[], char phone[]) {
    strcpy(customer->name, name);
    strcpy(customer->email, email);
    strcpy(customer->phone, phone);
}

void deleteCustomer(Customer *customer){
    free(customer);
    customer = NULL;
}

Passenger createPassenger(Customer customer, char name[], char surname[], char ID[], char phone[], PassengerType passengerType) {
    Passenger passenger;
    customer = passenger.customer;
    strcpy(passenger.name, name);
    strcpy(passenger.surname, surname);
    strcpy(passenger.ID, ID);
    strcpy(passenger.phone, phone);
    passenger.passengerType = passengerType;
    passenger.reservation= NULL;
}
