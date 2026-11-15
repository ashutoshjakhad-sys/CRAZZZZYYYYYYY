#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct account {
    char bank_id[20];
    char pass[20];
    int balance;
};

void display();
void menu();
void login();
void banking_operations(struct account *current_acc);
void create_account();
bool check_login(struct account *acc);
void update_file(struct account updated_acc);
void debit(struct account *current_acc);
void credit(struct account *current_acc);
void check_balance(struct account current_acc);
void exit_app();

void display() {
    printf("\nPlease enter a choice:\n");
    printf("1. Create Account\n");
    printf("2. Login\n");
    printf("3. Exit\n");
    printf("Choice: ");
}

void menu() {
    printf("\nPlease select an option:\n");
    printf("1. Debit\n");
    printf("2. Credit\n");
    printf("3. Check Balance\n");
    printf("4. Logout\n");
    printf("Choice: ");
}

void create_account() {
    struct account acc;
    printf("Please Enter your Banking Id: ");
    scanf("%19s", acc.bank_id);
    printf("Enter your Password: ");
    scanf("%19s", acc.pass);
    acc.balance = 0;

    FILE *fp = fopen("accounts.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(fp, "%s %s %d\n", acc.bank_id, acc.pass, acc.balance);
    fclose(fp);
    printf("Account created successfully!\n");
}

bool check_login(struct account *acc) {
    char id[20], password[20];
    int balance;
    FILE *fp = fopen("accounts.txt", "r");
    if (fp == NULL) {
        printf("No accounts found. Please create an account first.\n");
        return false;
    }
    while (fscanf(fp, "%19s %19s %d", id, password, &balance) == 3) {
        if (strcmp(acc->bank_id, id) == 0 && strcmp(acc->pass, password) == 0) {
            acc->balance = balance; // Load saved balance
            fclose(fp);
            return true;
        }
    }
    fclose(fp);
    return false;
}

void login() {
    struct account acc;
    printf("Please Enter your Banking Id: ");
    scanf("%19s", acc.bank_id);
    printf("Enter your Password: ");
    scanf("%19s", acc.pass);

    if (check_login(&acc)) {
        printf("Login successful!\n");
        banking_operations(&acc);
    } else {
        printf("Invalid credentials!\n");
    }
}

void banking_operations(struct account *current_acc) {
    int choice;
    while (1) {
        menu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                debit(current_acc);
                break;
            case 2:
                credit(current_acc);
                break;
            case 3:
                check_balance(*current_acc);
                break;
            case 4:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void update_file(struct account updated_acc) {
    FILE *fp = fopen("accounts.txt", "r");
    if (fp == NULL) return;

    struct account list[100];
    int count = 0;

    while (fscanf(fp, "%19s %19s %d", list[count].bank_id, list[count].pass, &list[count].balance) == 3) {
        if (strcmp(list[count].bank_id, updated_acc.bank_id) == 0) {
            list[count].balance = updated_acc.balance;
        }
        count++;
    }
    fclose(fp);

    fp = fopen("accounts.txt", "w");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s %s %d\n", list[i].bank_id, list[i].pass, list[i].balance);
    }
    fclose(fp);
}

void debit(struct account *current_acc) {
    int amount;
    printf("Enter the amount to debit: ");
    scanf("%d", &amount);

    if (amount <= 0) {
        printf("Invalid amount!\n");
    } else if (amount > current_acc->balance) {
        printf("Insufficient balance!\n");
    } else {
        current_acc->balance -= amount;
        update_file(*current_acc);
        printf("Debited %d successfully!\n", amount);
    }
}

void credit(struct account *current_acc) {
    int amount;
    printf("Enter the amount to credit: ");
    scanf("%d", &amount);

    if (amount <= 0) {
        printf("Invalid amount!\n");
    } else {
        current_acc->balance += amount;
        update_file(*current_acc);
        printf("Credited %d successfully!\n", amount);
    }
}

void check_balance(struct account current_acc) {
    printf("Your current balance is: %d\n", current_acc.balance);
}

void exit_app() {
    printf("Thank you for using our banking system. Goodbye!\n");
}

int main() {
    int choice;
    while (1) {
        display();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                create_account();
                break;
            case 2:
                login();
                break;
            case 3:
                exit_app();
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
