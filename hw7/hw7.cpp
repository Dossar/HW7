/* 
 * File:   hw7.cpp
 * Author: Roy Van Liew and Saqib Zahid
 *
 * Last modified on April 9, 2014, 11:17 AM
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
//        BankAccount(); // Default Constructor
//        BankAccount(const BankAccount& Account); // Copy Constructor
//        ~BankAccount(); // Destructor
        void transfer( BankAccount& To , double amount );
        void deposit( double amount ); // Put money into account
        int withdraw( double amount ); // int returned: 0 for "ok", 1 for "insufficient funds".
        
        /**** Overloaded operators ****/
        friend ostream& operator <<(ostream& out, const BankAccount& Account);
        friend istream& operator >>(istream& in, BankAccount& Account);

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

// Inherited from BankAccount, has withdrawal fees.
class MoneyMarketAccount : BankAccount{

    public:
            int withdraw( double amount ); // Overridden withdraw for MoneyMarketAccount
    protected:
            int numOfWithdr; // Number of withdrawals. If zero, withdrawal is free.

};

// Inherited from BankAccount, has interest rate.
class CDAccount : BankAccount{

    public:
            int withdraw( double amount ); // Overridden withdraw for CDAccount
    protected:
            double interestRate;

};

//// Example of transfer
//void BankAccount::transfer( BankAccount& To , double amount ) {
//
//	int status;
//	status = withdraw( amount ); // Withdraw from current account. Return 0 for ok, return 1 for insufficient funds.
//	if( status == 0 ) {
//		To.deposit( amount ); // Deposit to an account passed in the parameter
//		cout << "Transferred $" << amount << endl;
//	}
//	if( status == 1 )
//		cout << "Insufficient funds." << endl;
//
//}

/*********************************************************/
/*              FUNCTION STUFF FOR CLASSES               */
/*********************************************************/

// Add money to BankAccount.
void BankAccount::deposit( double amount ){
    
    // If the amount is negative, do not deposit.
    if( amount < 0 )
        cout << "Cannot deposit negative money." << endl;    
    else
        balance += amount;
    
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
    
}

// Overloaded output operator
ostream& operator <<(ostream& out, const BankAccount& Account){
    
    out << "Type: " << typeid(Account).name() << endl; // Print out what type of bank account it is
    out << "Owner: " << Account.name << endl;
    out << "Balance: $" << Account.balance << endl;
    
}

// Overloaded input operator
istream& operator >>(istream& in, BankAccount& Account){
    
    cout << "Input owner's name: ";
    in >> Account.name;
    cout << "Input balance: ";
    in >> Account.balance;
    cout << endl;
    
}

int main() {
    
    // Create a bank account and test the input and output operators.
    BankAccount account1;
    cin >> account1;
    // Testing deposit and withdraw
    account1.deposit(-2);
    account1.deposit(100.25);
    account1.withdraw(-1);
    account1.withdraw(300.50);
    cout << account1;

    return 0;
}

