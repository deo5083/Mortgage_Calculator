/*
 David Ortiz
 10/17/2017
 
 Program will create an amortization schedule for a loan using user entered-principal, annual interest rate,
 and term of the loan, formatted according to directions given.

 */

#include <iostream>
#include<cmath>
#include<iomanip>
#include<fstream>

using namespace std;

int main() {
    double principal; //will hold the principal for the loan and will be used to calculate the results.
    double origPrincipal; //will store the copy of the principal, since principal will be subtracted with every payment.
    double annualInt; //will hold the annual interest rate as a percent
    double termYears; //will hold the term of the loan in years
    double monthlyInt;//converts annualInt to a monthly interest, then made a decimal.
    double monthlyPay; //will store the result of the interest forula, using principal, monthlyInt, and termMonths.
    double termMonths;//term of the loan in months, calculated using termYears.
    double interestAccured; //will calculate the monthly interest * remaiaining principal
    double totalPaid; //will calculate the total amount paid according to monthly payments * loan monthly terms
    double totalInt; //will calculate the reesult of the total paid - original principal, to see how much the user paid after interest.
    int count=0; //will used to keep track and print the month number, starting with 0
    
    bool valid = false; //setting valid to false; will be true if principal input is valid.

    
    ofstream output("Amortization.txt"); //for others

    
    //validating principal input.
    while(!valid){
        
        cout << "Enter the principal: ";
        cin >> principal;
        
        origPrincipal = principal;
        if(principal>0) valid=true;
        else cout <<"Enter a positive, nonzero principal amount!\n";
        
    } // end of while
    
    cout << "Enter the ANNUAL interest rate (in percent form): ";
    cin >> annualInt;
    
    cout << "Enter the term of the loan (in years): ";
    cin >> termYears;
    
    //calculations
    monthlyInt = (annualInt/12)/100;
    termMonths = termYears*12.0;
    monthlyPay = ((principal*monthlyInt)*pow((1+monthlyInt), termMonths))/(pow((1+monthlyInt), termMonths)-1);
    totalPaid = 0.00;
    
    //formatting the summary table for the output file
    for(int i=1; i<30; i++)output<<"-";
    output << endl;
    output << setw(12) <<  setprecision(2) << fixed << left << "Principal: " << setw(15) << right << origPrincipal << endl;
    for(int i=1; i<30; i++)output<<"-";
    output << endl;
    output << setw(12) << resetiosflags(ios::fixed) <<  left << "APR: " << setw(14) << right << annualInt << "%" << endl;
    for(int i=1; i<30; i++)output<<"-";
    output << endl;
    output << setw(12) <<  left << "Years: " << setw(15) << right << termYears << endl;
    for(int i=1; i<30; i++)output<<"-";
    output << endl;
    output << setw(12) <<  setprecision(2) << fixed <<  left << "Payment: " << setw(15) << right << monthlyPay  << endl;
    for(int i=1; i<30; i++)output<<"-";
    output << endl << endl;
    
    //headers for the payment schedule table for the output file and formats the table.
    output << setprecision(2) <<fixed << setw(10) << "Month #" <<setw(15)<< "Balance Owed" << setw(20) << "Interest Accrued" << setw(15)<< "Payment Made" << endl;
    for(int i=1; i<65; i++)output<<"-";
    output << endl;
    
    //setting each row of the payment schedule.
    do{
        interestAccured = principal*monthlyInt;

        //each row
        output << fixed<< setw(10)<< count << setw(15) << principal << setw(20) << interestAccured << setw(15) << monthlyPay << endl;
        
        principal = (principal+interestAccured)-monthlyPay;
        totalPaid += monthlyPay;
        count++;

    }while(count<termMonths); // end of do while
    
    //last row
    interestAccured = principal*monthlyInt;
    output << setprecision(0) << setw(10)<< termMonths << setw(15) << principal << setw(20) << interestAccured << endl;

    totalInt = totalPaid-origPrincipal;
    
    //outputting total table; formatted neatly.
    output << endl;
    for(int i=1; i<40; i++)output<<"-";
    output << endl;
    output <<setprecision(2) << fixed << setw(20) <<  left << "Total interest: " << setw(15) << right << totalInt << endl;
    for(int i=1; i<40; i++)output<<"-";
    output << endl;
    output << setw(20) << left << "Total paid: " << setw(15) << right << totalPaid << endl;
    for(int i=1; i<40; i++)output<<"-";
    output << endl;
    output << endl;
    
    //informing user of the output file name.
    cout << endl;
    cout << "Output is in \"Amortization.txt\"."<< endl << endl;
    
    output.close();
    
    system("pause");
    
} // end of main()
