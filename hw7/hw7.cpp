/* 
 * File:   hw7.cpp
 * Author: Roy Van Liew and Saqib Zahid
 *
 * Last modified on April 11, 2014, 8:13 PM
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <typeinfo> // This library is for printing out the object's type.

using namespace std;

/* BankAccount is the base class for this program.
 * Variables inherited in the other two classes are:
 * - name, balance
 * Functions inherited in the other two classes are:
 * - transfer, withdraw, deposit, and the accessors.
 * Note: withdraw is overridden in the other two classes. */
class BankAccount{
    
    public:
        BankAccount(); // Default Constructor
        BankAccount(string accName, double amount); // Constructor with parameters
        
        /**** Methods and overloaded output operator for BankAccount ****/
        void transfer( BankAccount& To , double amount );
        void deposit( double amount ); // Put money into account
        virtual int withdraw( double amount ); // This is virtual so in transfer we use correct withdraw.              
        friend ostream& operator <<( ostream& out, const BankAccount& Account );

        /**** Accessor functions for account name and balance. ****/
        string getName(){ 
            return name;
        }
        double getBalance(){
            return balance;
        }
        /**** End Accessor function declarations ****/

    protected:
        string name; // Name of the owner of the account.
        double balance; // How much money is in the account.
    
};

// Default constructor for BankAccount.
BankAccount::BankAccount(){
    
    // Prompt user to enter name and balance. Balance must be positive.
    cout << "Please enter the owner of this account: ";
    cin >> name;
    do{
        cout << "Please enter the balance of this account: ";
        cin >> balance;
        if( balance < 0 )
            cout << "Balance must be at least $0.\n" << endl;
    }while( balance < 0 );
    
}

// Constructor with parameters for BankAccount. No user prompts here.
BankAccount::BankAccount( string accName, double amount ){
    
    name = accName;
    balance = amount;
    
}

/* MoneyMarketAccount is derived from BankAccount.
 * withdraw function is overridden so there is a withdrawal fee.
 * There is also a member variable keeping track of what's been withdrawn. */
class MoneyMarketAccount : public BankAccount{

    public:
            // Default constructor for MoneyMarketAccount, prompt use to enter in data
            MoneyMarketAccount() : BankAccount()
            {
                    cout << "Please enter the number of withdrawals that have occurred: ";
                    cin >> numOfWithdr;    
            }
            // Constructor with withdrawals parameter for MoneyMarketAccount.
            // Get name and balance parameters from BankAccount's parameter constructor.
            MoneyMarketAccount( string accName, double amount, int withDr ) : BankAccount( accName , amount )
            {
                    numOfWithdr = withDr;                
            }

            // Accessor for number of withdrawals
            int getWithdr(){
                return numOfWithdr;
            }
            int withdraw( double amount ); // Overridden withdraw for MoneyMarketAccount
            // friend functions are not inherited.
            friend ostream& operator <<( ostream& out, const MoneyMarketAccount& Account );
    protected:
            int numOfWithdr; // Number of withdrawals. If zero, withdrawal is free.

};

/* CDAccount is derived from BankAccount.
 * withdraw function is overridden so a penalty on interest rate is incurred. */
class CDAccount : public BankAccount{

    public:
            // Default constructor for CDAccount, prompt use to enter in data
            CDAccount() : BankAccount()
            {
                    cout << "Please enter interest rate (in percent): ";
                    cin >> interestRate;    
            }        
            // Constructor with interest parameter for CDAccount.
            // Get name and balance parameters from BankAccount's parameter constructor.
            CDAccount(string accName, double amount, double interest) : BankAccount( accName , amount )
            {
                    interestRate = interest;
            }
        
            // Accessor for interest rate
            double getInterest(){
                return interestRate;
            }
            int withdraw( double amount ); // Overridden withdraw for CDAccount
            // friend functions are not inherited.
            friend ostream& operator <<( ostream& out, const CDAccount& Account );            
    protected:
            double interestRate;

};

/*********************************************************/
/*              METHODS FOR BANKACCOUNT                  */
/*********************************************************/

// Add money to an account. This is inherited for all classes.
void BankAccount::deposit( double amount ){
    
    // If the amount is negative, do not deposit.
    if( amount < 0 ){
        cout << "Cannot deposit negative money." << endl;
        return;
    }
    else{
        balance += amount;
        cout << "Successfully deposited $" << amount << " into " << name << endl;
    }
    
}

