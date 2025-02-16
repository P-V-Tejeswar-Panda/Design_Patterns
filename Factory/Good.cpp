/*
This class has the logic of choosing the pizza type in PizzaStore::makePizza method
This is not very flexible. This class will likely have lots of other functionality
And its not a good Idea to change this class too often.

Will solve this problem using Simple Factory in Good.cpp
*/
#include <iostream>
#include <string>
using namespace std;

class Pizza{
    protected:
    string pizzaName = "Default Pizza Name";
    public:
    virtual void makePizza() = 0;
    virtual void cut(){
        cout << "Cutting the " << this->pizzaName << " pizza" << endl;
    }
    virtual void box(){
        cout << "Boxing the " << this->pizzaName << " pizza" << endl;
    }
};

class Topping: public Pizza{
    protected:
    Pizza* pizza;
    string toppingName;
};

class Margerita: public Pizza{
    public:
    Margerita(){
        this->pizzaName = "Margerita";
    }
    void makePizza() override {
        cout << "Making Margerita Pizza ...\n"
             << "Making the base. "
             << "Adding Pizza sauce. "
             << "Adding lots of Mozzrella and Chedder Cheese. "
             << "Baking the pizza at 350 degrees." << endl;
    }
};

class PeppyPaneer: public Pizza{
    public:
    PeppyPaneer(){
        this->pizzaName = "Peppy Paneer";
    }
    void makePizza() override {
        cout << "Making Peppy Paneer Pizza ...\n"
             << "Making the base. "
             << "Adding Pizza sauce. "
             << "Adding lots of Panner and Chedder Cheese. "
             << "Baking the pizza at 400 degrees." << endl;
    }
};

class FarmHouse: public Pizza{
    public:
    FarmHouse(){
        this->pizzaName = "Farm House";
    }
    void makePizza() override {
        cout << "Making the farmhouse pizza ...\n"
             << "Making the base. "
             << "Adding Pizza sauce. "
             << "Adding lots of Vegetables, Mushrooms, Olives and Chedder Cheese. "
             << "Baking the pizza at 300 degrees." << endl;
    }
};

class ExtraCheese: public Topping{
    public:
    ExtraCheese(Pizza* pz){
        this->pizza = pz;
        this->toppingName = "ExtraCheese";
    }

    void makePizza() override {
        this->pizza->makePizza();
        cout << "Adding extra Liquid cheese on top!" << endl;
    }
};

/*===============New Simple Factory ====================*/

/*
By taking out the pizza choosing logic outside of the PizzaStore,
We have isolated the change.
*/

class SimplePizzaFactory{
    public:
    Pizza *makePizza(string pizzaName, string topping){
        Pizza* pz = NULL;
        if(pizzaName == "Margerita"){
            pz = new Margerita();
        }
        else if (pizzaName == "PeppyPaneer"){
            pz = new PeppyPaneer();
        }
        else if (pizzaName == "FarmHouse"){
            pz = new FarmHouse();
        }
        else{
            cout << "Unknown Pizza!" << endl;
        }
        if (topping != ""){
            if(topping == "ExtraCheese"){
                pz = new ExtraCheese(pz);
            }
            else{
                cout << "Unknown Topping!" << endl;
            }
        }
        pz->makePizza();
        return pz;
    }
};

class PizzaStore{

    public:
    void orderPizza(string pizzaName, string topping = ""){
        SimplePizzaFactory* sp = new SimplePizzaFactory();
        Pizza* pz = sp->makePizza(pizzaName, topping);
        if(pz){
            pz->cut();
            pz->box();
        }
    }
};

int main(void){
    PizzaStore* ps = new PizzaStore();
    ps->orderPizza("Margerita");
    ps->orderPizza("FarmHouse", "ExtraCheese");
}

/*
Making Margerita Pizza ...
Making the base. Adding Pizza sauce. Adding lots of Mozzrella and Chedder Cheese. Baking the pizza at 350 degrees.
Cutting the Margerita pizza
Boxing the Margerita pizza
Making the farmhouse pizza ...
Making the base. Adding Pizza sauce. Adding lots of Vegetables, Mushrooms, Olives and Chedder Cheese. Baking the pizza at 300 degrees.
Adding extra Liquid cheese on top!
Cutting the Default Pizza Name pizza
Boxing the Default Pizza Name pizza
*/