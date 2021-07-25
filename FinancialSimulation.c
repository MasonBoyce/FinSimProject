#include "FinancialSimulation.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void houseEquity(FinancialIdentity *person){
    //calculate equity in house
    person ->equityInHouse = person-> houseBoughtPrice  - person-> mortage;
}

void calculateWealth(FinancialIdentity *person){

    if (person->ownsHouse){
        houseEquity(person);
        person->netWorth = person->saving + person->checking+person->equityInHouse - person->debt-person->mortage;
    }
    else{
        person->netWorth = person->saving + person->checking - person->debt;
    }

}

void makePaymentHouse(FinancialIdentity *person, double payment){
    //check if they have enough money in checking account
    if (person->checking >= payment){
        person->checking -= payment;
    }
    //if not enough in checkings
    else{
        //take all the money out of checking and pay it
        payment -= person->checking;
        person->checking = 0;
        //take the rest out of savings
        person->saving -= payment;
    }
    // debt paid is the same as the payment
    person->mortgagePaid += payment;
    //they owe debtPaid less debt
    person->mortage -= payment;
}

void makePaymentDebt(FinancialIdentity *person, double payment){
    //check if they have enough money in checking account
    if (person->checking >= payment){
        person->checking -= payment;
    }
    //if not enough in checkings
    else{
        //take all the money out of checking and pay it
        payment -= person->checking;
        person->checking = 0;
        //take the rest out of savings
        person->saving -= payment;
    }
    // debt paid is the same as the payment
    person->debtPaid += payment;
    //they owe debtPaid less debt
    person->debt -= payment;
}

void makePaymentRent(FinancialIdentity *person, double payment){
    //check if they have enough money in checking account
    if (person->checking >= payment){
        person->checking -= payment;
    }
    //if not enough in checkings
    else{
        //take all the money out of checking and pay it
        payment -= person->checking;
        person->checking = 0;
        //take the rest out of savings
        person->saving -= payment;
    }
}

void savingsPlacement( FinancialIdentity *person, double interestRate){
    //they earn 1+intrest rate on thier savings account every year
    person->saving *= (1 + interestRate);
}



void debt(FinancialIdentity *person, double interestRate, double addPay){
    //monthly payments
    //addPay is additional amount paid off everymonth

    //find payment amount per month
    double monthlyRequired;
    double paymentAmount;

    //Loop to pay debt unless debt doesn't exist
    for (int month = 0; month < 12; month++){
        monthlyRequired = (.03 * person->debt);
        paymentAmount = addPay + monthlyRequired;
        if (person->debt >= paymentAmount){
            //payment method that takes money out of checking until out of money in checking then pays in savings
            makePaymentDebt(person, paymentAmount);
        }
        else {
            makePaymentDebt(person, person->debt);
        }
    }
    //adding a year with debt if debt does not equal 0 and increasing debt by the intrerst rate
    if (person->debt != 0){
        person->yearWithDebt += 1;
        person -> debt *= (1 + interestRate);
    }
}

void house(FinancialIdentity *person, double mortgageAmount, double interestRate, int mortgageTerm){
    //Formula given for monthly Payment
    int numberPayments = 12 * mortgageTerm;
    double monthlyInterest = interestRate / 12;
    double discountFactor = (pow(1 + monthlyInterest, numberPayments) - 1)/(monthlyInterest*pow(1 + monthlyInterest, numberPayments));
    double monthlyPayment = mortgageAmount / discountFactor;

    //Loop though and pay the mortgage every month unless mortage amount is 0
    for (int month = 0; month < 12; month++){
        if (person->mortage >= monthlyPayment){
            //payment method that takes money out of checking until out of money in checking then pays in savings
            makePaymentHouse(person, monthlyPayment);
        }
        else{
            makePaymentHouse(person, person->mortage);
        }
        //coumpounding Interest
        person->mortage *= (1 + monthlyInterest);
    }

}

void rent(FinancialIdentity *person, double rentAmount){
    //loop and pay every single month
    for (int month = 0; month < 12; month++){
        makePaymentRent(person, rentAmount);
    }

}



