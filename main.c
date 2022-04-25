#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// a basic password hashing function - rotate each character by 1 ASCII value
const char* passwdHash(char * passwd) {  
    for (size_t i=0; i<strlen(passwd); i++)
        passwd[i]++;
    return passwd;
}
struct db { // our database struct
    char name[50];
    char userid[25];
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
        printf("\n[upto 50 Chars] First Name: ");
        scanf("%s", user[i].name);
        printf("[upto 25 Chars] UserID: ");   
        scanf("%s", user[i].userid); 
        printf("[upto 25 Chars] Password: ");
        scanf("%s", textPasswd[i]);
    }
     
    for (int i=0; i<n; i++)
        strcpy(user[i].passwd, passwdHash(textPasswd[i])); // store the hash in the database
    for (int i=n-1; i>=0; i--)
        free(textPasswd[i]); // free each element from the heap
    free(textPasswd); // finally, free the entire array

    char uid[25]; char pw[25];
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
