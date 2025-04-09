#include <stdio.h>
#include <stdlib.h>

#define MAX 10 // Maximum number of frames (adjustable)

int main() {
    int window_size, frames[MAX], ack, i, sent = 0, base = 0, total_frames;

    // Input window size
    printf("Enter the window size: ");
    scanf("%d", &window_size);

    // Input total number of frames to send
    printf("Enter the total number of frames: ");
    scanf("%d", &total_frames);

    // Input frames
    printf("Enter %d frames: ", total_frames);
    for (i = 0; i < total_frames; i++) {
        scanf("%d", &frames[i]);
    }

    // Sending frames using Go-Back-N
    while (base < total_frames) {
        // Send frames within the window
        for (i = base; i < base + window_size && i < total_frames; i++) {
            if (i >= sent) { // Only print/send if not already sent
                printf("Sending frame %d\n", frames[i]);
                sent++;
            }
        }

        // Wait for acknowledgment
        printf("Waiting for acknowledgment...\n");
        printf("Enter acknowledgment for frame %d: ", frames[base]);
        scanf("%d", &ack);

        // Check if acknowledgment matches the base frame
        if (ack == frames[base]) {
            printf("Acknowledgment received for frame %d\n", frames[base]);
            base++; // Slide the window forward by 1
        } else {
            printf("Acknowledgment not received or incorrect for frame %d, resending from base\n", frames[base]);
            // In GBN, we don’t increment base; we resend from the base frame
        }
    }

    printf("All frames sent successfully\n");
    return 0;
}