// Withdraw money from BankAccount.
// Return 0 if balance is enough.
// Return 1 for insufficient funds or error case.
int BankAccount::withdraw( double amount ){
    
    // If withdraw amount is negative, it is an error case.
    if( amount < 0 ){
        cout << "Cannot withdraw negative money." << endl;
        return 1;
    }
    // If withdraw amount is higher than current balance, it is an error case.
    if( amount > balance ){
        cout << "Insufficient funds." << endl;
        return 1;
    }
    // Otherwise, amount to withdraw is legitimate.
    balance -= amount;
    cout << "Successfully withdrew $" << amount << " from Bank Account " << name << endl;
    return 0; // Returning 0 means the withdrawal was successful.
    
}

// Withdraw from one bank account to deposit to another. This is inherited for all classes.
// If withdraw returns 0, deposit is successful.
// If withdraw returns 1, no transfer is done.
void BankAccount::transfer( BankAccount& To , double amount ) {

	int status; // Determines if the account withdrawn from has sufficient funds or amount is valid.
	status = withdraw( amount ); // Withdraw from current account.
        // If status is zero, amount is legal.
	if( status == 0 ) {
		To.deposit( amount ); // Deposit to an account passed in the parameter
		cout << "Transferred $" << amount << " from " << name << " to " << To.getName() << endl;
	}
        // Otherwise, amount was either negative or too much.
	if( status == 1 )
		cout << "Transfer unsuccessful." << endl;

}

// Overloaded output operator for BankAccount
ostream& operator <<( ostream& out, BankAccount& Account ){
    
    out << "Type: Bank Account" << endl; // Print out what type of bank account it is
    out << "Owner: " << Account.getName() << endl;
    out << "Balance: $" << Account.getBalance() << endl;
    
}

/*********************************************************/
/*              METHODS FOR MONEYMARKETACCOUNT           */
/*********************************************************/

// Withdraw money from MoneyMarketAccount.
// Return 0 if balance is enough.
// Return 1 for insufficient funds or error case.
// Incur $1.50 penalty if withdrawals is greater than zero.
int MoneyMarketAccount::withdraw( double amount ){
    
    // If withdraw amount is negative, it is an error case.
    if( amount < 0 ){
        cout << "Cannot withdraw negative money." << endl;
        return 1;
    }
    // If withdraw amount is higher than current balance, it is an error case.
    if( amount > balance ){
        cout << "Insufficient funds." << endl;
        return 1;
    }
    // Otherwise, amount to withdraw is legitimate.
    // User gets one free withdrawal. If there has been one used already, incur $1.50 penalty.
    if( numOfWithdr == 0 ){
        balance -= amount;
        cout << "Successfully withdrew $" << amount << " from Money Market Account " << name << endl;
        numOfWithdr++;
        return 0; // Returning 0 means the withdrawal was successful.
    }
    if( numOfWithdr > 0 && ( amount + 1.50 ) <= balance ){
        balance -= ( amount + 1.50 );
        cout << "Successfully withdrew $" << ( amount + 1.50 ) << " from Money Market Account " << name << endl;
        numOfWithdr++;
        return 0; // Returning 0 means the withdrawal was successful.
    }
    if( ( amount + 1.50 ) > balance )
    {
        cout << "Insufficient funds." << endl;
        return 1;
    }
    
}

// Overloaded output operator for MoneyMarketAccount.
ostream& operator <<( ostream& out, MoneyMarketAccount& Account ){
    
    out << "Type: Money Market Account" << endl; // Print out what type of bank account it is
    out << "Owner: " << Account.getName() << endl;
    out << "Balance: $" << Account.getBalance() << endl;
    out << "Withdrawal count: " << Account.getWithdr() << endl;
    
}

/*********************************************************/
/*              METHODS FOR CDACCOUNT                    */
/*********************************************************/

// Withdraw money from MoneyMarketAccount.
// Return 0 if balance is enough.
// Return 1 for insufficient funds or error case.
// Incur 25% penalty on interest rate for any valid withdrawal amount made.
int CDAccount::withdraw( double amount ){
    
    // If withdraw amount is negative, it is an error case.
    if( amount < 0 ){
        cout << "Cannot withdraw negative money." << endl;
        return 1;
    }
    // If withdraw amount is higher than current balance, it is an error case.
    if( amount > balance ){
        cout << "Insufficient funds." << endl;
        return 1;
    }
    // Otherwise, amount to withdraw is legitimate.
    // Incur the 25% penalty to the interest rate and also subtract it from balance.
    double penalty = (interestRate*0.25);
    if( ( amount + (penalty/100.0) ) > balance ){
        cout << "Insufficient funds." << endl;
        return 1;
    }
    interestRate -= penalty; // Subtract 25% from interest as a penalty
    balance -= ( amount + (penalty/100.0) ); // interest rate is a percentage, so divide by 100
    cout << "Successfully withdrew $" << ( amount + (penalty/100.0) ) << " from CD Account " << name << endl;
    
    return 0; // Returning 0 means the withdrawal was successful.
    
}

