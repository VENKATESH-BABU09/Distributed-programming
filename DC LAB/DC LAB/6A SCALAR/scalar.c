#include <stdio.h> 
 
#define MAX_PROCESSES 10 
#define MAX_TICKS 20 
#define MAX_MESSAGES 10 
 
typedef struct { 
    int src_proc, src_tick; 
    int dest_proc, dest_tick; 
} Message; 
 
void printMatrix(int processes[MAX_PROCESSES][MAX_TICKS], int proc_count, int ticks[]) { 
    printf("\nUpdated Timestamp Matrix:\n"); 
    for (int i = 0; i < proc_count; i++) { 
        printf("P%d: ", i); 
        for (int j = 0; j < ticks[i]; j++) { 
            printf("%2d ", processes[i][j]); 
        } 
        printf("\n"); 
    } 
} 
 
 
void propagateProcess(int processes[MAX_PROCESSES][MAX_TICKS], int proc, int start, int tick_count, int 
increment) { 
    for (int i = start + 1; i < tick_count; i++) { 
        processes[proc][i] = processes[proc][i - 1] + increment;   
    } 
} 
 
 
void propagateAll(int processes[MAX_PROCESSES][MAX_TICKS], int proc_count, int ticks[], int increments[]) { 
    for (int i = 0; i < proc_count; i++) { 
        for (int j = 1; j < ticks[i]; j++) { 
            if (processes[i][j] <= processes[i][j - 1]) { 
                processes[i][j] = processes[i][j - 1] + increments[i];  
            } 
        } 
    } 
} 
 
int main() { 
    int processes[MAX_PROCESSES][MAX_TICKS]; 
    int ticks[MAX_PROCESSES]; 
    int increments[MAX_PROCESSES];  
    int proc_count, msg_count; 
 
     
    printf("Enter number of processes: "); 
    scanf("%d", &proc_count); 
 
    for (int i = 0; i < proc_count; i++) { 
        printf("Enter number of ticks for Process %d: ", i); 
        scanf("%d", &ticks[i]); 
 
        printf("Enter timestamps for Process %d: ", i); 
        for (int j = 0; j < ticks[i]; j++) { 
            scanf("%d", &processes[i][j]); 
        } 
 
         
        printf("Enter increment value for Process %d: ", i); 
        scanf("%d", &increments[i]); 
    } 
 
     
    printf("\nEnter number of messages: "); 
    scanf("%d", &msg_count); 
    Message messages[MAX_MESSAGES]; 
 
    for (int i = 0; i < msg_count; i++) { 
        printf("Enter message %c (Sender Process, Sender Tick, Receiver Process, Receiver Tick): ", 'A' + i); 
        scanf("%d %d %d %d", &messages[i].src_proc, &messages[i].src_tick, 
              &messages[i].dest_proc, &messages[i].dest_tick); 
    } 
 
     
    for (int i = 0; i < msg_count; i++) { 
        int src_p = messages[i].src_proc; 
        int src_t = messages[i].src_tick; 
        int dest_p = messages[i].dest_proc; 
        int dest_t = messages[i].dest_tick; 
 
        if (processes[src_p][src_t] >= processes[dest_p][dest_t]) { 
            printf("Violation detected at Message %c: P%d[%d] → P%d[%d]\n", 
                   'A' + i, src_p, src_t, dest_p, dest_t); 
             
             
            processes[dest_p][dest_t] = processes[src_p][src_t] + 1; 
 
             
            propagateProcess(processes, dest_p, dest_t, ticks[dest_p], increments[dest_p]); 
            propagateAll(processes, proc_count, ticks, increments); 
        } 
    } 
 
     
    printMatrix(processes, proc_count, ticks); 
 
    return 0; 
}