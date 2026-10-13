#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fptr;
    fptr = fopen("contact.txt","w");
    if(fptr == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    fprintf(fptr, "%d\n", addressBook->contactCount);
    for(int i=0; i<addressBook->contactCount; i++)
    {
        fprintf(fptr, "%s,%s,%s\n", addressBook->contacts[i].name,
                                    addressBook->contacts[i].phone,
                                    addressBook->contacts[i].email);
    }
    fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fptr;
    fptr = fopen("contact.txt","r");
    if(fptr == NULL)
    {
        printf("No contact file found.\n");
        return;
    }
    fscanf(fptr, "%d", &addressBook->contactCount);
    for(int i=0; i<addressBook->contactCount; i++)
    {
        fscanf(fptr, " %49[^,],%19[^,],%49[^\n]\n", addressBook->contacts[i].name,
                                            addressBook->contacts[i].phone,
                                            addressBook->contacts[i].email);
    }
    fclose(fptr);
}
