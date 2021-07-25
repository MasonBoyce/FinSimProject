#include <stdbool.h>
typedef struct FinancialIdentity_struct {

double saving; //double because of money
double mortage; //double because of money
double loan; //double because of money
double houseBoughtPrice; //importnat for calculating house equity
double equityInHouse; //important for more acurate net worth
double checking; //double because of money
double debt; //double because of money
double mortgagePaid; //double cuz money
int yearWithDebt; //int because it is a year
double debtPaid; //double because of money
bool ownsHouse; //Bool becasue yes or no
int netWorth; //Final Wealth calculator

} FinancialIdentity;
// Make the two types of financialIdentity
FinancialIdentity f1;
FinancialIdentity nf1;

//Method Stubs

void savingsPlacement(FinancialIdentity *person, double interestRate);

void debt(FinancialIdentity *person, double interestRate, double addPay);

void rent(FinancialIdentity *person, double rentAmount);

void house(FinancialIdentity *person, double mortgageAmount, double interestRate, int mortgageTerm);

int *simulate(FinancialIdentity *person, double yearlySalary, bool financiallyLiterate);

void makePayment(FinancialIdentity *person, double payment);

void calculateWealth(FinancialIdentity *person);
