#include <iostream>
#include <conio.h>
#include <iomanip> 
#include <string>
using namespace std;
int security_pin(int pin){
    bool if_running = true;
    int pin_input = 0;
    int digit;
    cout<<"Enter pin: ";
    while(if_running){
        // Read a character without echoing it
        digit = _getch(); // Use _getch() to get a character without displaying it
        // Check if the user pressed Enter (ASCII 13)
        if(digit == 13){
            cout<<endl; // Move to the next line after Enter
            if(pin_input == pin){
                if_running = false;
                cout<<"Select Service"<<endl<<endl;
                cout<<"Enter [1] to show balance"<<endl;
                cout<<"Enter [2] to Credit into account"<<endl;
                cout<<"Enter [3] to Debit from account into ksh account"<<endl;
                cout<<"Enter [4] to withdraw to M_pessa ccount"<<endl;
                cout<<"Enter [5] to Exit"<<endl<<endl;
            }else{
                cout<<"Incorrect Pin!"<<endl;
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
float available_balance = 1000;
float dollar_balance = 876.87;
float ksh_balance = 54789.65;
float exchange_rate = 133.89;
int showbalance(){
	cout<<fixed<<setprecision(2);
	cout<<"Available balance: $"<<available_balance<<endl;
	cout<<"Dollar balance: $"<<dollar_balance<<endl;
	cout<<"Ksh Balance: KSH"<<ksh_balance<<endl<<endl;
}
int credit(){
	cout<<fixed<<setprecision(2);
	float credit_amount;
	cout<<"Enter amount between $1.00 to $"<<available_balance<<" to Credit into account: ";
	cin>>credit_amount;
	if(credit_amount > available_balance){
		cout<<"Insufficient balance!"<<endl;
	}else if(credit_amount <= 0){
		cout<<"Invalid input!"<<endl;
	}else{
		dollar_balance += credit_amount;
		available_balance -= credit_amount;
		cout<<"Request to credit $"<<credit_amount<<" completed"<<endl;
		cout<<"Current dollar balance: $"<<dollar_balance<<endl<<endl;
	}
}
int debit(){
	cout<<fixed<<setprecision(2);
	float debit_amount;
	cout<<"Enter amount between $1.00 to $"<<dollar_balance<<" to credit ksh account: ";
	cin>>debit_amount;
	if(debit_amount > dollar_balance){
		cout<<"Insufficient balance!"<<endl;
	}else if(debit_amount <= 0){
		cout<<"Invalid input!"<<endl;
	}else{
		ksh_balance += (debit_amount * exchange_rate);
		dollar_balance -= debit_amount;
		cout<<"Request to credit $"<<debit_amount<<" into ksh account completed"<<endl;
		cout<<"Exchange rate: $1 = KSH"<<exchange_rate<<endl;
		cout<<"Current ksh balance: KSH"<<ksh_balance<<endl<<endl;
	}
}
int m_pesa(){
    string number;
    float amount;
    cout << "Enter your phone number: +254 ";
    cin >> number;
    if(number.length() != 9 || !isdigit(number[0]) || !isdigit(number[1]) || !isdigit(number[2]) || 
        !isdigit(number[3]) || !isdigit(number[4]) || !isdigit(number[5]) || 
        !isdigit(number[6]) || !isdigit(number[7]) || !isdigit(number[8]))
	{
        cout<<"Invalid phone number!"<<endl;
        return 1; // Return an error code
	}
    else{
    	cout<<fixed<<setprecision(2);
        cout<<"Available balance to withdraw: KSH"<<ksh_balance<<endl;
        cout<<"Enter amount between ksh100 to ksh250000: KSH";
        cin>>amount;
        if(amount <= 0){
            cout<<"Invalid input!"<<endl;
            return 1; // Return an error code
        }else if(amount >= 1 && amount < 100){
        	cout<<"More than one hundred bob buana!!!!"<<endl;
        	return 1;
		}else if(amount > 250000){
			cout<<"Less than two hundred and fifty thousand bob buana!!!!"<<endl;
		}
		else if(amount > ksh_balance){
            cout<<"Insufficient balance!"<<endl;
            return 1; // Return an error code
        }else{
            ksh_balance -= amount;
            cout<<"Request to withdraw KSH"<<amount<<" to M-Pesa account +254 "<<number<<" completed"<<endl;
            cout<<"Current balance: KSH"<<ksh_balance<<endl<<endl;
            return 0; // Successful operation
        }
    }
}
int main(int argc, char** argv){
	cout<<"Copyright 2025 PERSONAL BANK"<<endl;
	cout<<"Version 2.0.0"<<endl<<endl;
	cout<<"ACCOUNT NAME: IAN OMWOYO OTUKE"<<endl;
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
			cout<<"Option does not exist!!!!!!"<<endl;
		}
	}
	return 0;
}
