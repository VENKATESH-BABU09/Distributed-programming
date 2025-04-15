/*
 * booking.x - RPC interface for booking predefined slots
 */

struct slot {
    int slot_id;        
    bool available;     
};

struct booking_request {
    int slot_id;       
};

program BOOKING_PROG {
    version BOOKING_VERS {
        string BOOK_SLOT(booking_request) = 1; 
        slot GET_SLOT_STATUS(int) = 2;           
    } = 1;
} = 0x20000002;
