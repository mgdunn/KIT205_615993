#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "time.h"

long f1(long n) {
    long k = 0;
    for (long i = 0; i < n; i++) {
        for (long j = 0; j < n; j++) {
            k++;
        }
    }
    return k;
}

void f2(long n) {
    long k = 0;
    for (long i = 0; i < n; i++) {
        for (long j = 0; j < i; j++) {
            k++;
        }
        for (long t = 0; t < 10000; t++) {
            k++;
        }
    }
}

void f3(long n) {
    if (n > 0) {
        f3(n / 2);
        f3(n / 2);
    }
}

void f4(long n) {
    if (n > 0) {
        f4(n / 2);
        f4(n / 2);
        f2(n);
    }
}

void f5(long n) {
    long k = 0;
    for (long i = 0; i < 10; i++) {
        long j = n;
        while (j > 0) {
            f1(1000);
            k++;
            j = j / 2;
        }
    }
}

void f6(long n) {
    f2(n);
    f3(n);
    f5(n);
}

void f7(long n) {
    long k = 0;
    for (long i = 0; i < f1(n); i++) {
        k++;
    }
    for (long j = 0; j < n; j++) {
        k++;
    }
}

int main() {
    //Call the options function
	options();

    // Return 0 to indicate successful completion
    return 0;
}

void options(List* self) {

    int quit = 0;


    while (!quit) {
        int option;
        long n;

        printf("Select your option:\n ");
        printf("f1\n");
        printf("f2\n");
        printf("f3\n");
        printf("f4\n");
        printf("f5\n");
        printf("f6\n");
        printf("f7\n");
        scanf("%d", &option);

        printf("Enter a value for n\n");
        scanf("%d", &n);
        clock_t start = clock();

        switch (option) {
        case 0:
            quit = 1;
            break;
        case 1:
            f1(n);
            break;
        case 2:
            f2(n);
            break;
        case 3:
            f3(n);
            break;
        case 4:
            f4(n);
            break;
        case 5:
            f5(n);
            break;
        case 6:
            f6(n);
            break;
        case 7:
            f7(n);
            break;
        default:
            printf("Invalid choice, PLease enter a number between 0 and 3.\n");
            break;
        }
        //Prints the time the function took
        clock_t diff = clock() - start;
        long msec = diff * 1000 / CLOCKS_PER_SEC;
        printf("Operation took %d milliseconds\n\n", msec);
    }
}