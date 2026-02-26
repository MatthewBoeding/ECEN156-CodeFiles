#include <cstring>
#include <iostream>

class Turtle{
    public:
        //Constructors
        Turtle();
        Turtle(int age, char * shell, double weight, bool doesBite);
        //Destructor
        virtual ~Turtle() {}

        //Getters and Setters
        int getAge() const {return age;}
        const char *getShell() const {return shell;}
        double getWeight() const{return weight;}
        virtual bool getDoesBite() {return doesBite;}

        void setAge(int age) {this->age = age;}
        void setShell(char* shell){strcpy(this->shell, shell);}
        void setWeight(double weight) {this->weight = weight;}
        void setDoesBite(bool doesBite) {this->doesBite = doesBite;}

        virtual void displayFunFact() const = 0;

    private:
        int age;
        char shell[15];
        double weight;
        bool doesBite;
};

Turtle::Turtle() : age(0), shell(""), weight(0.0), doesBite(true)
{}

Turtle::Turtle(int age, char * shell, double weight, bool doesBite)
{
    this->age = age;
    strcpy(this->shell, shell);
    this->weight = weight;
    this->doesBite = doesBite;   
}

class PaintedTurtle : public Turtle{
    private:
        char paintColor[15];
        char pattern[20];
    public:
        PaintedTurtle();
        PaintedTurtle(char * paintColor, char * pattern, int age, char * shell, double weight, bool doesBite);

        virtual ~PaintedTurtle() {}

        char * getPaintColor() {return paintColor;}
        char * getPattern() {return pattern;}

        void setPaintColor(char * paintColor) {strcpy(this->paintColor, paintColor);}
        void setPattern(char * pattern) {strcpy(this->pattern, pattern);}

        bool getDoesBite() override;
        void displayFunFact() const override;
        
};
PaintedTurtle::PaintedTurtle() : Turtle(), paintColor(""), pattern("")
{
    strcpy(this->paintColor, "");
    strcpy(this->pattern, "");
}

PaintedTurtle::PaintedTurtle(char * paintColor, char * pattern, int age, char * shell, double weight, bool doesBite)
: Turtle(age, shell, weight, doesBite)
{
    strcpy(this->paintColor, paintColor);
    strcpy(this->pattern, pattern);
}

bool PaintedTurtle::getDoesBite(){
    return false;
}

void PaintedTurtle::displayFunFact() const {
    std::cout << "Painted Turtles are Cute \n" << "Painted Turtles are not acutally painted\n";
}

int main()
{
    PaintedTurtle yurtle("Orange", "Stripes", 2, "Square", 2, true);
    bool biter = yurtle.getDoesBite();
}