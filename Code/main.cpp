#include <iostream>
#include <string>
#include <vector>
#include "functions.h"

using namespace std;

int main() {
  //Variables 
  bool again = true;
  LinkedList<int> integerList;
  vector<Employee *> employees;
  string name;
  int id;
  double rate;
  int hours;
  double salary;
  int days;
  size_t indexSpot;
  int interger;
  char choice1;
  while(again){
    //Main menu for the program.
    cout << "Welcome to the menu where you can add from either an employee or an index." << endl;
    cout << "A. Add an integer" << endl;
    cout << "R. Remove an integer" << endl;
    cout << "D. Display the list" << endl;
    cout << "P. Add a Professional Employee"<< endl;
    cout << "N. Add a Nonprofessional Employee"<< endl;
    cout << "S. Show Employee Information"<< endl;
    cout << "Q. Quit Program"<< endl;
    cout << "Please enter in your choice: ";
    cin >> choice1;
    cout << endl << endl;
    switch(choice1){
      case 'a':
      case 'A':
        cout << "Enter an integer to add to the list: ";
        cin >> interger;
        integerList.pushBack(interger);
        cout << endl;
        break;
      case 'r':
      case 'R':
        cout << "Please enter a index of the list that you will like to remove: ";
        cin >> indexSpot;
        if (integerList.remove(indexSpot)) {
          cout << "The interger has been removed!" << endl << endl;
        }    
        else {
          cout << "This interger doesnt exist or the list is empty!" << endl << endl;
        }
        break;
      case 'd':{}
      case 'D':{
        cout << "Here is the current list: ";
        Node<int> *currentList = integerList.getHead();
        while (currentList != nullptr) {
          cout << currentList->data << " ";
          currentList = currentList->next;
        }
        cout << endl << endl;
        break;
      }
      case 'p':{}
      case 'P':{
        cout << "Please enter a Professional Employee info "<< endl;
        cout << "Employee Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Employee ID: ";
        cin >> id;
        cout << "Employees Monthly Salary: ";
        cin >> salary;
        cout << "Employees Vacation Days: ";
        cin >> days;
        cout << endl;
        employees.push_back(new ProfessionalEmp(name, id, salary, days));
        break;
      }
      case 'n':{}
      case 'N':{
      cout << "Please Enter a Nonprofessional Employee info: " << endl;
      cout << "Employee Name: ";
      cin.ignore();
      getline(cin, name);
      cout << "Employee ID: ";
      cin >> id;
      cout << "Employees Hourly Rate: ";
      cin >> rate;
      cout << "Employees Hours Worked: ";
      cin >> hours;
      cout << endl;
      employees.push_back(new NonprofessionalEmp(name, id, rate, hours));
      break;
      }
      case 's':{}
      case 'S':{
        cout << "Please input the Employee ID that you wish to see the information of: ";
        cin >> id;
      bool found = false;
      for (const auto &emp : employees) {
        if (emp->getId() == id) {
          emp->displayInfo();
          found = true;
          break;
        }
      }
      if (!found) {
        cout << "Sorry, the ID you entered doesnt match any employee" << endl << endl;
      }
      break;
      }
      case 'q':{}
      case 'Q':{
        cout << "Thank you for using this program! have a nice day. ";
        again = false;
        break;
      }
      
      default:{
        cout << "You entered a wrong input, please try again!" << endl <<endl;
      }
    }
  }
}
