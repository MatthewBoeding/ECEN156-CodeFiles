#include <iostream>
#include <cstring>
#include "pet_class.h"
using namespace std;


//Cats
// char furColor[12]; 
// char name[50];
// int age; 
// double weight; 
#include <cstring>

class Cat : public Pet{
    private:
        char furColor[12]; 
        double weight; 

    public:
        Cat();    //default constructor
        Cat(char * furColor, double weight, char* name, bool canTalk, char* species, char* ownerName, int age);
        //destructor
        ~Cat();

        //Getters
        double getWeight();
        //Setters
        void setWeight(double weight);
};

/* Constructors are done. yay! Never touch these again!*/
Cat::Cat() : furColor(""), weight(0), Pet::Pet()
{
    cout << "Default constructor for Cat has been called;" << endl;
}
Cat::Cat(char * furColor, double weight, char* name, bool canTalk, char* species, char* ownerName, int age)
: Pet::Pet(name, canTalk, species, ownerName, age)
{
    this->weight = weight;
    strncpy(this->furColor, furColor, 12);
    //TODO FIX the final character being \0
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
        Cat frodo("Orange", 45, "Frodo", true, "Komodo Dragon", "Grace", 55);
        double startWeight = frodo.getWeight();
        cout << "Frodo needs to lose weight: " <<startWeight << endl;
        frodo.setWeight(35);

        double newWeight = frodo.getWeight();
        cout << "Yay frodo lost weight: " << newWeight << endl;
        
}