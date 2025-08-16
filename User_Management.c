#include <stdio.h>
#include <string.h> // For fixing fgets input
#include <conio.h> // For masking password input

#define MAX_USERS 10
#define CREDENTIAL_LENGTH 30

typedef struct {
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];
} User;

User users[MAX_USERS];
int user_count = 0;

// Function Prototypes
void register_user();
int login_user();
void fix_fgets_input(char* str);
void input_password(char* password);

int main() {
    int users_Selection;
    int user_index;

    do {
        printf("\n=== User Management Menu ===\n");
        printf("1. Registration\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your selection: ");
        scanf("%d", &users_Selection);
        getchar(); // to consume leftover newline from scanf

        switch (users_Selection) {
            case 1:
                register_user();
                break;

            case 2:
                user_index = login_user();
                if (user_index >= 0) {
                    printf("\nLogin successful! Welcome, %s\n", users[user_index].username);
                } else {
                    printf("\nLogin failed: Incorrect username or password.\n");
                }
                break;

            case 3:
                printf("\nExiting the Program. Goodbye!\n");
                break;

            default:
                printf("\nInvalid option. Please enter a number between 1 and 3.\n");
                break;
        }

    } while (users_Selection != 3);

    return 0;
}

void register_user() {
    if (user_count == MAX_USERS) {
        printf("Maximum of %d users reached. No more registrations allowed.\n", MAX_USERS);
        return;
    }

    printf("\n--- Register a new user ---\n");
    printf("Enter username: ");
    fgets(users[user_count].username, CREDENTIAL_LENGTH, stdin); // fget takes enter as input string as well
    fix_fgets_input(users[user_count].username); // Fix the fget input and enter from fgets

    input_password(users[user_count].password);

    printf("User '%s' registered successfully.\n", users[user_count].username);
    user_count++;
}

int login_user() {
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];

    printf("\n--- Login ---\n");
    printf("Enter username: ");
    fgets(username, CREDENTIAL_LENGTH, stdin);
    fix_fgets_input(username);

    input_password(password);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(username, users[i].username) == 0 &&
            strcmp(password, users[i].password) == 0) {
            return i; // successful login
        }
    }
    return -1; // login failed
}

void fix_fgets_input(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void input_password(char* password) {
    int index = 0;
    char ch;

    printf("Enter password: ");
    while (1) {
        ch = _getch();  // read character without echo

        if (ch == 13) {  // Enter key
            password[index] = '\0';
            printf("\n");
            break;
        }
        else if (ch == 8) {  // Backspace
            if (index > 0) {
                index--;
                printf("\b \b");
            }
        }
        else if (index < CREDENTIAL_LENGTH - 1) {
            password[index++] = ch;
            printf("*");
        }
    }
}
