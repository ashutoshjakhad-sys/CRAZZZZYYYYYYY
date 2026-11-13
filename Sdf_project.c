#include<stdio.h>
#include<string.h>

void display(){
    printf("Please enter a choice!!!");
    printf("1.Create Account");
    printf("2.Login");
    printf("3.Exit");
}
void login(){
    char bank_id [20]; 
    char pass [20];
    printf("Please Enter your Banking Id!");
    scanf("%s",&bank_id);
    printf("Enter your Password");
    scanf("%s",&pass);
}
void create_account(){
    char bank_id [20]; 
    char pass [20];
    printf("Please Enter your Banking Id!");
    scanf("%s",&bank_id);
    printf("Enter your Password");
    scanf("%s",&pass);
    fp = fopen("accounts.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
}
    fprintf(fp, "%s %s\n", bank_id, pass);
    fclose(fp);
    printf("Account created successfully!\n");
}
boolean check_login(char bank_id[], char pass[]){
    FILE *fp;
    char id[20], password[20];
    fp = fopen("accounts.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return false;
    }
    while (fscanf(fp, "%s %s", id, password) != EOF) {
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
    fp = fopen("accounts.txt", "r+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
}
    balance -= amount;
    fprintf(fp, "%d", balance);
    fclose(fp);
}
void credit(){
    printf("Enter the amount to credit: ");
    int amount;
    scanf("%d", &amount);
    fp = fopen("accounts.txt", "r+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
}
    balance += amount;
    fprintf(fp, "%d", balance);
    fclose(fp);
}
void check_balance(){
    fp = fopen("accounts.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
}
    