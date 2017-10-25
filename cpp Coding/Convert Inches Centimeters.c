// Chris Darnell
// OSU: 932920725
// CS 261 - Assignment 0 - test.c
// Date: 9/29/16

// C Program to convert a value from inches to centimenters, and vice versa.

#include <stdio.h>

int main() {
    
// Variables to be used.
    
    double enteredCentimeters, enteredInches, convertedInches, convertedCentimeters;
    
// Get values to convert from user.
    
    printf("Enter the number of centimeters you wish to convert to inches: \n");
    scanf("%lf", &enteredCentimeters);
    printf("\nEnter the number of inches you wish to convert to centimeters: \n");
    scanf("%lf", &enteredInches);
    
// Convert and display values.
    
// 1 inch = 2.54 cent; 1 cent = 0.393701 inch
    
    convertedInches = enteredCentimeters * .393701;
    convertedCentimeters = enteredInches * 2.545;
    
    
    printf("\nConverted to inches, %lf", enteredCentimeters);
    printf(" centimeters is equal to %lf",convertedInches);
    printf(" inches.\n");
           
    printf("\nConverted to centimeters, %lf",  enteredInches);
    printf(" inches is equal to %lf", convertedCentimeters);
    printf(" centimeters.\n\n");
    
    
    return 0;
    
}

