#include "pet_class.h"
#include <cstring>

Pet::Pet() : name(""), canTalk(false), species(""), ownerName(""), age(0)
{
}

Pet::Pet(char * name, bool canTalk, char* species, char* ownerName, int age)
{
    strcpy(this->name, name); // error checking strncpy(this->name, name, 50);
    this->canTalk = canTalk;
    strcpy(this->ownerName, ownerName);
    strcpy(this->species, species);
    this->age = age;
}

Pet::~Pet(){}

char* Pet::getName()
{
    return this->name;
}

bool Pet::getCanTalk()
{
    return this->canTalk;
}

char* Pet::getSpecies()
{
    return this->species;
}

char* Pet::getOwnerName()
{
    return this->ownerName;
}

int Pet::getAge(){
    return this->age;
}

void Pet::setAge(int age)
{
    this->age = age;
}

void Pet::setName(char * name)
{
    strcpy(this->name, name);
}

void Pet::setCanTalk(bool canTalk)
{
    this->canTalk = canTalk;
}

void Pet::setSpecies(char * species)
{
    strcpy(this->species, species);
}

void Pet::setOwnerName(char * ownerName)
{
    strcpy(this->ownerName, ownerName);
}