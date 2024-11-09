#include <stdio.h>
#include <string.h>

int main() {
    char name[100]; // Array to store the user's name

    // Prompt the user for their name
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin); // Read user input

    // Remove the newline character from the input
    name[strcspn(name, "\n")] = 0;

    // Print a greeting message
    printf("Hello, %s! Welcome to the program.\n", name);

    return 0;
}