#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "aPerson.c"
#include "aFlight.c"
#include "aReservation.c"
#include "aFile.c"

Customer *login()
{
    printf("\n    - Welcome to Flight Reservation System! -\n");
    printf("\n------------   - User Login -   ------------\n");
    char enteredUsername[30];
    char enteredPassword[30];

    printf("\nPlease enter your username: ");
    scanf("%s", enteredUsername);
    printf("Please enter your password: ");
    scanf("%s", enteredPassword);

    for (int i = 0; i < customerCount; i++)
    {
        if (strcmp(enteredUsername, customers[i].username) == 0 && strcmp(enteredPassword, customers[i].password) == 0)
        {
            printf("\nLogin successful!\n");
            return &customers[i];
        }
    }

    printf("\nLogin failed. Invalid username or password.\n");
    return NULL;
}

int main()
{
    Customer *account = NULL;
    PassengerType passengerType;
    TicketType ticketType;

    createCustomer("manager", "123", "manager", "manager@gmail.com", "123456789", 1);
    createCustomer("meryem", "123", "meryem", "meryem@gmail.com", "987654321", 0);
    createFlight("18.12.2023", "12:00", 100, 500.0, "Istanbul", "Ankara", PEGASUS, false);
    createFlight("18.12.2023", "12:00", 100, 600.0, "Istanbul", "Ankara", TURKISH_AIRLINES, false);
    createFlight("18.12.2023", "12:00", 100, 400.0, "Istanbul", "Ankara", ANADOLU_JET, false);

    writeCustomersToFile();
    writeFlightsToFile();
    writeReservationsToFile();

    char username[30];
    char password[30];
    char name[30];
    char surname[30];
    char email[30];
    char phone[20];
    char date[20];
    char time[10];
    int flightId;
    int passengerId;
    int customerId;
    int passengerTypeInt;
    int option;
    int capacity;
    float baseFare;
    int resCount = 1;
    int isLoggedIn = 0;
    char departureCity[30];
    char arrivalCity[30];
    char airlineComp[50];
    char addDelay[1];
    char checkIn[5];

    int index;
    while (true)
    {
        if (account == NULL)
        {
            printf("\n------------------- Welcome to Flight Reservation System! -------------------\n");
            printf("Please select the action you want to perform:\n");
            printf("  1- Login\n");
            printf("  2- Exit\n");

            int loginChoice;
            scanf("%d", &loginChoice);

            if (loginChoice == 1)
            {
                account = login();
            }
            else if (loginChoice == 2)
            {
                printf("Exiting the system. Goodbye!\n");
                break;
            }
            else
            {
                printf("Invalid choice. Please try again.\n");
            }
        }
        else if (account->isManager)
        {
            printf("\n-----------------      Hello Manager!      -----------------\n");

            printf("Please select the action you want to perform.\n");
            printf("\n    1-  Press 1 to create a new flight.   ");
            printf("\n    2-  Press 2 to create a new customer.   ");
            printf("\n    3-  Press 3 to create a new reservation.   ");
            printf("\n    4-  Press 4 to delete a flight.   ");
            printf("\n    5-  Press 5 to delete a customer.   ");
            printf("\n    6-  Press 6 to delete a reservation.   ");
            printf("\n    7-  Press 7 to update a flight.   ");
            printf("\n    8-  Press 8 to add delay to a flight.   ");
            printf("\n    9-  Press 9 to view all flights.   ");
            printf("\n    10- Press 10 to view all reservations.   ");
            printf("\n    11- Logout\n");
            int choice;
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                printf("\n----------       - Flight Creation Process -       ----------\n");
                printf("Please enter flight's information.\n");
                printf("\nPlease enter the flight's date.   ");
                scanf("%s", date);
                printf("\nPlease enter flight's time.   ");
                scanf("%s", time);
                printf("\nPlease enter flight's capacity.   ");
                scanf("%d", &capacity);
                printf("\nPlease enter flight's base fare.   ");
                scanf("%f", &baseFare);
                printf("\nPlease enter departure city.   ");
                scanf("%s", departureCity);
                printf("\nPlease enter arrival city.   ");
                scanf("%s", arrivalCity);
                printf("\nPlease choose an Airline Company. (0: Pegasus, 1: Turkish Airlines, 2: Anadolu Jet)   ");
                scanf("%s", airlineComp);
                AirlineCompany a;
                sscanf(airlineComp, "%d", &a);
                createFlight(date, time, capacity, baseFare, departureCity, arrivalCity, a, false);
                writeFlightsToFile();
                printf("\nFlight created successfully!\n");
                break;

            case 2:
                printf("\n----------       - Customer Creation Process -       ----------\n");
                printf("Please enter customer's information.\n");
                printf("\nPlease enter customer's username.   ");
                scanf("%s", username);
                printf("\nPlease enter customer's password.   ");
                scanf("%s", password);
                printf("\nPlease enter customer's name.   ");
                scanf("%s", name);
                printf("\nPlease enter customer's email.   ");
                scanf("%s", email);
                printf("\nPlease enter customer's phone.   ");
                scanf("%s", phone);
                printf("\nIs the customer a manager? (1 for Yes, 0 for No)   ");
                scanf("%d", &option);

                // createCustomer(username, password, name, email, phone, option).id;

                createCustomer(username, password, name, email, phone, option);
                writeCustomersToFile();
                printf("\nCustomer created successfully!\n");
                break;

            case 3:
                printf("\n----------       - Reservation Creation Process -       ----------\n");
                printf("Please enter reservation's information.\n");
                printf("\nPlease enter the flight ID for reservation.   ");
                scanf("%d", &flightId);
                Flight *selectedFlight = findFlightById(flightId);
                if (selectedFlight == NULL)
                {
                    printf("\nFlight not found!\n");
                    break;
                }
                printf("\nPlease enter the passenger ID for reservation.   ");
                scanf("%d", &index);
                Passenger *selectedPassenger = findPassengerById(index);
                if (selectedPassenger == NULL)
                {
                    printf("\nPassenger not found!\n");
                    break;
                }
                printf("\nPlease choose the ticket type (0: Economy, 1: First Class).   ");
                scanf("%d", &option);
                ticketType = (TicketType)option;
                createReservation(selectedFlight, selectedPassenger, ticketType);
                writeReservationsToFile();
                printf("\nReservation created successfully!\n");
                break;

            case 4:
                printf("\n----------       - Flight Deletion Process -       ----------\n");
                printf("\nList of all flights:\n");
                for (int i = 0; i < flightCount; i++)
                {
                    printf("\nFlight ID: %d\n", flights[i].flightId);
                    printf("Date: %s\n", flights[i].date);
                    printf("Time: %s\n", flights[i].time);
                    printf("Capacity: %d\n", flights[i].capacity);
                    printf("Base Fare: %.2f\n", flights[i].baseFare);
                    printf("Departure City: %s\n", flights[i].departureCity);
                    printf("Arrival City: %s\n", flights[i].arrivalCity);
                    printf("Airline Company: %s\n", airlineCompany[flights[i].airlineCompany]);
                    printf("Is Delayed: %s\n", flights[i].isDelayed ? "Yes" : "No");
                    printf("\n--------------------------\n");
                }
                printf("Please enter the flight ID to delete.   ");
                scanf("%d", &flightId);
                deleteFlight(flightId);
                writeFlightsToFile();
                printf("\nFlight deleted successfully!\n");
                break;

            case 5:
                printf("\n----------       - Customer Deletion Process -       ----------\n");
                printf("\nList of all customers:\n");
                for (int i = 0; i < customerCount; i++)
                {
                    printf("Customer ID: %d\n", customers[i].id);
                    printf("Customer name: %d\n", customers[i].name);
                    printf("\n--------------------------\n");
                }
                printf("\n\nPlease enter the customer ID to delete.   ");
                scanf("%d", &customerId);
                deleteCustomer(customerId);
                writeCustomersToFile();
                printf("\nCustomer deleted successfully!\n");
                break;

            case 6:
                printf("\n----------       - Reservation Deletion Process -       ----------\n");
                printf("\nList of all reservations:\n");
                for (int i = 0; i < reservationCount; i++)
                {
                    printf("Reservation ID: %d\n", reservations[i].reservationId);
                    printf("Passenger name: %d\n", reservations[i].passenger->name);
                    printf("Flight Informations:\nFlight Id: %d     Flight's route: %s - %s", reservations[i].flight->flightId, reservations[i].flight->departureCity, reservations[i].flight->arrivalCity);
                    printf("\n--------------------------\n");
                }
                printf("\n\nPlease enter the reservation ID to delete.   ");
                scanf("%d", &index);
                deleteReservation(index);
                writeReservationsToFile();
                printf("\nReservation deleted successfully!\n");
                break;

            case 7:
                printf("\n----------       - Flight Update Process -       ----------\n");
                printf("Please enter the flight ID to update.   ");
                scanf("%d", &flightId);
                Flight *updatedFlight = findFlightById(flightId);
                if (updatedFlight == NULL)
                {
                    printf("\nFlight not found!\n");
                    break;
                }
                printf("\nPlease enter the new date for the flight.   ");
                scanf("%s", date);
                printf("\nPlease enter the new time for the flight.   ");
                scanf("%s", time);

                if (updateFlight(updatedFlight, date, time))
                {
                    writeFlightsToFile();
                    printf("\nFlight updated successfully!\n");
                }
                else
                {
                    printf("\nFlight update failed!\n");
                }
                break;

            case 8:
                printf("\n----------       - Add Delay to Flight Process -       ----------\n");
                printf("Please enter the flight ID to add delay.   ");
                scanf("%d", &flightId);
                Flight *delayedFlight = findFlightById(flightId);
                if (delayedFlight == NULL)
                {
                    printf("\nFlight not found!\n");
                    break;
                }
                delayedFlight->isDelayed = true;
                writeFlightsToFile();
                printf("\nDelay added to the flight successfully!\n");
                break;

            case 9:
                printf("\n----------       - View All Flights -       ----------\n");
                if (flightCount == 0)
                {
                    printf("\nNo flights available.\n");
                }
                else
                {
                    printf("\nList of all flights:\n");
                    for (int i = 0; i < flightCount; i++)
                    {
                        printf("\nFlight ID: %d\n", flights[i].flightId);
                        printf("Date: %s\n", flights[i].date);
                        printf("Time: %s\n", flights[i].time);
                        printf("Capacity: %d\n", flights[i].capacity);
                        printf("Base Fare: %.2f\n", flights[i].baseFare);
                        printf("Departure City: %s\n", flights[i].departureCity);
                        printf("Arrival City: %s\n", flights[i].arrivalCity);
                        printf("Airline Company: %s\n", airlineCompany[flights[i].airlineCompany]);
                        printf("Is Delayed: %s\n", flights[i].isDelayed ? "Yes" : "No");
                        printf("\n--------------------------\n");
                    }
                }
                break;

            case 10:
                printf("\n----------       - View All Reservations -       ----------\n");
                if (reservationCount == 0)
                {
                    printf("\nNo reservations available.\n");
                }
                else
                {
                    printf("\nList of all reservations:\n");
                    for (int i = 0; i < reservationCount; i++)
                    {
                        printf("\nReservation ID: %d\n", reservations[i].reservationId);
                        printf("Price: %.2f\n", reservations[i].price);
                        printf("Flight ID: %d\n", reservations[i].flight->flightId);
                        printf("Passenger ID: %d\n", reservations[i].passenger->id);
                        printf("Ticket Type: %s\n", ticketTypes[reservations[i].ticketType]);
                        printf("Check-In: %s\n", reservations[i].isCheckIn ? "Yes" : "No");
                        printf("Flight Full: %s\n", reservations[i].isFlightFull ? "Yes" : "No");
                        printf("\n--------------------------\n");
                    }
                }
                break;
            case 11:
                printf("Logging out...\n");
                account = NULL;
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
                break;
            }
        }
        else if (!account->isManager)
        {
            printf("\n------------------- Hello %s! -------------------\n", account->name);
            printf("Please select the action you want to perform:\n");
            printf("  1- View all flights\n");
            printf("  2- View my reservations\n");
            printf("  3- Create a new reservation\n");
            printf("  4- Cancel a reservation\n");
            printf("  5- Check-In\n");
            printf("  6- Download my online ticket\n");
            printf("  7- Logout\n");

            int choice;
            int countCase2 = 0;
            int selected;
            int reservationId;
            TicketType ticketType;
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                if (flightCount == 0)
                {
                    printf("\nNo flights available.\n");
                }
                else
                {
                    printf("\nList of all flights:\n");
                    for (int i = 0; i < flightCount; i++)
                    {
                        printf("\nFlight ID: %d\n", flights[i].flightId);
                        printf("Date: %s\n", flights[i].date);
                        printf("Time: %s\n", flights[i].time);
                        printf("Capacity: %d\n", flights[i].capacity);
                        printf("Base Fare: %.2f\n", flights[i].baseFare);
                        printf("Departure City: %s\n", flights[i].departureCity);
                        printf("Arrival City: %s\n", flights[i].arrivalCity);
                        printf("Airline Company: %s\n", airlineCompany[flights[i].airlineCompany]);
                        printf("Is Delayed: %s\n", flights[i].isDelayed ? "Yes" : "No");
                        printf("\n--------------------------\n");
                    }
                }
                break;

            case 2:
                for (int i = 0; i < reservationCount; i++)
                {
                    if (reservations[i].passenger->customer == account)
                    {
                        countCase2++;
                        printf("\nReservation ID: %d\n", reservations[i].reservationId);
                        printf("Price: %.2f\n", reservations[i].price);
                        printf("Flight ID: %d\n", reservations[i].flight->flightId);
                        printf("Ticket Type: %s\n", ticketTypes[reservations[i].ticketType]);
                        printf("Check-In: %s\n", reservations[i].isCheckIn ? "Yes" : "No");
                        printf("Flight Full: %s\n", reservations[i].isFlightFull ? "Yes" : "No");
                        printf("\n--------------------------\n");
                    }
                }
                if (countCase2 == 0)
                {
                    printf("\nYou have no reservations.\n");
                }
                break;

            case 3:

                printf("\n----------       - Reservation Creation Process -       ----------\n");
                printf("Please enter the flight ID for reservation.   ");
                scanf("%d", &flightId);
                Flight *selectedFlight = findFlightById(flightId);
                if (selectedFlight == NULL)
                {
                    printf("\nFlight not found!\n");
                    break;
                }
                printf("Please enter the passenger informations.\n");
                printf("Passenger Name: ");
                scanf("%s", name);

                printf("Passenger Surname: ");
                scanf("%s", surname);

                printf("Passenger Phone: ");
                scanf("%s", phone);

                do
                {
                    printf("Passenger Type (0: ADULT, 1: CHILD): ");
                    scanf("%d", &passengerTypeInt);
                } while (passengerTypeInt < 0 || passengerTypeInt > 1);

                passengerType = (passengerTypeInt == 0) ? ADULT : CHILD;

                Passenger passenger = createPassenger(name, surname, phone, account, passengerType);

                printf("Please choose the ticket type (0: Economy, 1: First Class)   ");
                scanf("%d", &selected);
                ticketType = (TicketType)selected;
                createReservation(selectedFlight, &passenger, ticketType);
                writeReservationsToFile();
                printf("\nReservation created successfully!\n");
                break;

            case 4:

                printf("\n----------       - Reservation Cancellation Process -       ----------\n");
                printf("This is your reservation's informations:\n");
                for (int i = 0; i < reservationCount; i++)
                {
                    if (reservations[i].passenger->customer == account)
                    {
                        countCase2++;
                        printf("\nReservation ID: %d\n", reservations[i].reservationId);
                        printf("Price: %.2f\n", reservations[i].price);
                        printf("Flight ID: %d\n", reservations[i].flight->flightId);
                        printf("Ticket Type: %s\n", ticketTypes[reservations[i].ticketType]);
                        printf("Check-In: %s\n", reservations[i].isCheckIn ? "Yes" : "No");
                        printf("Flight Full: %s\n", reservations[i].isFlightFull ? "Yes" : "No");
                    }
                }
                if (countCase2 == 0)
                {
                    printf("\nYou have no reservations.\n");
                    break;
                }

                printf("Please enter the reservation ID to cancel.   ");
                scanf("%d", &reservationId);
                Reservation *reservation = findReservationById(reservationId);

                if (reservation == NULL)
                {
                    printf("\nReservation not found!\n");
                }

                if (reservation->passenger->customer != account)
                {
                    printf("\nYou can only cancel your own reservations.\n");
                }

                if (reservation->isCheckIn)
                {
                    printf("You cannot cancel this reservation because you have already checked in.\n");
                }
                else
                {
                    deleteReservation(reservationId);
                    writeReservationsToFile();
                    printf("\nReservation canceled successfully!\n");
                }

                break;
            case 5:
                printf("\n----------       - Reservation Check-In Process -       ----------\n");

                for (int i = 0; i < reservationCount; i++)
                {
                    if (reservations[i].passenger->customer == account)
                    {
                        if (!reservations[i].isCheckIn)
                        {
                            countCase2++;
                            printf("\nReservation ID: %d\n", reservations[i].reservationId);
                            printf("Price: %.2f\n", reservations[i].price);
                            printf("Flight ID: %d\n", reservations[i].flight->flightId);
                            printf("Ticket Type: %s\n", ticketTypes[reservations[i].ticketType]);
                            printf("Check-In: %s\n", reservations[i].isCheckIn ? "Yes" : "No");
                            printf("Flight Full: %s\n", reservations[i].isFlightFull ? "Yes" : "No");
                            printf("Do you want to Check-In? ( Yes - No )   ");
                            scanf("%s", &checkIn);
                            if (strcmp(checkIn, "Yes") || strcmp(checkIn, "yes"))
                            {
                                reservations[i].isCheckIn = true;
                                printf("\nCheck-In proccess completed.\n");
                                break;
                            }
                        }
                    }
                }
                if (countCase2 == 0)
                {
                    printf("\nYou have no reservations.\n");
                }
                break;
            case 6:
                for (int i = 0; i < reservationCount; i++)
                {
                    if (reservations[i].passenger->customer == account)
                    {
                        createTicket(&reservations[i]);
                    }
                }
                break;

            case 7:
                printf("Logging out...\n");
                account = NULL;
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
                break;
            }
        }
    }
    writeCustomersToFile();
    writeFlightsToFile();
    writeReservationsToFile();
    return 0;
}