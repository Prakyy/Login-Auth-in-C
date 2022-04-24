/* <Define purpose here> and LOC (excluding comments); It can be argued that for security reasons we don't want to store passwords in plain text and the userids in the same block of memory. So, dynamically allocate a new array that stores our passwords temprarily, runs it through the hash function, stores the hash in our struct database and then imediately free() the memory of its contents. */
#include<stdio.h>
#include<string.h>

// a basic password hashing function - rotate each character by 1 ASCII value
const char* passwdHash(char * passwd) {  
    for (size_t i=0; i<strlen(passwd); i++)
        passwd[i]++;
    return passwd;
}
struct db { // our database struct
    char name[50];
    char userid[10];
    char passwd[25];
};

int main() {
    printf("Enter the number of users to add to the database: ");
    int n; scanf("%d", &n);
    struct db user[n];  // create an array of structs
    // create a string array with size 'n' using malloc
    char *textPasswd[n];
    for (int i=0; i<n; i++) {
        textPasswd[i] = (char*)malloc(sizeof(char)*25);
    }

    printf("\nEnter the credentials for each user >>");

    for (int i=0; i<n; i++) {
        printf("\n[upto 50 Chars] First Name: ");   scanf("%s", user[i].name);
        printf("[upto 10 Chars] UserID: ");         scanf("%s", user[i].userid); 
        printf("[upto 25 Chars] Password: ");       scanf("%s", textPasswd[i]);
    }
     
    for (int i=0; i<n; i++)
        strcpy(user[i].passwd, passwdHash(textPasswd[i])); // store the hash in the database
    for (int i=n-1; i>=0; i--)
        free(textPasswd[i]); // free each element from the heap
    free(textPasswd); // finally, free the entire array

    char uid[10]; char pw[25];
    printf("\nUserID to be verified: "); scanf("%s", uid); 
    printf("Enter the password: "); scanf("%s", pw);
    for (int i=0; i<n; i++) { // Credential verification
        if (strcmp (uid, user[i].userid)==0) {
            // check if password is correct
            if (strcmp (passwdHash(pw), user[i].passwd)==0) {
                printf("\nCredentials verified for %s", user[i].name); break;
            }
            else {
                printf("\nIncorrect password"); break; 
            }
        }
        else if (i==n-1)
            printf("\nUser not found");
    }
}
