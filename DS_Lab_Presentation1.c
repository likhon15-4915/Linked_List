#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structures for train and passenger
struct Train {
    int trainNumber;
    char trainName[50];
    int totalSeats;
    int availableSeats;
    struct Train* next;
};

struct Passenger {
    char passengerName[50];
    int trainNumber;
    struct Passenger* next;
};

// Function to create a new train node
struct Train* createTrain(int trainNumber, const char* trainName, int totalSeats) {
    struct Train* newTrain = (struct Train*)malloc(sizeof(struct Train));
    if (newTrain != NULL) {
        newTrain->trainNumber = trainNumber;
        strncpy(newTrain->trainName, trainName, sizeof(newTrain->trainName));
        newTrain->totalSeats = totalSeats;
        newTrain->availableSeats = totalSeats;
        newTrain->next = NULL;
    }
    return newTrain;
}

// Function to create a new passenger node
struct Passenger* createPassenger(const char* passengerName, int trainNumber) {
    struct Passenger* newPassenger = (struct Passenger*)malloc(sizeof(struct Passenger));
    if (newPassenger != NULL) {
        strncpy(newPassenger->passengerName, passengerName, sizeof(newPassenger->passengerName));
        newPassenger->trainNumber = trainNumber;
        newPassenger->next = NULL;
    }
    return newPassenger;
}

// Function to add a train to the linked list
void addTrain(struct Train** head, int trainNumber, const char* trainName, int totalSeats) {
    struct Train* newTrain = createTrain(trainNumber, trainName, totalSeats);
    if (newTrain != NULL) {
        newTrain->next = *head;
        *head = newTrain;
    }
}

// Function to display available trains
void displayTrains(struct Train* head) {
    struct Train* currentTrain = head;
    printf("\nAvailable Trains:\n");
    while (currentTrain != NULL) {
        printf("Train Number: %d\n", currentTrain->trainNumber);
        printf("Train Name: %s\n", currentTrain->trainName);
        printf("Total Seats: %d\n", currentTrain->totalSeats);
        printf("Available Seats: %d\n\n", currentTrain->availableSeats);
        currentTrain = currentTrain->next;
    }
}

// Function to reserve a seat for a passenger
void reserveSeat(struct Train* head, struct Passenger** passengers, const char* passengerName, int trainNumber) {
    struct Train* currentTrain = head;
    while (currentTrain != NULL) {
        if (currentTrain->trainNumber == trainNumber && currentTrain->availableSeats > 0) {
            currentTrain->availableSeats--;
            struct Passenger* newPassenger = createPassenger(passengerName, trainNumber);
            if (newPassenger != NULL) {
                newPassenger->next = *passengers;
                *passengers = newPassenger;
                printf("\nReservation successful for passenger: %s on Train %d\n", passengerName, trainNumber);
                return;
            }
        }
        currentTrain = currentTrain->next;
    }
    printf("\nReservation failed. No available seats on Train %d\n", trainNumber);
}

// Function to remove a reservation for a passenger
void removeReservation(struct Passenger** passengers, const char* passengerName, int trainNumber) {
    struct Passenger* currentPassenger = *passengers;
    struct Passenger* prevPassenger = NULL;

    while (currentPassenger != NULL) {
        if (strcmp(currentPassenger->passengerName, passengerName) == 0 && currentPassenger->trainNumber == trainNumber) {
            // Found the reservation to remove
            if (prevPassenger != NULL) {
                prevPassenger->next = currentPassenger->next;
            } else {
                *passengers = currentPassenger->next;
            }
            free(currentPassenger);
            printf("\nReservation removed for passenger: %s on Train %d\n", passengerName, trainNumber);
            return;
        }
        prevPassenger = currentPassenger;
        currentPassenger = currentPassenger->next;
    }
    printf("\nReservation not found for passenger: %s on Train %d\n", passengerName, trainNumber);
}

// Function to display passenger reservations
void displayReservations(struct Passenger* passengers) {
    struct Passenger* currentPassenger = passengers;
    printf("\nPassenger Reservations:\n");
    while (currentPassenger != NULL) {
        printf("Passenger Name: %s\n", currentPassenger->passengerName);
        printf("Train Number: %d\n\n", currentPassenger->trainNumber);
        currentPassenger = currentPassenger->next;
    }
}

// Function to free memory allocated for train and passenger nodes
void freeData(struct Train* trains, struct Passenger* passengers) {
    while (trains != NULL) {
        struct Train* tempTrain = trains;
        trains = trains->next;
        free(tempTrain);
    }

    while (passengers != NULL) {
        struct Passenger* tempPassenger = passengers;
        passengers = passengers->next;
        free(tempPassenger);
    }
}

int main() {
    struct Train* trains = NULL;
    struct Passenger* reservations = NULL;

    int choice;
    char passengerName[50];
    int trainNumber;
    char trainName[50];
    int totalSeats;

    do {
        printf("\nRailway Reservation System\n");
        printf("1. Add Train\n");
        printf("2. Reserve Seat\n");
        printf("3. Remove Reservation\n");
        printf("4. Display Trains\n");
        printf("5. Display Reservations\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Train Number: ");
                scanf("%d", &trainNumber);
                printf("Enter Train Name: ");
                scanf("%s", trainName);
                printf("Enter Total Seats: ");
                scanf("%d", &totalSeats);
                addTrain(&trains, trainNumber, trainName, totalSeats);
                break;

            case 2:
                printf("Enter Passenger Name: ");
                scanf("%s", passengerName);
                printf("Enter Train Number for Reservation: ");
                scanf("%d", &trainNumber);
                reserveSeat(trains, &reservations, passengerName, trainNumber);
                break;

            case 3:
                printf("Enter Passenger Name: ");
                scanf("%s", passengerName);
                printf("Enter Train Number for Reservation: ");
                scanf("%d", &trainNumber);
                removeReservation(&reservations, passengerName, trainNumber);
                break;

            case 4:
                displayTrains(trains);
                break;

            case 5:
                displayReservations(reservations);
                break;

            case 6:
                printf("Exiting Railway Reservation System...\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 6);

    // Clean up memory by freeing all allocated nodes
    freeData(trains, reservations);
    return 0;
}
