#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 3
void printVectorClock(int vc[N])
{
    printf("[ ");
    for (int i = 0; i < N; i++)
        printf("%d ", vc[i]);
    printf("]\n");
}

void updateSendEvent(int sender, int vectorClock[N])
{
    vectorClock[sender]++;
    printf(" Updated Vector Clock: P%d ", sender + 1);
    printVectorClock(vectorClock);
}

void updateReceiveEvent(int sender, int receiver, int senderClock[N], int receiverClock[N])
{
    receiverClock[receiver]++;

    for (int i = 0; i < N; i++)
    {
        if (receiverClock[i] < senderClock[i])
        {
            receiverClock[i] = senderClock[i];
        }
    }
    printf("\n Updated Vector Clock: P%d", receiver + 1);
    printVectorClock(receiverClock);
}

int main()
{
    int vectorClocks[N][N];
    int senderId, receiverId;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            vectorClocks[i][j] = 0;
    }

    printf("Enter  (or type '0 0' to exit):\n");
    while (1)
    {
        printf("\nMessage: ");
        scanf("%d %d", &senderId, &receiverId);
        if (senderId == 0 && receiverId == 0)
            break;

        if (senderId >= 1 && senderId <= N && receiverId >= 1 && receiverId <= N && senderId != receiverId)
        {
            senderId--;
            receiverId--;
            updateSendEvent(senderId, vectorClocks[senderId]);
            updateReceiveEvent(senderId, receiverId, vectorClocks[senderId], vectorClocks[receiverId]);
        }
        else
            printf("Invalid input.(1-%d).\n", N);
    }
    printf("\nFinal Vector Clocks:\n");
    for (int i = 0; i < N; i++)
    {
        printf("P%d: ", i + 1);
        printVectorClock(vectorClocks[i]);
    }
}