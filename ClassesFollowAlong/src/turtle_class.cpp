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

        virtual void displayFunFact() const;

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

void Turtle::displayFunFact() const {
    std::cout << "Turtles are Cute \n";
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

class SnappingTurtle : public Turtle{
    private:
        char attitude[20];
    public:
        SnappingTurtle();
        SnappingTurtle(char * attitude, int age, char * shell, double weight, bool doesBite);

        virtual ~SnappingTurtle() {}

        char * getAttitude() {return attitude;}

        void setAttitude(char * attitude) {strcpy(this->attitude,attitude); }
        void displayFunFact() const override;
};

SnappingTurtle::SnappingTurtle() : Turtle(), attitude("Spicy")
{}

SnappingTurtle::SnappingTurtle(char * attitude, int age, char * shell, \
    double weight, bool doesBite) : Turtle(age, shell, weight, doesBite)
    {
        strcpy(this->attitude, attitude);
    }
void SnappingTurtle::displayFunFact() const{
    std::cout << "Snapping Turtles are Ugly and They like to bite.\n";
}

struct TurtleNode{
    Turtle * turtle;     //Polymorphic pointers
    TurtleNode * next;
};

class TurtleList{
    private:
        TurtleNode * head;
        TurtleNode * tail;

    public:
        TurtleList();
        TurtleList(TurtleNode * head, TurtleNode * tail);

        ~TurtleList();

        bool deleteAtIndex(int i);
        bool deleteWithValue(char * name);

        bool insertAtIndex(int i, TurtleNode * node);
        bool appendToTail(TurtleNode * node);
        bool prepend(TurtleNode * node);

};

bool TurtleList::deleteAtIndex(int i)
{
    bool success = false;
    TurtleNode * temp = head;
    if(temp != nullptr)         //We only do this if head != null
    {
        for(int j = 0; j<i; j++)    //Traverse through the list
        {
            if(temp->next == nullptr)   //Break if at the end
            {
                break;
            }
            if(j == i-1)    
            {            //deletion condition
                TurtleNode * john = temp->next;
                temp->next = john->next; // now i-1 is pointing to i+1
                delete john;
                success = true;
            }
            else
            {
                temp = temp->next;
            }
        }
    }
    return success;
}

bool TurtleList::prepend(TurtleNode * node)
{
    bool success = false;
    //make this node our head node;
    TurtleNode * temp = head;
    if(node != nullptr)
    {
        success = true;
        //updated our head node
        head = node;
        //Re-link the linked list
        head->next = temp;
        if(tail == nullptr)
        {
            tail = temp;
        }
    }
    return success;
}
/* 
*
*
*/
bool TurtleList::appendToTail(TurtleNode * node)
{
    bool success = false;
    TurtleNode * temp = tail;
    if(node != nullptr)
    {
        tail = node;
        if(temp != nullptr)
        {
            tail->next = nullptr;
            temp->next = tail;
        }
        else
        {
            head->next = tail;
        }
        success = true;
    }
    return success;
}

bool TurtleList::insertAtIndex(int i, TurtleNode * node)
{
    bool success = false;
    TurtleNode * temp = head;       //current
    if(node != nullptr)
    {
        for(int j = 0; j < i; j++)
        {
            if(temp->next == nullptr)
            {
                break;
            }
            if(j == i-1)
            {
                node->next = temp->next;
                temp->next = node;
                success = true;
            }
            else
            {
                temp = temp->next;
            }
        }
    }
    return success;
}


TurtleList::TurtleList() : head(nullptr), tail(nullptr) {}

TurtleList::TurtleList(TurtleNode * head, TurtleNode * tail)
: head(head), tail(tail) {
    this->head->next = this->tail;
    if(tail != nullptr)
    {
        this->tail->next = nullptr;
    }
}

TurtleList::~TurtleList()
{
    //We need to Delete
    // 1. all nodes
    // 2. all classes within the nodes
    TurtleNode * mrTemp = nullptr;      //current
    TurtleNode * mrsTemp;
    mrTemp = head;
    while(mrTemp != nullptr)
    {
        mrsTemp = mrTemp->next;   //next
        delete mrTemp->turtle;
        delete mrTemp;
        mrTemp = mrsTemp;
    }
}


int main()
{
    PaintedTurtle * yurtle = new PaintedTurtle("Orange", "Stripes", 2, "Square", 2, true);
    bool biter = yurtle->getDoesBite();
    SnappingTurtle * turyle = new SnappingTurtle("Happy", 2, "Round", 5, true);
    yurtle->displayFunFact();
    bool biter2 = turyle->getDoesBite();
    turyle->displayFunFact();
    TurtleList * listOfTurtles = new TurtleList();

    TurtleNode * yurtleNode = new TurtleNode;
    yurtleNode->turtle = yurtle;
    yurtleNode->next = nullptr;
    listOfTurtles->prepend(yurtleNode);

    TurtleNode * tim = new TurtleNode;
    tim->turtle = turyle; 
    tim->next = nullptr;
    listOfTurtles->appendToTail(tim);


}