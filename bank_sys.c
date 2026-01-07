#include <stdio.h>
#include <string.h>

#define MAX_CUSTOMERS 20 // Maximum number of customers 20
#define MAX_TRANS 10  // Maximum number of transactions per customer

char name[MAX_CUSTOMERS][50]; // Customer name
int accNo[MAX_CUSTOMERS];         // Account number
double balance[MAX_CUSTOMERS];     // Account balance
char history[MAX_CUSTOMERS][MAX_TRANS][50]; // Transaction history
int transCount[MAX_CUSTOMERS]; // Number of transactions per customer

int totalCustomers = 0;

/* -------- Transaction Helper -------- */
void addTransaction(int i, char *type, double amt) {

    char msg[50];

    if (transCount[i] == MAX_TRANS) {
        for (int j = 1; j < MAX_TRANS; j++) {
            strcpy(history[i][j - 1], history[i][j]);
        }
        transCount[i]--;
    }
    sprintf(msg, "%s: %.2lf", type, amt);
    strcpy(history[i][transCount[i]++], msg);
}

/* -------- Banking Operations -------- */
void deposit(int i, double amt) {
    if (amt <= 0) {
        printf("Invalid deposit amount!\n");
        return;
    }
    balance[i] += amt;
    addTransaction(i, "Deposit successful",amt);
}


void withdraw(int i, double amt) {
    if (amt <= 0 || amt > balance[i]) {
        printf("Invalid withdrawal amount!\n");
        return;
    }
    balance[i] -= amt;
    addTransaction(i, "Withdrawal successful", amt);
}

void showBalance(int i) {
    printf("Current Balance: %.2lf\n", balance[i]);
}

void showTransactions(int i) {
    printf("\nTransaction History:\n");
    for (int j = 0; j < transCount[i]; j++) {
        printf("%d. %s\n", j + 1, history[i][j]);
    }
}

/* -------- Main Program -------- */
int main() {
    int choice, index;
    double amount;

    /* Sample customer setup */
    strcpy(name[0], "Test User");
    accNo[0] = 1001;
    balance[0] = 1000.0;
    transCount[0] = 0;
    totalCustomers = 1;

    index = 0; // working with first customer

    while (1) {
        printf("\n--- Simple Banking System ---\n");
        printf("1. Deposit\n");
        printf("2. Withdraw\n");
        printf("3. Check Balance\n");
        printf("4. View Transactions\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter deposit amount: ");
                scanf("%lf", &amount);
                deposit(index, amount);
                break;

            case 2:
                printf("Enter withdrawal amount: ");
                scanf("%lf", &amount);
                withdraw(index, amount);
                break;

            case 3:
                showBalance(index);
                break;

            case 4:
                showTransactions(index);
                break;

            case 5:
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}
