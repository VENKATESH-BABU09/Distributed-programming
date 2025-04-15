#include "booking.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Define a global slots array
static struct slot slots[] = {
    {1, true},  // Slot 1 available
    {2, true},  // Slot 2 available
    {3, true},  // Slot 3 available
    {4, false}, // Slot 4 reserved
    {5, true},
    {6, true},  // Slot 1 available
    {7, true},  // Slot 2 available
    {8, true},  // Slot 3 available
    {9, false}, // Slot 4 reserved
    {10, true}   // Slot 5 available



};

// Function to book a slot
char **book_slot_1_svc(booking_request *req, struct svc_req *svc) {
    static char response[50];  // Static buffer to hold response message
    static char *response_ptr = response;  // Pointer to return

    int slot_id = req->slot_id;

    printf("Received booking request for slot ID: %d\n", slot_id);

    // Validate slot ID
    if (slot_id < 1 || slot_id > 10) {
        snprintf(response, sizeof(response), "Invalid slot ID.");
        return &response_ptr;
    }

    // Check availability
    if (slots[slot_id - 1].available) {
        slots[slot_id - 1].available = false;  // Mark slot as booked
        snprintf(response, sizeof(response), "Booking successful for slot %d.", slot_id);
        printf("Slot %d booked successfully.\n", slot_id);
    } else {
        snprintf(response, sizeof(response), "Slot %d is already reserved.", slot_id);
        printf("Slot %d is already reserved.\n", slot_id);
    }

    return &response_ptr;
}

// Function to get slot status
slot *get_slot_status_1_svc(int *slot_id, struct svc_req *svc) {
    static slot status;

    printf("Checking status for slot ID: %d\n", *slot_id);

    // Validate slot ID
    if (*slot_id < 1 || *slot_id > 10) {
        status.slot_id = -1;
        status.available = false;
    } else {
        status = slots[*slot_id - 1];  // Return current slot status
    }

    printf("Slot %d, Available: %s\n", *slot_id, status.available ? "Yes" : "No");
    return &status;
}
