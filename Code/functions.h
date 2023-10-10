//Don't really needed to use a .cpp file for this .h file.
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename D> struct Node {
  D data;
  Node *next;
  Node(const D &item) : data(item), next(nullptr) {}
};

//This is a class for the linked list.
template <typename Item_Type> class LinkedList {
private:
  Node<Item_Type> *head;
  Node<Item_Type> *tail;
  size_t num_items;

public:
  LinkedList() : head(nullptr), tail(nullptr), num_items(0) {}
  Node<Item_Type> *getHead() const { return head; }

//This will push a number towards the front of the list that the user inputs.
  void pushFront(const Item_Type &item) {
    Node<Item_Type> *new_node = new Node<Item_Type>(item);
    if (empty()) {
      head = tail = new_node;
    } 
    else {
      new_node->next = head;
      head = new_node;
    }
    num_items++;
  }

  //Function will be used to put a number to the back of the list that the user inputs.
  void pushBack(const Item_Type &item) {
    Node<Item_Type> *new_node = new Node<Item_Type>(item);
    if (empty()) {
      head = tail = new_node;
    } 
    else {
      tail->next = new_node;
      tail = new_node;
    }
    num_items++;
  }

//This function will remove the interger in the front of the list.
  void popFront() {
    if (empty()) {
      cout << "There is no intergers in the list, cannot use the popFront() function." << endl << endl;
      return;
    }
    Node<Item_Type> *temp = head;
    head = head->next;
    delete temp;
    num_items--;
  }

//This function will remove the interger in the back of the list.
  void popBack() {
    if (empty()) {
      cout << "There is no intergers in the list, cannot use the function popBack() function." << endl << endl;
      return;
    }
    if (head == tail) {
      delete head;
      head = tail = nullptr;
    } 
    else {
      Node<Item_Type> *temp = head;
      while (temp->next != tail) {
        temp = temp->next;
      }
      delete tail;
      tail = temp;
      tail->next = nullptr;
    }
    num_items--;
  }

  //This function will get the index of the first intergers in the list.
  Item_Type front() const {
    if (empty()) {
      cout << "There is no intergers in the list, cannot use front() function." << endl << endl;
      return Item_Type();
    }
    return head->data;
  }

  //This function will get the index of the back intergers in the list.
  Item_Type back() const {
    if (empty()) {
      cout << "List is empty, cannot access back()." << endl << endl;
      return Item_Type();
    }
    return tail->data;
  }

  bool empty() const { return num_items == 0; }

  //This function will enter a interger to the list.
  void insert(size_t index, const Item_Type &item) {
    if (index > num_items) {
      pushBack(item);
    } 
    else if (index == 0) {
      pushFront(item);
    } 
    else {
      Node<Item_Type> *new_node = new Node<Item_Type>(item);
      Node<Item_Type> *temp = head;
      for (size_t i = 0; i < index - 1; i++) {
        temp = temp->next;
      }
      new_node->next = temp->next;
      temp->next = new_node;
      num_items++;
    }
  }

  //This function will take away an interger from the list that the user requested.
  bool remove(size_t index) {
    if (empty() || index >= num_items) {
      return false;
    }
    if (index == 0) {
      popFront();
    } 
    else {
      Node<Item_Type> *temp = head;
      for (size_t i = 0; i < index - 1; i++) {
        temp = temp->next;
      }
      Node<Item_Type> *to_delete = temp->next;
      temp->next = to_delete->next;
      delete to_delete;
      if (index == num_items - 1) {
        tail = temp;
      }
      num_items--;
    }

    return true;
  }

  //This function will find the requested index of the list.
  size_t find(const Item_Type &item) const {
    Node<Item_Type> *temp = head;
    size_t index = 0;
    while (temp != nullptr) {
      if (temp->data == item) {
        return index;
      }
      temp = temp->next;
      index++;
    }
    return num_items;
  }

  ~LinkedList() {
    while (!empty()) {
      popFront();
    }
  }
};

//Base class for Employee
class Employee {
protected:
  std::string name;
  int id;

public:
  Employee(const std::string &n, int i) : name(n), id(i) {}
  //These functions sets the values to each function to 0.
  virtual double WeeklySalary() const = 0;
  virtual double HealthCareContributions() const = 0;
  virtual int VacationDays() const = 0;
  virtual int getId() const { return id; }
  virtual void displayInfo() const {
    cout << "Employee Name: " << name <<  endl <<"Employee ID: " << id << endl;
  }
};

// inheritance class for Professional Employees from the base class employee.
class ProfessionalEmp : public Employee {
private:
  double monthlySalary;
  int vacationDays;

public:
  ProfessionalEmp(const std::string &n, int i, double salary, int days)
      : Employee(n, i), monthlySalary(salary), vacationDays(days) {}

  // This function will assume a month has 4 weeks
  double WeeklySalary() const override {
    return monthlySalary / 4;
  }

  //This function will caluclaute 20% of weekly salary for healthcare
  double HealthCareContributions() const override {
    return 0.2 * monthlySalary; 
  }

  int VacationDays() const override { return vacationDays; }

  void displayInfo() const override {
    Employee::displayInfo();
    cout << "Salary: $" << monthlySalary << " per month" << endl;
    cout << "Healthcare Contributions: $" << HealthCareContributions() << " per week" << endl;
    cout << "Vacation Days: " << vacationDays << " days per year" << endl << endl;
  }
};

// Derived class for Nonprofessional Employees
class NonprofessionalEmp : public Employee {
private:
  double hourlyRate;
  int hoursWorked;

public:
  NonprofessionalEmp(const std::string &n, int i, double rate, int hours)
      : Employee(n, i), hourlyRate(rate), hoursWorked(hours) {}

   //returns how much the nonprofessional employee makes per week
  double WeeklySalary() const override {
    return hourlyRate * hoursWorked;
  }

  // This function will caluclaute 10% of weekly salary for healthcare
  double HealthCareContributions() const override {
    return 0.1 * WeeklySalary();
  }

  // This will assume that 1 hour of work gives 0.1 vacation day
  int VacationDays() const override {
    return hoursWorked / 10;
  }

  //This function displays the employees infomation
  void displayInfo() const override {
    Employee::displayInfo();
    cout << "Hourly Rate: $" << hourlyRate << " per hour" << endl;
    cout << "Hours Worked: " << hoursWorked << " hours per week" << endl;
    cout << "Salary: $" << WeeklySalary() << " per week" << endl;
    cout << "Healthcare Contributions: $" << HealthCareContributions() << " per week" << endl;
    cout << "Vacation Days: " << VacationDays()  << " days per year" << endl << endl;
  }
};
