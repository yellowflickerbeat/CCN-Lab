#include <stdio.h>
#include <stdlib.h>   // for random()
#include <unistd.h>   // for sleep()

#define WINDOW 1      // Stop and Wait → window size = 1

int main() {

    int i, totalFrames, frame[50];

    printf("\nEnter number of frames to transmit: ");
    scanf("%d", &totalFrames);

    printf("Enter %d frame values: ", totalFrames);
    for (i = 1; i <= totalFrames; i++)
        scanf("%d", &frame[i]);

    printf("\nSTOP-AND-WAIT ARQ Simulation (No pipelining)\n");
    printf("Sender sends ONE frame → waits for ACK before next.\n");
    printf("If error occurs → Negative ACK → resend same frame.\n\n");

    for (i = 1; i <= totalFrames; i++) {

        // ---------------------------------------------------
        // RANDOM SIMULATION:
        // random()%2 → 1 = success, 0 = error
        // ---------------------------------------------------
        if (random() % 2 == 1) {   // SUCCESS CASE

            printf("Sending Frame %d\n", frame[i]);
            printf("ACK received → Frame %d delivered successfully.\n\n", frame[i]);

        } else {                   // ERROR CASE

            printf("ERROR detected for Frame %d.\n", frame[i]);
            printf("Negative ACK → Resending the same frame...\n");
            sleep(1);  // Delay for clear visualization

            i--;       // resend the same frame
            continue;
        }
    }

    printf("All frames transmitted successfully!\n");
    return 0;
}
