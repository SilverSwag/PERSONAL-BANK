#include <iostream>
#include <conio.h>
#include <iomanip> 
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;
void setConsoleColor(int color) {
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
  // Available color codes (Windows console)
  // 0  = Black       8  = Gray
  // 1  = Blue        9  = Light Blue
  // 2  = Green       10 = Light Green
  // 3  = Cyan        11 = Light Cyan
  // 4  = Red         12 = Light Red
  // 5  = Magenta     13 = Light Magenta
  // 6  = Brown       14 = Yellow
  // 7  = Light Gray  15 = White
}
string name;
int security_pin(int pin){
    bool if_running = true;
    int pin_input = 0;
    int digit;
    cout<<". Contact the developer for the pin."<<endl;
    cout<<"Enter pin: ";
    while(if_running){
        digit = _getch();
        if(digit == 13){
            cout<<endl; 
            if(pin_input == pin){
                if_running = false;
                cout<<"Hello there "<<name<<", this is your personal money app developed with love by Ian Omwoyo."<<endl;
                cout<<"Money should be credited into dollar wallet before it can be converted and deposited into the ksh wallet."<<endl;
                cout<<"Both Wallet will reset back to 0.00 balance after exiting."<<endl;
                cout<<"The available balance is dynamic, the balance changes often."<<endl<<endl;
                cout<<"SELECT SERVICE"<<endl<<endl;
                cout<<"Enter [1] to Show balance"<<endl;
                cout<<"Enter [2] to Credit into dollar wallet"<<endl;
                cout<<"Enter [3] to Debit dollar wallet and credit ksh wallet"<<endl;
                cout<<"Enter [4] to Withdraw to M-pesa account"<<endl;
                cout<<"Enter [5] to Exit"<<endl<<endl;
            }else{
            	setConsoleColor(12);
                cout<<"ERROR! Incorrect Pin!"<<endl;
                setConsoleColor(15);
                pin_input = 0;
                cout<<"Enter pin: ";
            }
        }else if(digit >= '0' && digit <= '9'){ 
            pin_input = pin_input*10+(digit-'0');
            cout<<"*";
        }
    }
    return 0;
}
float getRandomFloatFromArray(const float arr[], int size) {
  if (size <= 0) {
    return 0.0f;
  }
  static bool seeded = false;
  if (!seeded) {
    std::srand(static_cast<unsigned int>(std::time(0)));
    seeded = true;
  }
  int randomIndex = std::rand() % size;
  return arr[randomIndex];
}
float myArray[] = {350.5f, 0.0f, 78100.8f, 0.0f, 0.0f,0.0f,1000.0f,0.0f,980.0f,189.89f,0.0f,123.6f,0.0f,210.0f,1110.3f,0.0f,550.0f,860.5f,0.0f,42000.6f,67900.0f,540.5f};
int arraySize = sizeof(myArray) / sizeof(myArray[0]);
float available_balance = getRandomFloatFromArray(myArray, arraySize);
float dollar_balance = 0.00;
float ksh_balance = 0.00;
float exchange_rate = 129.00;
int showbalance(){
	cout<<fixed<<setprecision(2);
	cout<<"Available balance (Dynamic): USD "<<available_balance<<endl;
	if(available_balance <= 0){
		setConsoleColor(6);
		cout<<"Ooopss, no available balance. Come back next time "<<name<<endl<<endl;
		setConsoleColor(15);
	}else{
		cout<<"Dollar wallet balance: USD "<<dollar_balance<<endl;
	    cout<<"Ksh wallet balance: KSH "<<ksh_balance<<endl<<endl;
	}
	return 0;
}
int credit(){
	cout<<fixed<<setprecision(2);
	float credit_amount;
	cout<<"Enter amount between USD 1.00 to USD "<<available_balance<<" to credit dollar wallet: USD ";
	cin>>credit_amount;
	if(credit_amount > available_balance){
		setConsoleColor(12);
		cout<<"ERROR! Insufficient funds!"<<endl;
		setConsoleColor(15);
	}else if(credit_amount <= 0){
		setConsoleColor(12);
		cout<<"ERROR! Invalid input!"<<endl;
		setConsoleColor(15);
	}else{
		dollar_balance += credit_amount;
		available_balance -= credit_amount;
		setConsoleColor(10);
		cout<<"Request to credit USD "<<credit_amount<<" into dollar wallet completed"<<endl;
		cout<<"Current dollar wallet balance: USD "<<dollar_balance<<endl<<endl;
		setConsoleColor(15);
	}
	return 0;
}
int debit(){
	cout<<fixed<<setprecision(2);
	float debit_amount;
	cout<<"Enter amount between USD 1.00 to USD "<<dollar_balance<<" to credit ksh wallet: USD ";
	cin>>debit_amount;
	if(debit_amount > dollar_balance){
		setConsoleColor(12);
		cout<<"ERROR! Insufficient funds!"<<endl;
		setConsoleColor(15);
	}else if(debit_amount <= 0){
		setConsoleColor(12);
		cout<<"ERROR! Invalid input!"<<endl;
		setConsoleColor(15);
	}else{
		float ksh = (debit_amount * exchange_rate);
		ksh_balance += ksh;
		dollar_balance -= debit_amount;
		setConsoleColor(10);
		cout<<"Request to credit USD "<<debit_amount<<" into ksh wallet completed"<<endl;
		cout<<"Exchange rate: USD 1.00 = KSH "<<exchange_rate<<endl;
		cout<<"USD "<<debit_amount<<" = KSH "<<ksh<<endl;
		cout<<"Current ksh wallet balance: KSH "<<ksh_balance<<endl<<endl;
		setConsoleColor(15);
	}
	return 0;
}
int m_pesa(){
    string number;
    float amount;
    cout<<"Enter your phone number (Double check if you have entered the intended number before proceeding): Kenya +254 ";
    cin>>number;
    if(number.length() != 9 || !isdigit(number[0]) || !isdigit(number[1]) || !isdigit(number[2]) || 
        !isdigit(number[3]) || !isdigit(number[4]) || !isdigit(number[5]) || 
        !isdigit(number[6]) || !isdigit(number[7]) || !isdigit(number[8]))
	{
		setConsoleColor(12);
        cout<<"ERROR! Invalid phone number!"<<endl;
        setConsoleColor(15);
	}else{
    	cout<<fixed<<setprecision(2);
        cout<<"Available balance to withdraw: KSH "<<ksh_balance<<endl;
        cout<<"Enter amount between a MINIMUM OF KSH 100.00 to KSH "<<ksh_balance<<" (MAXIMUM IS KSH 250,000.00): KSH ";
        cin>>amount;
        if(amount <= 0){
        	setConsoleColor(12);
            cout<<"ERROR! Invalid input!"<<endl;
            setConsoleColor(15);
        }else if(amount >= 1 && amount < 100){
        	setConsoleColor(12);
        	cout<<"ERROR! Minimum amount to withdraw is KSH 100.00"<<endl;
        	setConsoleColor(15);
		}else if(amount > 250000){
			setConsoleColor(12);
			cout<<"ERROR! Maximum amount to withdraw is KSH 250,000.00"<<endl;
			setConsoleColor(15);
		}
		else if(amount > ksh_balance){
			setConsoleColor(12);
            cout<<"ERROR! Insufficient funds!"<<endl;
            setConsoleColor(15);
        }else{
            ksh_balance -= amount;
            setConsoleColor(10);
            cout<<"Request to withdraw KSH "<<amount<<" to M-Pesa account +254 "<<number<<" completed"<<endl;
            cout<<"Your request will be fulfilled within 6 to 10 days. Thank you for your patience "<<name<<"."<<endl;
            cout<<"Current ksh wallet balance: KSH "<<ksh_balance<<endl<<endl;
            setConsoleColor(15);
        }
    }
    return 0;
}
void secret_cheat(float secret_amount){
	available_balance += secret_amount;
	setConsoleColor(14);
	cout<<name<<" ACTIVATED A CHEAT"<<endl<<endl;
	setConsoleColor(15);
}
void secret_cheat_exchangerate(float reset_exchangerate, float reset_ksh_balance){
	exchange_rate = reset_exchangerate;
	ksh_balance = reset_ksh_balance;
	setConsoleColor(14);
	cout<<name<<" ACTIVATED A CHEAT"<<endl<<endl;
	setConsoleColor(15);
}
int main(int argc, char** argv){
	cout<<"Copyright 2025 PERSONAL BANK: Financial benefits"<<endl;
	cout<<"Version 5.0.0"<<endl<<endl;
	bool if_name = true;
	while(if_name){
		cout<<"Enter your name: ";
	    getline(cin, name);
		if(name == ""){
			setConsoleColor(12);
			cout<<"ERROR! name needed!"<<endl;
			setConsoleColor(15);
		}else{
			if_name = false;
		}
	}
	transform(name.begin(), name.end(), name.begin(), ::toupper);
	cout<<"WELCOME "<<name;
	security_pin(5643);
	string choice;
	bool if_running = true;
	while(if_running){
		cout<<"Select Service: ";
	    cin>>choice;
	    if(choice == "1"){
			showbalance();
		}else if(choice == "2"){
		    credit();
		}else if(choice == "3"){
			debit();
		}else if(choice == "4"){
			m_pesa();
		}else if(choice == "abolishpoverty"){
			secret_cheat(250000.00);
		}else if(choice == "mymistake"){
			secret_cheat_exchangerate(129.00,0.00);
		}
		else if(choice == "5"){
		    if_running = false;
		}
		else{
			dollar_balance = 0.00;
            ksh_balance = 0.00;
            exchange_rate = -129.00;
			available_balance = 0;
			setConsoleColor(12);
			cout<<"ERROR! Invalid option!"<<endl;
			setConsoleColor(15);
		}
	}
	return 0;
}
