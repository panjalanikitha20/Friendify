#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structures for user profiles
typedef struct User
{
    char username[50];
    char password[50];
    struct User *friends;
    struct User *next;
} User;

// Global user database linked list
User *users = NULL;

// Function to create a new user profile
User *createProfile()
{
    User *newUser = (User *)malloc(sizeof(User));
    newUser->friends = NULL;
    newUser->next = NULL;
    printf("Enter username: ");
    scanf("%s", newUser->username);
    printf("Enter password: ");
    scanf("%s", newUser->password);
    newUser->next = users;
    users = newUser;

    // Store the user's data in a file
    FILE *file = fopen(newUser->username, "w");
    fprintf(file, "Username: %s\n", newUser->username);
    fprintf(file, "Password: %s\n", newUser->password);
    fclose(file);
    return newUser;
}

// Function to authenticate a user
User *authenticateUser(const char *username, const char *password)
{
    User *current = users;
    while (current != NULL)
    {
        if (strcmp(current->username, username) == 0 && strcmp(current->password, password) == 0)
        {
            return current; // User is authenticated
        }
        current = current->next;
    }
    return NULL; // User not found or incorrect password
}

// Function to add a friend to the user's friend list
void addFriend(User *user, User *friend)
{
    User *newFriend = (User *)malloc(sizeof(User));
    strcpy(newFriend->username, friend->username);
    newFriend->next = user->friends;
    user->friends = newFriend;
}

// Function to view the friend list
void viewFriendList(User *user)
{
    User *currentFriend = user->friends;
    if (currentFriend == NULL)
    {
        printf("You have no friends.\n");
    }
    else
    {
        printf("Your friend list:\n");
        while (currentFriend != NULL)
        {
            printf("%s\n", currentFriend->username);
            currentFriend = currentFriend->next;
        }
    }
}

// Function to send a message
void sendMessage(User *sender, User *receiver, const char *text)
{
    FILE *file = fopen("messages.txt", "a");
    fprintf(file, "From: %s\n", sender->username);
    fprintf(file, "To: %s\n", receiver->username);
    fprintf(file, "Message: %s", text);
    fprintf(file, "-------------------\n");
    fclose(file);
}

// Function to display a user's messages
void displayMessages(User *user)
{
    FILE *file = fopen("messages.txt", "r");
    char line[100];
    char sender[50], receiver[50], message[100];
    int display = 0;

    if (file != NULL)
    {
        while (fgets(line, sizeof(line), file))
        {
            if (strncmp(line, "From: ", 6) == 0)
            {
                sscanf(line, "From: %s", sender);
            }
            else if (strncmp(line, "To: ", 4) == 0)
            {
                sscanf(line, "To: %s", receiver);
                display = (strcmp(receiver, user->username) == 0);
            }
            else if (strncmp(line, "Message: ", 9) == 0 && display)
            {
                sscanf(line, "Message: %[^\n]", message);
                printf("From: %s\nMessage: %s\n", sender, message);
            }
            else if (strcmp(line, "-------------------\n") == 0 && display)
            {
                printf("------------\n");
                display = 0;
            }
        }
        fclose(file);
    }
    else
    {
        printf("You have no messages.\n");
    }
}

// Main function
int main()
{
    int choice;
    User *currentUser = NULL;

    while (1)
    {
        printf("\n  ########### WELCOME TO FRIENDIFY ###########\n");
        printf("       *    SOCIAL NETWORKING SIMULATION   *   \n");
        printf("                  1. Create User Profile\n");
        printf("                  2. Login\n");
        printf("                  3. Add Friend\n");
        printf("                  4. View Friend List\n");
        printf("                  5. Send Message\n");
        printf("                  6. Display Messages\n");
        printf("                  7. Exit\n");
        printf("                  8. Logout\n");
        printf("--->Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (currentUser != NULL)
            {
                printf("$$$ You are already logged in as %s.\n", currentUser->username);
                break;
            }
            createProfile();
            printf("$$$ User profile created successfully!\n");
            break;

        case 2:
            if (currentUser != NULL)
            {
                printf("$$$ You are already logged in as %s.\n", currentUser->username);
                break;
            }
            {
                char username[50], password[50];
                printf("--->Enter username: ");
                scanf("%s", username);
                printf("--->Enter password: ");
                scanf("%s", password);
                User *authenticatedUser = authenticateUser(username, password);
                if (authenticatedUser != NULL)
                {
                    currentUser = authenticatedUser;
                    printf("$$$ Logged in as %s\n", username);
                }
                else
                {
                    printf("$$$ Authentication failed. Invalid username or password.\n");
                }
            }
            break;

        case 3:
            if (currentUser == NULL)
            {
                printf("$$$ You must log in first.\n");
            }
            else
            {
                char friendName[50];
                printf("--->Enter friend's username: ");
                scanf("%s", friendName);

                User *friendToAdd = users;
                int found = 0;
                while (friendToAdd != NULL)
                {
                    if (strcmp(friendToAdd->username, friendName) == 0)
                    {
                        addFriend(currentUser, friendToAdd);
                        printf("$$$ %s is now your friend.\n", friendName);
                        found = 1;
                        break;
                    }
                    friendToAdd = friendToAdd->next;
                }
                if (!found)
                {
                    printf("$$$ User not found.\n");
                }
            }
            break;

        case 4:
            if (currentUser == NULL)
            {
                printf("$$$ You must log in first.\n");
            }
            else
            {
                viewFriendList(currentUser);
            }
            break;

        case 5:
            if (currentUser == NULL)
            {
                printf("$$$ You must log in first.\n");
            }
            else
            {
                char receiverName[50], messageText[100];
                printf("--->Enter recipient's username: ");
                scanf("%s", receiverName);
                printf("--->Enter message: ");
                getchar(); // Clear newline
                fgets(messageText, sizeof(messageText), stdin);

                User *recipient = users;
                int found = 0;
                while (recipient != NULL)
                {
                    if (strcmp(recipient->username, receiverName) == 0)
                    {
                        sendMessage(currentUser, recipient, messageText);
                        printf("$$$ Message sent to %s.\n", receiverName);
                        found = 1;
                        break;
                    }
                    recipient = recipient->next;
                }
                if (!found)
                {
                    printf("$$$ Recipient not found.\n");
                }
            }
            break;

        case 6:
            if (currentUser == NULL)
            {
                printf("$$$ You must log in first.\n");
            }
            else
            {
                displayMessages(currentUser);
            }
            break;

        case 7:
        {
            User *current = users;
            while (current != NULL)
            {
                User *temp = current;
                current = current->next;
                free(temp);
            }
            printf("THANK YOU!!!\n");
            exit(0);
        }

        case 8:
            if (currentUser != NULL)
            {
                printf("$$$ Logged out from %s.\n", currentUser->username);
                currentUser = NULL;
            }
            else
            {
                printf("$$$ No user is currently logged in.\n");
            }
            break;

        default:
            printf("$$$ Invalid choice. Please try again.\n");
        }
    }
}
