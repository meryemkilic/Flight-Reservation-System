#ifndef PAYMENT_H
#define PAYMENT_H
#pragma once

typedef struct {
    char cardNumber[20];
    char cardHolderName[20];
    char cardExpiryDate[20];
    float amount;
} Payment;


#endif 