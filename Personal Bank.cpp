#include <iostream>
#include <conio.h>
#include <iomanip> 
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;
string name;
int security_pin(int pin){
    bool if_running = true;
    int pin_input = 0;
    int digit;
    cout<<"Contact the developer for the pin."<<endl;
    cout<<"Enter pin: ";
    while(if_running){
        // Read a character without echoing it
        digit = _getch(); // Use _getch() to get a character without displaying it
        // Check if the user pressed Enter (ASCII 13)
        if(digit == 13){
            cout<<endl; // Move to the next line after Enter
            if(pin_input == pin){
                if_running = false;
                transform(name.begin(), name.end(), name.begin(), ::toupper);
                cout<<"Welcome "<<name<<", this is your personal bank app account."<<endl;
                cout<<"Money should be credited into dollar wallet before it can be converted and deposited into the ksh wallet."<<endl;
                cout<<"Both Wallet will reset back to 0.00 balance after exiting and the available balance will reset back to the amount it was before exiting."<<endl<<endl;
                cout<<"Select Service"<<endl<<endl;
                cout<<"Enter [1] to show balance"<<endl;
                cout<<"Enter [2] to Credit into dollar wallet"<<endl;
                cout<<"Enter [3] to Debit dollar wallet and credit ksh wallet"<<endl;
                cout<<"Enter [4] to withdraw to M-pesa account"<<endl;
                cout<<"Enter [5] to Exit"<<endl<<endl;
            }else{
                cout<<"ERROR! Incorrect Pin!"<<endl;
                pin_input = 0; // Reset pin_input for the next attempt
                cout<<"Enter pin: "; // Prompt again
            }
        }else if(digit >= '0' && digit <= '9'){ // Check if the input is a digit
            pin_input = pin_input*10+(digit-'0'); // Build the pin_input number
            cout<<"*"; // Print an asterisk for each digit entered
        }
    }
    return 0; // Return 0 or any other value as needed
}
float available_balance = 350.00;
float dollar_balance = 0.00;
float ksh_balance = 0.00;
float exchange_rate = 129.00;
int showbalance(){
	cout<<fixed<<setprecision(2);
	cout<<"Available balance: $"<<available_balance<<endl;
	cout<<"Dollar wallet balance: $"<<dollar_balance<<endl;
	cout<<"Ksh wallet balance: KSH"<<ksh_balance<<endl<<endl;
}
int credit(){
	cout<<fixed<<setprecision(2);
	float credit_amount;
	cout<<"Enter amount between $1.00 to $"<<available_balance<<" to credit dollar wallet: ";
	cin>>credit_amount;
	if(credit_amount > available_balance){
		cout<<"ERROR! Insufficient funds!"<<endl;
	}else if(credit_amount <= 0){
		cout<<"ERROR! Invalid input!"<<endl;
	}else{
		dollar_balance += credit_amount;
		available_balance -= credit_amount;
		cout<<"Request to credit $"<<credit_amount<<" into dollar wallet completed"<<endl;
		cout<<"Current dollar wallet balance: $"<<dollar_balance<<endl<<endl;
	}
}
int debit(){
	cout<<fixed<<setprecision(2);
	float debit_amount;
	cout<<"Enter amount between $1.00 to $"<<dollar_balance<<" to credit ksh wallet: ";
	cin>>debit_amount;
	if(debit_amount > dollar_balance){
		cout<<"ERROR! Insufficient funds!"<<endl;
	}else if(debit_amount <= 0){
		cout<<"ERROR! Invalid input!"<<endl;
	}else{
		float ksh = (debit_amount * exchange_rate);
		ksh_balance += ksh;
		dollar_balance -= debit_amount;
		cout<<"Request to credit $"<<debit_amount<<" into ksh wallet completed"<<endl;
		cout<<"Exchange rate: $1.00 = KSH"<<exchange_rate<<endl;
		cout<<"$"<<debit_amount<<" = ksh"<<ksh<<endl;
		cout<<"Current ksh wallet balance: KSH"<<ksh_balance<<endl<<endl;
	}
}
int m_pesa(){
    string number;
    float amount;
    cout<<"Enter your phone number (Double check if you have entered the intended number before proceeding): +254 ";
    cin>>number;
    if(number.length() != 9 || !isdigit(number[0]) || !isdigit(number[1]) || !isdigit(number[2]) || 
        !isdigit(number[3]) || !isdigit(number[4]) || !isdigit(number[5]) || 
        !isdigit(number[6]) || !isdigit(number[7]) || !isdigit(number[8]))
	{
        cout<<"ERROR! Invalid phone number!"<<endl;
	}
    else{
    	cout<<fixed<<setprecision(2);
        cout<<"Available balance to withdraw: KSH"<<ksh_balance<<endl;
        cout<<"Enter amount between a MINIMUM OF ksh100.00 to ksh"<<ksh_balance<<" (MAXIMUM IS ksh250,000.00): KSH";
        cin>>amount;
        if(amount <= 0){
            cout<<"ERROR! Invalid input!"<<endl;
        }else if(amount >= 1 && amount < 100){
        	cout<<"ERROR! Minimum amount to withdraw is ksh100.00"<<endl;
		}else if(amount > 250000){
			cout<<"ERROR! Maximum amount to withdraw is ksh250,000.00"<<endl;
		}
		else if(amount > ksh_balance){
            cout<<"ERROR! Insufficient funds!"<<endl;
        }else{
            ksh_balance -= amount;
            cout<<"Request to withdraw KSH"<<amount<<" to M-Pesa account +254 "<<number<<" completed"<<endl;
            cout<<"Current ksh wallet balance: KSH"<<ksh_balance<<endl<<endl;
        }
    }
}
int main(int argc, char** argv){
	cout<<"Copyright 2025 PERSONAL BANK: Financial benefits"<<endl;
	cout<<"Version 3.2.0"<<endl<<endl;
	cout<<"Enter your name: ";
	getline(cin, name);
	transform(name.begin(), name.end(), name.begin(), ::toupper);
	cout<<"ACCOUNT NAME: "<<name<<endl;
	security_pin(5643);
	int choice;
	bool if_running = true;
	while(if_running){
		cout<<"Select Option: ";
		cin>>choice;
		if(choice == 1){
			showbalance();
		}else if(choice == 2){
		    credit();
		}else if(choice == 3){
			debit();
		}else if(choice == 4){
			m_pesa();
		}else if(choice == 5){
			if_running = false;
		}
		else{
			cout<<"ERROR! Invalid option!"<<endl;
		}
	}
	return 0;
}