// Overloaded output operator for CDAccount.
ostream& operator <<( ostream& out, CDAccount& Account ){
    
    out << "Type: CD Account" << endl; // Print out what type of bank account it is
    out << "Owner: " << Account.getName() << endl;
    out << "Balance: $" << Account.getBalance() << endl;
    out << "Interest rate: " << Account.getInterest() << "%" << endl;
    
}

// Start of main. Here we create three accounts each of different types.
int main() {
    
    // Create the three bank accounts.
    cout << "\nCreating Bank Account." << endl;
    BankAccount BA;
    cout << "\nCreating Money Market Account." << endl;
    MoneyMarketAccount MMA("MMA",250,0);
    cout << "\nCreating CD Account." << endl;
    CDAccount CDA;
    
    /**** TEST WITHDRAW AND DEPOSIT FUNCTIONS ****/
    
    // Test withdraw and deposit Bank Account
    cout << "\n*** Testing withdraw and deposit for " << BA.getName() << " ***\n" << endl;
    cout << BA << endl;
    BA.withdraw(50.00);
    cout << BA << endl;
    BA.deposit(100.00);
    cout << BA;
    
    // Test withdraw and deposit Money Market Account
    cout << "\n*** Testing withdraw and deposit for " << MMA.getName() << " ***\n" << endl;
    cout << MMA << endl;
    MMA.withdraw(50.00);
    cout << MMA << endl;
    MMA.deposit(100.00);
    cout << MMA;  

    // Test withdraw and deposit CD Account
    cout << "\n*** Testing withdraw and deposit for " << CDA.getName() << " ***\n" << endl;
    cout << CDA << endl;
    CDA.withdraw(50.00);
    cout << CDA << endl;
    CDA.deposit(100.00);
    cout << CDA;  
    
    /**** TEST TRANSFER FUNCTION ****/
    
    // Transfer from BA to CDA
    cout << "\n*** Testing transfer from " << BA.getName() << " to " << CDA.getName() << " ***\n" << endl;
    cout << BA << endl;
    cout << CDA << endl;
    BA.transfer(CDA,50);
    cout << endl;
    cout << BA << endl;
    cout << CDA;
    
    // Transfer from CDA to BA
    cout << "\n*** Testing transfer from " << CDA.getName() << " to " << BA.getName() << " ***\n" << endl;
    cout << CDA << endl;
    cout << BA << endl;
    CDA.transfer(BA,100);
    cout << endl;
    cout << CDA << endl;
    cout << BA;    

    // Transfer from BA to MMA
    cout << "\n*** Testing transfer from " << BA.getName() << " to " << MMA.getName() << " ***\n" << endl;
    cout << BA << endl;
    cout << MMA << endl;    
    BA.transfer(MMA,75);
    cout << endl;
    cout << BA << endl;
    cout << MMA;
    
    // Transfer from MMA to BA
    cout << "\n*** Testing transfer from " << MMA.getName() << " to " << BA.getName() << " ***\n" << endl;
    cout << MMA << endl;
    cout << BA << endl;    
    MMA.transfer(BA,150);
    cout << endl;
    cout << MMA << endl;
    cout << BA;    
    
    // Transfer from CDA to MMA
    cout << "\n*** Testing transfer from " << CDA.getName() << " to " << MMA.getName() << " ***\n" << endl;
    cout << CDA << endl;
    cout << MMA << endl;    
    CDA.transfer(MMA,175);
    cout << endl;
    cout << CDA << endl;
    cout << MMA;
    
    // Transfer from MMA to CDA
    cout << "\n*** Testing transfer from " << MMA.getName() << " to " << CDA.getName() << " ***\n" << endl;
    cout << MMA << endl;
    cout << CDA << endl;
    MMA.transfer(CDA,200);
    cout << endl;
    cout << MMA << endl;
    cout << CDA;    
    
    return 0;
    
}

