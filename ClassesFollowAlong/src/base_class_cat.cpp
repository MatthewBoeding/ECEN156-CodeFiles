#include <iostream>
#include <cstring>
using namespace std;


//Cats
// char furColor[12]; 
// char name[50];
// int age; 
// double weight; 
#include <cstring>

class Cat{
    private:
        char furColor[12]; 
        char name[50];
        int age; 
        double weight; 

    public:
        Cat();    //default constructor
        Cat(char * furColor, char * name, int age, double weight);
        //destructor
        ~Cat();

        //Getters
        double getWeight();
        //Setters
        void setWeight(double weight);
};

/* Constructors are done. yay! Never touch these again!*/
Cat::Cat() : furColor(""), name(""), age(0), weight(0)
{
    cout << "Default constructor for Cat has been called;" << endl;
}
Cat::Cat(char * furColor, char * name, int age, double weight)
: age(age), weight(weight)
{
    this->age = age;
    this->weight = weight;
    strncpy(this->furColor, furColor, 12);
    //TODO FIX the final character being \0
    strncpy(this->name, name, 50);
    cout << "Parameterized Constructor called" << endl;
}
//Destructor?
Cat::~Cat()
{
    cout << "Cat is gone" << endl;
}

void Cat::setWeight(double weight)
{
    this->weight = weight;
}

double Cat::getWeight()
{
    return this->weight;
}

int main(){
        Cat frodo("Orange", "Frodo", 7, 45);
        double startWeight = frodo.getWeight();
        cout << "Frodo needs to lose weight: " <<startWeight << endl;
        frodo.setWeight(35);

        double newWeight = frodo.getWeight();
        cout << "Yay frodo lost weight: " << newWeight << endl;
        
}