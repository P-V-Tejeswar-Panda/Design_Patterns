/*
    Improvements over good
    We will be adding support for sizes like Large, Medium, Small
*/
#include <iostream>
#include <string>
using namespace std;

class Beverage{
    public: enum Size {LARGE, MEDIUM, SMALL};
    protected:
    string desc = "Unknown Beverage";
    Size size = LARGE;
    public:
    virtual float calculate() = 0;
    virtual string getDescription(){
        switch (this->size){
            case Size::LARGE:
                return this->desc + "(large)";
            case Size::MEDIUM:
                return this->desc + "(medium)";
            case Size::SMALL:
                return this->desc + "(small)";
        }
        return this->desc;
    }
    void setSize(Size sz){
        this->size = sz;
    }
    Size getSize(){
        return this->size;
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
    Cappuccino(Size sz){
        this->desc = "Cappuccino";
        this->setSize(sz);
    }
    float calculate(){
        return 23;
    }

};

class Latte: public Beverage{
    public:
    Latte(Size sz){
        this->desc = "Latte";
        this->setSize(sz);
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
        float baseBeverageCost = baseBeverage->calculate();
        switch(baseBeverage->getSize()){
            case Beverage::Size::LARGE:
                return baseBeverageCost + 20;
            case Beverage::Size::MEDIUM:
                return baseBeverageCost + 17;
            case Beverage::Size::SMALL:
                return baseBeverageCost + 10;
        }
        return baseBeverageCost;
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
        float baseBeverageCost = baseBeverage->calculate();
        switch(baseBeverage->getSize()){
            case Beverage::Size::LARGE:
                return baseBeverageCost + 30;
            case Beverage::Size::MEDIUM:
                return baseBeverageCost + 25;
            case Beverage::Size::SMALL:
                return baseBeverageCost + 20;
        }
        return baseBeverageCost;
    }

    string getDescription() override{
        return baseBeverage->getDescription() + ", Whipped Cream";
    }
};

int main(void){
    Beverage* order1 = new Cappuccino(Beverage::Size::MEDIUM);
    order1 = new SoyMilk(order1);
    order1 = new WhippedCream(order1);

    cout << "Order 1: " << order1->getDescription() << " Price: " << order1->calculate() << " rupees" << endl;

    Beverage* order2 = new WhippedCream(new SoyMilk(new Latte(Beverage::Size::SMALL)));

    cout << "Order 2: " << order2->getDescription() << " Price: " << order2->calculate() << " rupees" << endl;
}

/*
Order 1: Cappuccino(medium), Soy Milk, Whipped Cream Price: 70 rupees
Order 2: Latte(small), Soy Milk, Whipped Cream Price: 68 rupees
*/
