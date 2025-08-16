#include <stdio.h>
#include <string.h>

void Create_Account();
void Deposit_Money();
void Withdraw_Money();
void Check_Balance();
void Delete_Account();

const char* Account_File = "account.dat";

typedef struct {
    char name[50];
    int acc_no;
    float balance;
} Account;

void flush_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    while (1) {
        int Choice;
        printf("\n*** BANK MANAGEMENT SYSTEM ***\n");
        printf("1. Create Account\n2. Deposit Money\n3. Withdraw Money\n4. Check Balance\n5. Exit\n6. Delete Account\n");
        printf("Enter Your Choice: ");
        scanf("%d", &Choice);

        switch (Choice) {
            case 1:
                Create_Account();
                break;
            case 2:
                Deposit_Money();
                break;
            case 3:
                Withdraw_Money();
                break;
            case 4:
                Check_Balance();
                break;
            case 5:
                printf("Exiting the bank! Pleasure doing business with you.\n");
                return 0;
            case 6:
                Delete_Account();
                break;
            default:
                printf("Invalid Choice!\n");
                break;
        }
    }

    return 0;
}

void Create_Account() {
    Account acc;
    FILE *file = fopen(Account_File, "ab+");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    flush_input();

    printf("\nEnter your name: ");
    fgets(acc.name, sizeof(acc.name), stdin);
    acc.name[strcspn(acc.name, "\n")] = '\0';

    printf("Enter your account number: ");
    scanf("%d", &acc.acc_no);
    acc.balance = 0;

    fwrite(&acc, sizeof(acc), 1, file);
    fclose(file);
    printf("Account created successfully.\n");
}

void Deposit_Money() {
    FILE *file = fopen(Account_File, "rb+");
    if (file == NULL) {
        printf("Unable to open file!\n");
        return;
    }

    int acc_no;
    float money;
    Account acc_to_read;

    printf("Enter your Account Number: ");
    scanf("%d", &acc_no);
    printf("Enter amount to deposit: ");
    scanf("%f", &money);

    while (fread(&acc_to_read, sizeof(acc_to_read), 1, file)) {
        if (acc_to_read.acc_no == acc_no) {
            acc_to_read.balance += money;
            fseek(file, -sizeof(acc_to_read), SEEK_CUR);
            fwrite(&acc_to_read, sizeof(acc_to_read), 1, file);
            fclose(file);
            printf("Successfully deposited %.2f.\nNew balance: %.2f\n", money, acc_to_read.balance);
            return;
        }
    }

    fclose(file);
    printf("Account number %d not found.\n", acc_no);
}

void Withdraw_Money() {
    FILE *file = fopen(Account_File, "rb+");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return;
    }

    int acc_no;
    float money;
    Account acc_to_read;

    printf("Enter your account number: ");
    scanf("%d", &acc_no);
    printf("Enter the amount to withdraw: ");
    scanf("%f", &money);

    while (fread(&acc_to_read, sizeof(acc_to_read), 1, file)) {
        if (acc_to_read.acc_no == acc_no) {
            if (acc_to_read.balance >= money) {
                acc_to_read.balance -= money;
                fseek(file, -sizeof(acc_to_read), SEEK_CUR);
                fwrite(&acc_to_read, sizeof(acc_to_read), 1, file);
                fclose(file);
                printf("Successfully withdrawn %.2f.\nRemaining balance: %.2f\n", money, acc_to_read.balance);
                return;
            } else {
                fclose(file);
                printf("Insufficient balance.\n");
                return;
            }
        }
    }

    fclose(file);
    printf("Withdrawal failed. Account number %d not found.\n", acc_no);
}

void Check_Balance() {
    FILE *file = fopen(Account_File, "rb");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    int acc_no;
    Account acc_read;

    printf("Enter your account number: ");
    scanf("%d", &acc_no);

    while (fread(&acc_read, sizeof(acc_read), 1, file)) {
        if (acc_read.acc_no == acc_no) {
            printf("\nAccount Holder: %s\nCurrent Balance: %.2f\n", acc_read.name, acc_read.balance);
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("Account number %d not found.\n", acc_no);
}

void Delete_Account() {
    int acc_no;
    int found = 0;
    Account acc;
    
    printf("Enter the account number to delete: ");
    scanf("%d", &acc_no);

    FILE *file = fopen(Account_File, "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (file == NULL || temp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fread(&acc, sizeof(acc), 1, file)) {
        if (acc.acc_no != acc_no) {
            fwrite(&acc, sizeof(acc), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp);

    remove(Account_File);
    rename("temp.dat", Account_File);

    if (found) {
        printf("Account number %d has been deleted successfully.\n", acc_no);
    } else {
        printf("Account number %d not found.\n", acc_no);
    }
}