int *simulate( FinancialIdentity *person, double yearlySalary, bool financiallyLiterate){
    //intizle array using malloc with size of 41 intgers
    int* wealthSimulation = (int*)malloc(41*sizeof(int));
    //Calculating the wealth of the person at the start of the  simulation. In our simulation it should start with -47500
    //This value will be inputed into the first value of the Wealth Simulation vector
    calculateWealth(person);
    wealthSimulation[0] = person->netWorth;
    //Valulable variable that is the Initlial mortgage amount helpful for housing payment
    double mortageA;
    //In this simulation the house price will always be 210,000 Intilizing this at the begninning helps from repeating code
    person -> houseBoughtPrice =210000;
    //Initlizes boolean owns house to false
    person -> ownsHouse = false;

    //Loop for 40 years
    for (int i=1;i<41;i++){

        //Put 30% in checkings
        person ->checking += (yearlySalary*.3);

        //Put 20% in savings
        person ->saving += (yearlySalary*.2);

        //If the person is bool finnicially literate do the following
        if (financiallyLiterate){
            //savings with intrest of 7% a year
            savingsPlacement(person,.07);

            //debt with intrrest rate of 20% a year and 100 dollars extra per month
            debt(person,.2,100);

            //Every Year checks 3 conditions to see if person will buy house
            //First checks if it has the required 20% for a down payment
            //Second checks that they have not already own the house
            //Third makes sure that they can still afford to pay rent on top of downpayment. Otherwise you would get a negative savings value
            if (person->saving >= .2 * (person->houseBoughtPrice) && !person->ownsHouse && person->checking + person->saving >= .2*(person->houseBoughtPrice)+(950*12) ){
                //buys house
                person->ownsHouse = true;
                //pays the downPayment
                person ->saving -= .2 * (person->houseBoughtPrice);
                double downPayment = .2 * (person->houseBoughtPrice);
                //sets the mortgage equal to purchase price - down payment
                person -> mortage = person->houseBoughtPrice - downPayment;
                //mortageA is the orginal mortage amount that will be helpful in calculating the monthly housing payment
                mortageA = person->houseBoughtPrice - downPayment;
            }

            //if person doesnt own house pay rent
            if (!person->ownsHouse){
                rent(person,950);
            }
            //Otherwise pay mortgage
            else{
                house(person, mortageA,.045,30);
            }
        }
        //Finacnially not literate
        else{
            //Savings with intrest rate of 1% a year
            savingsPlacement(person,.01);

            //debt with intrrest rate of 20% a year and 1 dollar extra per month
            debt(person,.2,1);

            //Every Year checks 3 conditions to see if person will buy house
            //First checks if it has the required 20% for a down payment
            //Second checks that they have not already own the house
            //Third makes sure that they can still afford to pay rent on top of downpayment. Otherwise you would get a negative savings value
            if (person->saving>= .05 * (person->houseBoughtPrice) && !person->ownsHouse && person->checking + person->saving >= .05 * (person->houseBoughtPrice) + (950 * 12)){
                person->ownsHouse = true;
                //pays the downPayment
                person ->saving -= .05 * (person->houseBoughtPrice);
                double downPayment = .05 * (person->houseBoughtPrice);
                //sets the mortgage equal to purchase price - down payment
                person -> mortage = person->houseBoughtPrice - downPayment;
                //mortageA is the orginal mortage amount that will be helpful in calculating the monthly housing payment
                mortageA = person->houseBoughtPrice - downPayment;
            }
            //If doesnt own a house rents
            if (!person->ownsHouse){
                rent(person,950);
            }
            //Otherwise pay the mortgage at 5% intrest
            else{
                house(person,mortageA,.05,30);
            }

        }
        calculateWealth(person);
        wealthSimulation[i] = person->netWorth;
    } //End of Loop

    return wealthSimulation;
}

int main(void){
    //Intialzing the structs and files
    FILE *fl;
    FILE *nfl;
    FinancialIdentity Fl;
    FinancialIdentity NFl;

    //Initalizing struct to the intial scenario for checking saving for fl and nfl
    Fl.checking = 0;
    Fl.saving = 5000;
    Fl.debt = 52500;

    NFl.checking = 0;
    NFl.saving = 5000;
    NFl.debt = 52500;

    //run the simulations into new arrays
    int* fliterate = simulate(&Fl, 69000, true);
    int* nfliterate = simulate(&NFl, 69000, false);

    //open the  file to write to
    fl = fopen("output_fl.txt","w");

    //loop through array and print a new line for every data point
    for (int i = 0; i < 41; i++) {
        fprintf(fl, "%d\n", fliterate[i]);
    }
    //close file
    fclose(fl);
    //open file
    nfl = fopen("output_nfl.txt","w");

    //loop through array and print a new line for every data point
    for (int i = 0; i < 41; i++) {
        fprintf(nfl, "%d\n", nfliterate[i]);
    }
    //close file
    fclose(nfl);

    return 0;
}
