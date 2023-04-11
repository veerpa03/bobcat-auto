/**
 *    @file: hw_6.cc
 *  @author: viraj parmar
 *    @date: 04/10/2023         
 *   @brief: This program will is a user oriented program in which the user has to select the car model
 *           and the required option to add in it. This program will also remvoe the options added. User can also cancel
 *           the order.
 *  
 */


#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

///function prototypes

void displayMenu(int &choice, char &model) ;
// a function that displays the option menu
void optionOne(char &model, double &total, string &modelOfCar, int &choice) ;
// a function that picks the model based on user input
void addOpt(string &option, vector<string> names, vector<double> prices, vector<string> &selectedChoice, double &total, int &choice) ;
// function reads a inputted option, adds it to selectchoices and updates total
void printLn(vector<string> selectedChoice, double total, char &model) ;
// the line that displays model and total and options chosen
void displayNames(vector<string> names, vector<double> prices, int vCounts) ;
// displays the list of options
void cancelOrder(char &model, vector<string> &selectedChoice, double &total) ;
// resets all fields
void removeOpt(string &option, vector<string> &selectedChoice, double &total, vector<double> prices, vector<string> names) ;
// does the opposite of addOpt
string toUpper(string one) ;
// makes it so inputted option can be anything, not case sensitive

int main(int argc, char const *argv[]) {
vector<string> names(30) ; // creates vector for option names
vector<string> selectedChoice(0) ; // creates vector for selected choices
vector<double> prices(30) ; // creates vectors for prices
ifstream in ;
char model = 'P' ; // = to P so program knows if nothing is selected
string modelS ;
string option ;
string nameOfOption ;
int count = 0 ;
int vCount = 0 ;
int choice ;
double ePrice = 10000 ; // prices of the all of the models
double lPrice = 12000 ;
double xPrice = 18000 ;
double total = 0 ; // the total

//rounds to 2 decimal places
cout.setf(ios::fixed);
cout.setf(ios::showpoint);
cout.precision(2);
 
//opens file
in.open("options.txt") ;
//checks for failure
if(in.fail()) {
cout << "File error" << endl ;
return -1 ;
}

// while it reads numbers at beginning, it getlines the option name
while(in >> prices[vCount]){
getline(in, names[vCount]) ;
vCount ++ ;
}

// this get rids of the space before the name
for(int i = 0; i < vCount; i++){
names[i] = names[i].substr(1, (names[i]).length()-1) ;
}

//close file
in.close() ;

//starts by displaying the menu
displayMenu(choice,model) ;

// while choice != 6
while(choice != 6){
switch(choice){
case 1:
// the IF statement says if the model is already selected, and they change it, it subtratcs current model price and asks for the new model
count ++ ;
if(count > 1){
if(model == 'E'){
total -= ePrice ;
} else if(model == 'L'){
total -= lPrice ;
} else if(model == 'X'){
total -= xPrice ;
}
cout << "Enter the model (E, L, X): " ;
cin >> model ;
optionOne(model, total, modelS, choice) ;
} else {
cout << "Enter the model (E, L, X): " ;
cin >> model ;
optionOne(model, total, modelS, choice) ;
}
printLn(selectedChoice, total, model) ;
break ;
case 2:
displayNames(names, prices, vCount) ;
break ;
case 3:
// if they already have six options chosen it will not let this pick another, also if they have no model selected it asks them to do that
if(selectedChoice.size() != 6){
if(model == 'P' ){
cout << "Please enter a model." << endl ;
} else {
addOpt(option, names, prices, selectedChoice, total, choice) ;
printLn(selectedChoice, total, model) ;
}
} else {
cout << "You already have six options." << endl ;
}
break ;
case 4:
if(model == 'P' ){
cout << "Please enter a model." << endl ;
} else{
removeOpt(option, selectedChoice, total, prices, names) ;
printLn(selectedChoice, total, model) ;
}
break ;
case 5:
cancelOrder(model, selectedChoice, total) ;
break ;
case 6:
default:
break ;
}
displayMenu(choice,model) ;
}
return 0;
}/// main

