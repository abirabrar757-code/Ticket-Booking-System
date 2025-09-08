#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Flight {
    int flightcode;
    char source[50];
    char destination[50];
    char airline[50];
    char departure[10];
    char arrival[10];
    float price;
    char category[20];
    int available_seats;
    int domestic;
};

struct Booking {
    int bookingId;
    int flightcode;
    char passengername[50];
    char gender[5];
    char email[30];
    char contact[15];
    int payment;
    char payment_details[20];
    int cancelled;
};

struct Flight flights[20];
struct Booking bookings[50];
int flight_count;
int booking_count;

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void safeGetString(char *buffer, int size) {
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
}

void flightlist() {
    // Domestic Flights
    //DHAKA TO CHATTOGRAM
    strcpy(flights[0].source, "Dhaka");
    strcpy(flights[0].destination, "Chattogram");
    strcpy(flights[0].airline, "US Bangla");
    strcpy(flights[0].departure, "10:00 AM");
    strcpy(flights[0].arrival, "12:30 PM");
    flights[0].price = 5000;
    strcpy(flights[0].category, "Economy");
    flights[0].available_seats = 30;
    flights[0].domestic = 1;
    flights[0].flightcode = 2001;
    //DHAKA TO SYLHET
    strcpy(flights[1].source, "Dhaka");
    strcpy(flights[1].destination, "Sylhet");
    strcpy(flights[1].airline, "Biman Bangladesh");
    strcpy(flights[1].departure, "02:00 PM");
    strcpy(flights[1].arrival, "03:30 PM");
    flights[1].price = 4500;
    strcpy(flights[1].category, "Economy");
    flights[1].available_seats = 25;
    flights[1].domestic = 1;
    flights[1].flightcode = 2002;

   //SYLHET TO CHATTOGRAM
    strcpy(flights[4].source,"Sylhet");
    strcpy(flights[4].destination,"Chattogram");
    strcpy(flights[4].airline,"US Bangla");
    strcpy(flights[4].departure,"10:00 AM");
    strcpy(flights[4].arrival,"12:30 PM");
    flights[4].price=9000;
    strcpy(flights[4].category,"Economy");
    flights[4].available_seats=70;
    flights[4].domestic=1;
    flights[4].flightcode=8500;


// International Flights

    //Dhaka to New York
    strcpy(flights[5].source,"Dhaka");
    strcpy(flights[5].destination,"New York");
    strcpy(flights[5].airline,"Emirates");
    strcpy(flights[5].departure,"4:00 AM");
    strcpy(flights[5].arrival,"11:00 PM");
    flights[5].price=200000;
    strcpy(flights[5].category,"Business");
    flights[5].available_seats=90;
    flights[5].domestic=0;
    flights[5].flightcode=8881;
    //Dhaka to London
    strcpy(flights[6].source,"Dhaka");
    strcpy(flights[6].destination,"London");
    strcpy(flights[6].airline,"Qatar Airways");
    strcpy(flights[6].departure,"3:00 AM");
    strcpy(flights[6].arrival,"10:00 PM");
    flights[6].price=100000;
    strcpy(flights[6].category,"Business");
    flights[6].available_seats=30;
    flights[6].domestic=0;
    flights[6].flightcode=4444;

    //Dhaka to Dubai
    strcpy(flights[2].source, "Dhaka");
    strcpy(flights[2].destination, "Dubai");
    strcpy(flights[2].airline, "Emirates");
    strcpy(flights[2].departure, "11:00 PM");
    strcpy(flights[2].arrival, "02:30 AM");
    flights[2].price = 75000;
    strcpy(flights[2].category, "Economy");
    flights[2].available_seats = 40;
    flights[2].domestic = 0;
    flights[2].flightcode = 2003;

    //Dhaka to Syngapore
    strcpy(flights[3].source, "Dhaka");
    strcpy(flights[3].destination, "Singapore");
    strcpy(flights[3].airline, "Singapore Airlines");
    strcpy(flights[3].departure, "09:00 PM");
    strcpy(flights[3].arrival, "03:30 AM");
    flights[3].price = 85000;
    strcpy(flights[3].category, "Economy");
    flights[3].available_seats = 35;
    flights[3].domestic = 0;
    flights[3].flightcode = 2004;

    //Dhaka to Rome
    strcpy(flights[7].source,"Dhaka");
    strcpy(flights[7].destination,"Rome");
    strcpy(flights[7].airline,"Emirates");
    strcpy(flights[7].departure,"2:00 AM");
    strcpy(flights[7].arrival,"8:00 PM");
    flights[7].price=85000;
    strcpy(flights[7].category,"Business");
    flights[7].available_seats=30;
    flights[7].domestic=0;
    flights[7].flightcode=55666;



    flight_count = 8;
}

