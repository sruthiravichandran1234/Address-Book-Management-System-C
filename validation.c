#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"

//Function for name validation
int validateName(char *name)
{
    for(int i=0; name[i] != '\0'; i++)
    if(! isalpha(name[i]) && name[i] != ' ')
    {
        printf("Invalid name. Try again with a valid name \n");
        return 0;
    }
    return 1;
}

//Function for phone number validation
int validatePhone(char *phone, AddressBook *addressBook)
{
    //1. Check is the length is exactly 10 (as numbers are 10 digits only)
    if(strlen(phone) != 10)
    {
        printf("Invalid phone number. Try again with a valid number \n");
        return 0;
    }
    else
    {
        //2. Check if all the characters are digit (as phone no contains only digits)
        for(int i=0; i<10; i++)
        {
            if(isdigit(phone[i]) == 0)
            {
                printf("Invalid phone number. Try again with a valid number \n");
                return 0;
            }
        }
        //3. Check for duplicates of phone no in the address book
        for(int i=0; i<addressBook->contactCount; i++)
        {
            if(strcmp(phone, addressBook->contacts[i].phone) == 0)
            {
                printf("Phone number already exists. Try again, with valid one as number should be unique \n");
                return 0;
            }
        }
    }
    //if all the validations are passed return 1
    return 1;
}

//Function for email id validation
int validateEmail(char *email)
{
    char *at = strchr(email,'@'); 
    char *dot = strchr(email,'.');
    //Condition to check if email not contain any one of @ or .
    if(at == NULL || dot == NULL)
    {
        printf("Invalid email id. Try again with a valid email \n");
        return 0;
    }
    // @ should not be the first character
    if(at == email)
    {
        printf("Invalid email id. Try again with a valid email\n");
        return 0;
    }
    // There must be something between @ and .
    if(dot == at + 1)
    {
        printf("Invalid email id. Try again with a valid email\n");
        return 0;
    }
    // There must be something after .
    if(*(dot + 1) == '\0')
    {
        printf("Invalid email id. Try again with a valid email\n");
        return 0;
    }
    // Check before @
    for(char *p = email; p < at; p++)
    {
        if(!isalnum((unsigned char)*p) && *p != '.' && *p != '_' && *p != '-')
        {
            printf("Invalid email id. Try again with a valid email\n");
            return 0;
        }
    }
    // Check between @ and .
    for(char *p = at + 1; p < dot; p++)
    {
        if(!isalpha((unsigned char)*p))
        {
            printf("Invalid email id. Try again with a valid email\n");
            return 0;
        }
    }
    // Check after .
    for(char *p = dot + 1; *p != '\0'; p++)
    {
        if(!isalpha((unsigned char)*p))
        {
            printf("Invalid email id. Try again with a valid email\n");
            return 0;
        }
    }

    return 1;
}