void displayMenu(int &choice,char &model) {
    model = toupper(model);
    if(model=='P')
    {
        cout<<"NO MODEL SELECTED"<<endl;
    }
cout << "1. Select a model(E, L, X)" << endl ;
cout << "2. Display available options and prices" << endl ;
cout << "3. Add an option" << endl ;
cout << "4. Remove an option" << endl ;
cout << "5. Cancel order" << endl ;
cout << "6. Quit" << endl ;
cout << "Enter a choice: " ;
cin >> choice ; // assigning this value to the variable choice in main
}

void optionOne(char &model, double &total, string &modelOfCar, int &choice){
model = toupper(model) ; // takes the model and then adds the price to total
if(model == 'E'){
modelOfCar = "Model: E, " ;
total += 10000 ;
} else if(model == 'L'){
modelOfCar = "Model: L, " ;
total += 12000 ;
} else if(model == 'X'){
modelOfCar = "Model: X, " ;
total += 18000 ;
} else{
;
}
}

void addOpt(string &option, vector<string> names, vector<double> prices, vector<string> &selectedChoice, double &total, int &choice){
cout << "Enter an option name: " ;
cin >> ws ;
getline(cin, option) ;
int found = 0 ; // reads the line for the option

for(size_t i = 0; i < names.size(); i++){
//uses the toUpper function to compare
if(toUpper(option) == toUpper(names[i])){
found = i ; // if the option is found in the available options it saves the index for price
for(size_t i = 0; i < selectedChoice.size(); i++){
if(toUpper(option) == toUpper(selectedChoice[i])){// if the option entered is already in the selectedChoices it doesnt let them add it
cout << "You have already selected this option." << endl ;
cout << selectedChoice[i] ;
return ;
}
}
// adds the price of option to the total
total += prices[found] ;
// adds the option to the selected choices vector
selectedChoice.push_back(names[i]) ;
}
}
}

void removeOpt(string &option, vector<string> &selectedChoice, double &total, vector<double> prices, vector<string> names){
cout << "Enter an option name to remove: " ;
cin >> ws ;
getline(cin, option) ;
int found = 0;

for(size_t i = 0; i < selectedChoice.size(); i++){
// if the option is in the selected choice it saves index
if(toUpper(option) == toUpper(selectedChoice[i])){
found = i ;
} else {
continue ;
}
}
for(size_t i = 0; i < names.size(); i++){
if(toUpper(option) == toUpper(names[i])){
total -= prices[i] ; // subtracts the price of the option because it is now removed
}
}
// removes from the vector
selectedChoice.erase(selectedChoice.begin()+found) ;

}

// displays the names
void displayNames(vector<string> names, vector<double> prices, int vCount){
int threePer = 0 ;
cout << "Model E: $10,000, Model S: $12,0000, Model X: $18,000" << endl ;
for(int i = 0; i < vCount; i++){
cout << setw(25) << left << names[i] << "($" << prices[i] << ") ";
threePer ++ ;
if(threePer == 3){
cout << endl ;
threePer = 0 ;
}
}

}

void cancelOrder(char &model, vector<string> &selectedChoice, double &total){
model = 'P' ;
selectedChoice.clear() ;
total = 0 ;
cout << "Order canceled." << endl ;
// resets the order
}


// lthe line it prints after something is selected
void printLn(vector<string> selectedChoice, double total, char &model){
if(model == 'P'){
cout << "Please enter a model." << endl ;
} else {
cout << "Model " << model << " " << total << ", " << "Options: " ;
if(selectedChoice.size() == 0){
cout << endl ;
} else {
for(size_t i = 0; i < selectedChoice.size()-1; i++){
cout << selectedChoice[i] << ", " ;
}
cout << selectedChoice.back() << endl ;
}
}
}

//makes the string upper case to compare
string toUpper(string one){
for(size_t i = 0; i < one.length(); i++){
one[i] = toupper(one[i]) ;
}
return one ;
}