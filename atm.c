#include <stdio.h>
#include <string.h>
#define MAX_USERS 5
typedef struct {
    char username[20];
    char password[20];
    double balance;
    char transaction_history[1000];
} User;
void display_menu();
void check_balance(User *user);
void deposit(User *user);
void withdraw(User *user);
void transfer(User users[], int user_index);
void display_transaction_history(User *user);
int login(User users[], int num_users);

int main() {
    User users[MAX_USERS] = {
        {"user1", "pass1", 1000.0, ""},
        {"user2", "pass2", 2000.0, ""},
        {"user3", "pass3", 3000.0, ""},
        {"user4", "pass4", 4000.0, ""},
        {"user5", "pass5", 5000.0, ""}
    };

    int num_users = 5;
    int user_index;

    printf("Welcome to the ATM Simulator\n");

    user_index = login(users, num_users);
    if (user_index == -1) {
        printf("Invalid credentials. Exiting...\n");
        return 0;
    }

    int choice;
    do {
        display_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                check_balance(&users[user_index]);
                break;
            case 2:
                deposit(&users[user_index]);
                break;
            case 3:
                withdraw(&users[user_index]);
                break;
            case 4:
                transfer(users, user_index);
                break;
            case 5:
                display_transaction_history(&users[user_index]);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 6);

    return 0;
}

void display_menu() {
    printf("\nATM Menu:\n");
    printf("1. Check Balance\n");
    printf("2. Deposit\n");
    printf("3. Withdraw\n");
    printf("4. Transfer\n");
    printf("5. Display Transaction History\n");
    printf("6. Exit\n");
}

void check_balance(User *user) {
    printf("Your current balance is: $%.2f\n", user->balance);
}

void deposit(User *user) {
    double amount;
    printf("Enter amount to deposit: $");
    scanf("%lf", &amount);
    if (amount > 0) {
        user->balance += amount;
        printf("Deposited $%.2f successfully. New balance: $%.2f\n", amount, user->balance);
        char transaction[50];
        sprintf(transaction, "Deposited $%.2f\n", amount);
        strcat(user->transaction_history, transaction);
    } else {
        printf("Invalid amount.\n");
    }
}

void withdraw(User *user) {
    double amount;
    printf("Enter amount to withdraw: $");
    scanf("%lf", &amount);
    if (amount > 0 && amount <= user->balance) {
        user->balance -= amount;
        printf("Withdrew $%.2f successfully. New balance: $%.2f\n", amount, user->balance);
        char transaction[50];
        sprintf(transaction, "Withdrew $%.2f\n", amount);
        strcat(user->transaction_history, transaction);
    } else {
        printf("Invalid amount or insufficient funds.\n");
    }
}

void transfer(User users[], int user_index) {
    int target_index;
    double amount;
    printf("Enter target user index (0 to %d): ", MAX_USERS - 1);
    scanf("%d", &target_index);
    if (target_index >= 0 && target_index < MAX_USERS && target_index != user_index) {
        printf("Enter amount to transfer: $");
        scanf("%lf", &amount);
        if (amount > 0 && amount <= users[user_index].balance) {
            users[user_index].balance -= amount;
            users[target_index].balance += amount;
            printf("Transferred $%.2f to user %d successfully. New balance: $%.2f\n", amount, target_index, users[user_index].balance);
            char transaction[50];
            sprintf(transaction, "Transferred $%.2f to user %d\n", amount, target_index);
            strcat(users[user_index].transaction_history, transaction);
        } else {
            printf("Invalid amount or insufficient funds.\n");
        }
    } else {
        printf("Invalid target user index.\n");
    }
}

void display_transaction_history(User *user) {
    printf("Transaction History:\n%s", user->transaction_history);
}

int login(User users[], int num_users) {
    char username[20], password[20];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Login successful. Welcome, %s!\n", username);
            return i;
        }
    }
    return -1;
}
