#include "booking.h"
#include <stdio.h>
#include <stdlib.h>

// Function to book a slot
void book_slot(CLIENT *clnt, int slot_id) {
    booking_request req;
    req.slot_id = slot_id;
    char **result = book_slot_1(&req, clnt);  // Call the remote function

    if (result == NULL) {
        clnt_perror(clnt, "RPC call failed (BOOK_SLOT)");
    } else {
        printf("Server response: %s\n", *result);
    }
}

// Function to check slot availability
void check_slot(CLIENT *clnt, int slot_id) {
    slot *result = get_slot_status_1(&slot_id, clnt);  // Call the remote function

    if (result == NULL) {
        clnt_perror(clnt, "RPC call failed (GET_SLOT_STATUS)");
    } else {
        if (result->slot_id == -1) {
            printf("Invalid slot ID.\n");
        } else {
            printf("Slot ID: %d, Available: %s\n", result->slot_id, result->available ? "Yes" : "No");
        }
    }
}

int main(int argc, char *argv[]) {
    CLIENT *clnt;
    int slot_id;

    if (argc != 3) {
        printf("Usage: %s <server_address> <slot_id>\n", argv[0]);
        return 1;
    }

    slot_id = atoi(argv[2]);  // Convert slot_id argument to integer

    // Create an RPC client connection to the server
    clnt = clnt_create(argv[1], BOOKING_PROG, BOOKING_VERS, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror(argv[1]);  // Error handling if client creation fails
        return 1;
    }

    // Step 1: Try to book the slot
    book_slot(clnt, slot_id);

    // Step 2: Check the status of the slot after booking
    check_slot(clnt, slot_id);

    // Destroy the client connection
    clnt_destroy(clnt);
    return 0;
}