void displayAvailableDestinations(int isDomestic) {
    printf("\nAvailable %s destinations:\n", isDomestic ? "domestic" : "international");
    printf("Source\t\tDestination\n");
    printf("------------------------\n");

    for (int i = 0; i < flight_count; i++) {
        if (flights[i].domestic == isDomestic) {
            printf("%s\t\t%s\n", flights[i].source, flights[i].destination);
        }
    }
}

void SearchAndDisplayFlights(const char *source, const char *destination, int isDomestic) {
    int found = 0;
    printf("\nAvailable %s Flights from %s to %s:\n",
           isDomestic ? "Domestic" : "International",
           source, destination);
    printf("%-8s %-12s %-12s %-15s %-12s %-12s %-10s %-10s\n",
           "ID", "Source", "Dest", "Airline", "Departure", "Arrival", "Price", "Category");

    for (int i = 0; i < flight_count; i++) {
        if (strcasecmp(flights[i].source, source) == 0 &&
            strcasecmp(flights[i].destination, destination) == 0 &&
            flights[i].domestic == isDomestic) {
            printf("%-8d %-12s %-12s %-15s %-12s %-12s %-10.2f %-10s\n",
                   flights[i].flightcode,
                   flights[i].source,
                   flights[i].destination,
                   flights[i].airline,
                   flights[i].departure,
                   flights[i].arrival,
                   flights[i].price,
                   flights[i].category);
            found = 1;
        }
    }
    if (!found) {
        printf("\nNo flights available on this route!\n");
    }
}

int bookFlight() {
    struct Booking newbook;
    int flightType;
    int flightchoice;
    char source[50], destination[50];

    printf("\nSelect flight type:\n");
    printf("1. Domestic\n");
    printf("2. International\n");
    printf("Enter your choice (1-2): ");
    if (scanf("%d", &flightType) != 1 || (flightType != 1 && flightType != 2)) {
        printf("Invalid choice!\n");
        clearInputBuffer();
        return 0;
    }

    int isDomestic = (flightType == 1);

    displayAvailableDestinations(isDomestic);

    printf("\nEnter Source City: ");
    clearInputBuffer();
    safeGetString(source, sizeof(source));

    printf("Enter Destination City: ");
    safeGetString(destination, sizeof(destination));

    SearchAndDisplayFlights(source, destination, isDomestic);

    printf("\nEnter Flight ID (Press 0 to cancel): ");
    if (scanf("%d", &flightchoice) != 1) {
        printf("Invalid input!\n");
        clearInputBuffer();
        return 0;
    }

    if (flightchoice == 0) {
        printf("Booking cancelled\n");
        return 0;
    }

    int flight_index = -1;
    for (int i = 0; i < flight_count; i++) {
        if (flights[i].flightcode == flightchoice &&
            strcasecmp(flights[i].source, source) == 0 &&
            strcasecmp(flights[i].destination, destination) == 0 &&
            flights[i].domestic == isDomestic) {
            flight_index = i;
            break;
        }
    }

    if (flight_index == -1) {
        printf("Invalid Flight ID!\n");
        return 0;
    }

    if (flights[flight_index].available_seats <= 0) {
        printf("Sorry, there are no available seats!\n");
        return 0;
    }

    newbook.flightcode = flightchoice;
    newbook.bookingId = 1000 + booking_count;
    newbook.cancelled = 0;

    printf("\nEnter passenger details:\n");
    clearInputBuffer();

    printf("Name: ");
    safeGetString(newbook.passengername, sizeof(newbook.passengername));

    printf("Gender (M/F): ");
    safeGetString(newbook.gender, sizeof(newbook.gender));

    printf("Email: ");
    safeGetString(newbook.email, sizeof(newbook.email));

    printf("Contact: ");
    safeGetString(newbook.contact, sizeof(newbook.contact));

    printf("\nSelect payment method:\n");
    printf("1. Debit Card\n");
    printf("2. Credit Card\n");
    printf("3. Net Banking\n");
    printf("Enter choice (1-3): ");
    if (scanf("%d", &newbook.payment) != 1) {
        printf("Invalid payment choice!\n");
        return 0;
    }
    clearInputBuffer();

    switch (newbook.payment) {
    case 1:  // Debit Card
        printf("Enter your Debit card number (15 digits): ");
        safeGetString(newbook.payment_details, sizeof(newbook.payment_details));
        if (strlen(newbook.payment_details) != 15) {
            printf("Invalid debit card number!\n");
            return 0;
        }
        break;

    case 2:  // Credit Card
        printf("Enter your Credit card number (15 digits): ");
        safeGetString(newbook.payment_details, sizeof(newbook.payment_details));
        if (strlen(newbook.payment_details) != 15) {
            printf("Invalid credit card number!\n");
            return 0;
        }
        break;

    case 3:  // Net Banking
        printf("Enter your Bank Account Number (10 digits): ");
        safeGetString(newbook.payment_details, sizeof(newbook.payment_details));
        if (strlen(newbook.payment_details) != 10) {
            printf("Invalid account number length!\n");
            return 0;
        }
        break;

    default:
        printf("Invalid payment method!\n");
        return 0;
}

    bookings[booking_count++] = newbook;
    flights[flight_index].available_seats--;
    printf("\nBooking successful! Your booking ID is: %d\n", newbook.bookingId);
    return 1;
}

