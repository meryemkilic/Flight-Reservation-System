#ifndef LOGIN_H
#define LOGIN_H
#pragma once
#include "aPerson.h"

int validateLogin(char username[], char password[], Customer *customers, Manager *manager);
int loginCustomer(Customer *customers, char username[], char password[]);
int loginManager(Manager *manager, char username[], char password[]);


#endif