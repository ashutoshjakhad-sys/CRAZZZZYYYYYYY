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
void login(){
    FILE *fp = fopen("accounts.txt", "r");  
    struct account acc;
    printf("Please Enter your Banking Id!");
    scanf("%s", acc.bank_id);
    printf("Enter your Password");
    scanf("%s", acc.pass);
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
