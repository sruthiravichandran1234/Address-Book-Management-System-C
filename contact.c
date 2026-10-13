#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"

void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    //Logic to check addressBook is empty first
    if(addressBook -> contactCount == 0)
    {
        printf("\n==================================================\n");
        printf("               No contacts available                \n");
        printf("====================================================\n");
        return;
    }
    //Print header of the table to list all details
    printf("\n==============================================================================\n");
    printf("| %-5s | %-20s | %-15s | %-25s | \n", "S.NO", "NAME", "PHONE NUMBER", "EMAIL ID");
    printf("------------------------------------------------------------------------------\n");

    //Loop through all existing dummy or saved contacts
    for(int i=0; i< addressBook -> contactCount; i++)
    {
        printf("| %-5d | %-20s | %-15s | %-25s | \n", i+1, addressBook->contacts[i].name, 
                                              addressBook->contacts[i].phone, 
                                              addressBook->contacts[i].email);
    }
    printf("==============================================================================\n");
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    char name[30];
    char phone[15];
    char email[30];
    int is_valid = 0;
    do
    {
        printf("Enter name: ");
        scanf(" %29[^\n]", name);
        is_valid = validateName(name); //fn call
    }while(! is_valid);

    is_valid = 0; //reset flag
    do
    {
        printf("Enter phone number: ");
        //__fpurge(stdin);
        scanf(" %14[^\n]", phone);
        is_valid = validatePhone(phone, addressBook); //fn call
    }while(! is_valid);
    
    is_valid = 0; //reset flag
    do
    {
        printf("Enter email id: ");
        //__fpurge(stdin);
        scanf(" %29[^\n]", email);
        is_valid = validateEmail(email); //fn call
    }while(! is_valid);
    strcpy(addressBook -> contacts[addressBook->contactCount].name, name);
    strcpy(addressBook -> contacts[addressBook->contactCount].phone, phone);
    strcpy(addressBook -> contacts[addressBook->contactCount].email, email);
    addressBook->contactCount++;
    saveContactsToFile(addressBook);
}

int searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int option;
    int index = -1;
    do
    {
        printf("\nSearch by \n");
        printf("1. Name \n");
        printf("2. Phone number \n");
        printf("3. Email ID \n");
        printf("Enter you search option: \n");
        scanf("%d", &option);
        switch(option)
        {
            case 1:
            {
                printf("Enter the name to search: \n");
                char str1[20];
                scanf(" %19[^\n]",str1);
                int found1 = 0; //flag to check if any contact matches
                for(int i=0; i<addressBook->contactCount; i++)
                {
                    //check if input matches with the stored contact in addressbook, if match found print that user's details alone
                    if(strcmp(str1, addressBook->contacts[i].name)==0)
                    {
                        printf("%-5d | %-20s | %-15s | %-25s \n", i, addressBook->contacts[i].name,
                                                           addressBook->contacts[i].phone,
                                                           addressBook->contacts[i].email);
                        found1++;
                        index = i;
                    }
                }
                if(found1 == 0)
                {
                    printf("Contact not found \n");
                }
                else if(found1 > 1)
                {
                    printf("Multiple contacts found.\n");
                    printf("Enter index number of the contact: ");
                    scanf("%d", &index);
                }
                break;  
            }
            case 2:
            {
                printf("Enter the phone no to search: \n");
                char str2[15];
                scanf(" %14[^\n]",str2);
                int found2 = 0; //flag to check if any contact matches
                for(int i=0; i<addressBook->contactCount; i++)
                {
                    //check if input matches with the stored contact in addressbook, if match found print that user's details alone
                    if(strcmp(str2, addressBook->contacts[i].phone)==0)
                    {
                        printf("%-5d | %-20s | %-15s | %-25s \n", i, addressBook->contacts[i].name,
                                                           addressBook->contacts[i].phone,
                                                           addressBook->contacts[i].email);
                        found2 = 1;
                        index = i;
                    }
                }
                if(found2 == 0)
                {
                    printf("Contact not found \n");
                }
                break;
            }
            case 3:
            {
                printf("Enter the email id to search: \n");
                char str3[25];
                scanf(" %24[^\n]",str3);
                int found3 = 0; //flag to check if any contact matches
                for(int i=0; i<addressBook->contactCount; i++)
                {
                    //check if input matches with the stored contact in addressbook, if match found print that user's details alone
                    if(strcmp(str3, addressBook->contacts[i].email)==0)
                    {
                        printf("%-5d | %-20s | %-15s | %-25s \n", i, addressBook->contacts[i].name,
                                                           addressBook->contacts[i].phone,
                                                           addressBook->contacts[i].email);
                        found3 = 1;
                        index = i;
                    }
                }
                if(found3 == 0)
                {
                    printf("Contact not found \n");
                }
                break;
            }
            default:
                printf("Invalid search, Try again \n");
        }
    }while(option < 1 || option > 3);
    return index;
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int index = searchContact(addressBook); 
    //if contact not found
    if(index == -1)
    {
        return;
    }
    int eopt;
    int res1;
    do
    {
        printf("Edit Menu: \n");
        printf("1. Edit Name \n");
        printf("2. Edit Phone number \n");
        printf("3. Edit Email \n");
        printf("Enter your edit option \n");
        scanf("%d", &eopt);
        switch(eopt)
        {
            case 1:
            {
                char newname[30];
                printf("Enter new name: ");
                scanf(" %29[^\n]", newname);
                res1 = validateName(newname); 
                if(res1 == 1)
                {
                    strcpy(addressBook->contacts[index].name, newname);
                }
                break;
            }
            case 2:
            {
                char newphone[15];
                printf("Enter new phone: ");
                scanf(" %14[^\n]", newphone);
                res1 = validatePhone(newphone, addressBook); 
                if(res1 == 1)
                {
                    strcpy(addressBook->contacts[index].phone, newphone);
                }
                break;
            }
            case 3:
            {
                char newemail[30];
                printf("Enter new email: ");
                scanf(" %29[^\n]", newemail);
                res1 = validateEmail(newemail); 
                if(res1 == 1)
                {
                    strcpy(addressBook->contacts[index].email, newemail);
                }
                break;
            }
            default:
                printf("Invalid edit, Try again \n");
        }
    }while(eopt < 1 || eopt > 3);  
    saveContactsToFile(addressBook);
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int index = searchContact(addressBook); 
    //if contact not found
    if(index == -1)
    {
        return;
    }
    //check if the element to be deleted is the last element in address book
    if(index == addressBook->contactCount-1)
    {
        addressBook->contactCount--;
    }
    else
    {
        for(int i=index; i<addressBook->contactCount-1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i+1];
        }
        addressBook->contactCount--;
    }
    printf("Contact deleted successfully.\n");
    saveContactsToFile(addressBook);
}
