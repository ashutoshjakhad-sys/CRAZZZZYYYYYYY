#include<stdio.h>
#include<string.h>


struct account{
    char bank_id[20];
    char pass[20];
    int balance;
};

void display(){
    printf("Please enter a choice!!!");
    printf("1.Create Account");
    printf("2.Login");
    printf("3.Exit");
}
void menu(){
    printf("Please select an option:\n");
    printf("1. Debit\n");
    printf("2. Credit\n");
    printf("3. Check Balance\n");
    printf("4. Logout\n");
}
void login(){
    FILE *fp = fopen("accounts.txt", "r");  
    struct account acc;
    printf("Please Enter your Banking Id!");
    scanf("%s", acc.bank_id);
    printf("Enter your Password");
    scanf("%s", acc.pass);
    if (check_login(acc.bank_id, acc.pass)) {
        printf("Login successful!\n");
        banking_operations();
    } else {
        printf("Invalid credentials!\n");
    }
    fclose(fp);
}
void banking_operations(){
    int choice;
    while(1){
        menu();
        scanf("%d", &choice);
        switch(choice){
            case 1:
                debit();
                break;
            case 2:
                credit();
                break;
            case 3:
                check_balance();
                break;
            case 4:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}
void create_account(){
    struct account acc;
    printf("Please Enter your Banking Id!");
    scanf("%s", acc.bank_id);
    printf("Enter your Password");
    scanf("%s", acc.pass);
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
boolean check_login(char bank_id[], char pass[]){
    char id[20], password[20];
    int balance;
    FILE *fp = fopen("accounts.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return false;
    }
    while (fscanf(fp, "%s %s %d", id, password, &balance) != EOF) {
        if (strcmp(bank_id, id) == 0 && strcmp(pass, password) == 0) {
            fclose(fp);
            return true;
        }
    }
    fclose(fp);
    return false;
}
void debit(){
    printf("Enter the amount to debit: ");
    int amount;
    scanf("%d", &amount);
    FILE *fp = fopen("accounts.txt", "r+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
}
    acc.balance -= amount;
    fprintf(fp, "%d", acc.balance);
    fclose(fp);
}
void credit(){
    printf("Enter the amount to credit: ");
    int amount;
    scanf("%d", &amount);
    FILE *fp = fopen("accounts.txt", "r+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
}
    acc.balance += amount;
    fprintf(fp, "%d", acc.balance);
    fclose(fp);
}
void check_balance(){
    FILE *fp = fopen("accounts.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    printf("Your current balance is: %d\n", acc.balance);
    fclose(fp);
}
void exit(){
    printf("Thank you for using our banking system. Goodbye!\n");
}

int main(){
    int choice;
    while(1){
        display();
        scanf("%d", &choice);
        switch(choice){
            case 1:
                create_account();
                break;
            case 2:
                login();
                break;
            case 3:
                exit();
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}