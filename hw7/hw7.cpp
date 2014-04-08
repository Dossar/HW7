/* 
 * File:   hw7.cpp
 * Author: Roy Van Liew and Saqib Zahid
 *
 * Last modified on April 8, 2014, 5:28 PM
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
            double fee; // Withdrawal fee if account has already done a withdrawal.

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
    
    BankAccount account1;
    cin >> account1;
    cout << account1;

    return 0;
}

