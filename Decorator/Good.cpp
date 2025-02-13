#include <iostream>
#include <string>
using namespace std;

class Beverage{
    protected:
    string desc = "Unknown Beverage";
    public:
    virtual float calculate() = 0;
    virtual string getDescription(){
        return desc;
    }
};

class Condiment: public Beverage{
    protected:
    Beverage* baseBeverage;
    public:
    virtual string getDescription() = 0;
};

class Cappuccino: public Beverage{
    public:
    Cappuccino(){
        this->desc = "Cappuccino";
    }
    float calculate(){
        return 23;
    }
};

class Latte: public Beverage{
    public:
    Latte(){
        this->desc = "Latte";
    }
    float calculate(){
        return 28;
    }
};

class SoyMilk: public Condiment{
    public:
    SoyMilk(Beverage* bv){
        this->baseBeverage = bv;
    }

    float calculate(){
        return baseBeverage->calculate()+20;
    }

    string getDescription() override{
        return baseBeverage->getDescription() + ", Soy Milk";
    }
};

class WhippedCream: public Condiment{
    public:
    WhippedCream(Beverage* bv){
        this->baseBeverage = bv;
    }

    float calculate(){
        return baseBeverage->calculate()+30;
    }

    string getDescription() override{
        return baseBeverage->getDescription() + ", Whipped Cream";
    }
};

int main(void){
    Beverage* order1 = new Cappuccino();
    order1 = new SoyMilk(order1);
    order1 = new WhippedCream(order1);

    cout << "Order 1: " << order1->getDescription() << " Price: " << order1->calculate() << " rupees" << endl;

    Beverage* order2 = new WhippedCream(new SoyMilk(new Latte()));

    cout << "Order 2: " << order2->getDescription() << " Price: " << order2->calculate() << " rupees" << endl;
}

/*
Order 1: Cappuccino, Soy Milk, Whipped Cream Price: 73 rupees
Order 2: Latte, Soy Milk, Whipped Cream Price: 78 rupees
*/