void cancelBooking() {
    int bookID;
    printf("Enter Your Booking ID: ");
    if (scanf("%d", &bookID) != 1) {
        printf("Invalid input!\n");
        clearInputBuffer();
        return;
    }

    for (int i = 0; i < booking_count; i++) {
        if (bookings[i].bookingId == bookID && !bookings[i].cancelled) {
            bookings[i].cancelled = 1;

            for (int j = 0; j < flight_count; j++) {
                if (flights[j].flightcode == bookings[i].flightcode) {
                    flights[j].available_seats++;
                    break;
                }
            }
            printf("Booking cancelled successfully\n");
            return;
        }
    }
    printf("Invalid booking ID or booking has been cancelled already!\n");
}

void checkTicket() {
    int bookID;
    printf("Enter your booking ID: ");
    if (scanf("%d", &bookID) != 1) {
        printf("Invalid input!\n");
        clearInputBuffer();
        return;
    }

    for (int i = 0; i < booking_count; i++) {
        if (bookings[i].bookingId == bookID) {
            if (bookings[i].cancelled) {
                printf("This booking has been cancelled.\n");
                return;
            }

            printf("\nBooking Details:\n");
            printf("Passenger Name: %s\n", bookings[i].passengername);

            for (int j = 0; j < flight_count; j++) {
                if (flights[j].flightcode == bookings[i].flightcode) {
                    printf("Flight: %s to %s\n", flights[j].source, flights[j].destination);
                    printf("Airline: %s\n", flights[j].airline);
                    printf("Flight Type: %s\n", flights[j].domestic ? "Domestic" : "International");
                    printf("Departure: %s\n", flights[j].departure);
                    printf("Arrival: %s\n", flights[j].arrival);
                    printf("Price: %.2f\n", flights[j].price);
                    return;
                }
            }
        }
    }
    printf("Booking not found!\n");
}

int main() {
    int choice;
    flightlist();

    while (1) {
        printf("\n\n\t\t ********************************************************************");
        printf("\n\t\t                   Welcome to EWU Flight Management System                ");
        printf("\n\t\t   *******************************************************************");
        printf("\n\n\n\t\t Please enter your choice from below (1-5):");
        printf("\n\n\t\t 1. Book Flight");
        printf("\n\n\t\t 2. Cancel Booking");
        printf("\n\n\t\t 3. Check Ticket");
        printf("\n\n\t\t 4. Search Flights");
        printf("\n\n\t\t 5. Exit");
        printf("\n\n\t\t For any Query: 9653258400");
        printf("\n\n\t\t Enter your choice (1-5): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number between 1 and 5.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                bookFlight();
                break;
            case 2:
                cancelBooking();
                break;
            case 3:
                checkTicket();
                break;
            case 4: {
                int flightType;
                char source[50], destination[50];

                printf("\nSelect flight type:\n");
                printf("1. Domestic\n");
                printf("2. International\n");
                printf("Enter your choice (1-2): ");
                if (scanf("%d", &flightType) != 1 || (flightType != 1 && flightType != 2)) {
                    printf("Invalid choice!\n");
                    clearInputBuffer();
                    break;
                }

                int isDomestic = (flightType == 1);
                displayAvailableDestinations(isDomestic);

                printf("\nEnter Source City: ");
                clearInputBuffer();
                safeGetString(source, sizeof(source));

                printf("Enter Destination City: ");
                safeGetString(destination, sizeof(destination));

                SearchAndDisplayFlights(source, destination, isDomestic);
                break;
            }
            case 5:
                printf("Thank you for using EWU Flight Management System\n");
                return 0;
            default:
                printf("Invalid Choice! Please try again\n");
        }
    }
    return 0;
}
