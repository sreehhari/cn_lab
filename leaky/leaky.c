
#include <stdio.h>
#include <stdlib.h>

#define BUCKET_SIZE 5
#define OUTPUT_RATE 1

int main() {
    int bucket[BUCKET_SIZE];         // Array to simulate bucket
    int in_rate, n, i, bucket_count = 0; // bucket_count tracks current packets in bucket
    int out_rate = OUTPUT_RATE;

    printf("Enter the number of packets: ");
    scanf("%d", &n);
    printf("Enter the input rate (packets per iteration): ");
    scanf("%d", &in_rate);

    // Initialize bucket with 0s
    for (i = 0; i < BUCKET_SIZE; i++) {
        bucket[i] = 0;
    }

    for (i = 0; i < n; i++) {
        // Check if adding packets exceeds bucket size
        if (bucket_count + in_rate <= BUCKET_SIZE) {
            bucket_count += in_rate; // Add packets to bucket
            printf("Packet %d added, bucket count: %d\n", i + 1, bucket_count);
        } else {
            printf("Bucket overflow, packet %d dropped\n", i + 1);
        }

        // Simulate output (leak) if enough iterations have passed
        if (i >= out_rate) {
            bucket_count -= out_rate; // Remove packets at output rate
            if (bucket_count < 0) bucket_count = 0; // Ensure count doesn’t go negative
            printf("Removed %d packet(s), bucket count: %d\n", out_rate, bucket_count);
        }

        // Print current bucket status (for demonstration)
        printf("Bucket status: ");
        for (int j = 0; j < bucket_count; j++) {
            printf("P "); // Represent each packet with 'P'
        }
        printf("\n");
    }

    return 0;
}