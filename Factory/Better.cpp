/*
Here we will solve the level 2 of the problem.
*/
#include <iostream>
#include <string>
using namespace std;

/*--------------------- Interfaces ---------------------*/
/*----------- Salvaged from good.cpp START -------------*/
class Pizza{
    protected:
    string pizzaName = "Default Pizza Name";
    public:
    virtual void makePizza() = 0;
    virtual void cut(){
        cout << "Cutting the " << this->getName() << " pizza" << endl;
    }
    virtual void box(){
        cout << "Boxing the " << this->getName() << " pizza" << endl;
    }
    virtual string getName(){
        return pizzaName;
    }
};

class Topping: public Pizza{
    protected:
    Pizza* pizza;
    string toppingName;
    public:
    virtual string getName() = 0; // Notice that in the base interface this has an implementation
                                  // Here we have made it pure virtual.
                                  // We could have implemented this here but I wanted to show that
                                  // this is also possible.
};
/*----------- Salvaged from good.cpp END --------------*/
/*------------------ NEW Additions  -------------------*/
class PizzaStore{
    public:
    virtual Pizza* makePizza(string pizzaName, string topping) = 0;
    void orderPizza(string pizzaName, string topping = ""){
        Pizza* pz = makePizza(pizzaName, topping);
        if(pz){
            pz->cut();
            pz->box();
        }
    }
};
/*------------------ NEW Additions END ----------------*/
/*------------------ Interfaces END -------------------*/
class BLRMargerita: public Pizza{
    public:
    BLRMargerita(){
        this->pizzaName = "Banglore Margerita";
    }
    void makePizza() override {
        cout << "Making Margerita Pizza Banglore Style! ...\n"
             << "Making the base. "
             << "Adding Pizza sauce. "
             << "Adding lots of Mozzrella and Chedder Cheese. "
             << "Baking the pizza at 350 degrees." << endl;
    }
};

class BLRPeppyPaneer: public Pizza{
    public:
    BLRPeppyPaneer(){
        this->pizzaName = "Banglore Peppy Paneer";
    }
    void makePizza() override {
        cout << "Making Peppy Paneer Pizza for the Bangalorians ...\n"
             << "Making the base. "
             << "Adding Italian sauce. "
             << "Adding lots of Panner and Mozerella Cheese. "
             << "Adding baked red Peprika. "
             << "Baking the pizza at 400 degrees." << endl;
    }
};

class BLRFarmHouse: public Pizza{
    public:
    BLRFarmHouse(){
        this->pizzaName = "Banglore Farm House";
    }
    void makePizza() override {
        cout << "Making the Famous BLR farmhouse pizza ...\n"
             << "Making the base. "
             << "Adding Pizza sauce. "
             << "Adding lots of Vegetables, Mushrooms, Olives and Chedder Cheese. "
             << "Baking the pizza at 300 degrees." << endl;
    }
};


/*------------------------ DEL Style ----------------------*/
class DELMargerita: public Pizza{
    public:
    DELMargerita(){
        this->pizzaName = "Delhi Margerita";
    }
    void makePizza() override {
        cout << "Making Delhi style Margerita Pizza ...\n"
             << "Making the base. "
             << "Adding Pizza sauce. "
             << "Adding lots of Mozzrella and Chedder Cheese. "
             << "Baking the pizza at 350 degrees." << endl;
    }
};

class DELPeppyPaneer: public Pizza{
    public:
    DELPeppyPaneer(){
        this->pizzaName = "Delhi Peppy Paneer";
    }
    void makePizza() override {
        cout << "Making Peppy Paneer Pizza Delhi Style! ...\n"
             << "Making the base. "
             << "Adding Salsa sauce. "
             << "Adding lots of Malai Panner and Regato Cheese. "
             << "Baking the pizza at 400 degrees." << endl;
    }
};

class DELFarmHouse: public Pizza{
    public:
    DELFarmHouse(){
        this->pizzaName = "Delhi Farm House";
    }
    void makePizza() override {
        cout << "Making the farmhouse pizza in a classic Delhi Style ...\n"
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
        cout << "[Topping!] Adding extra Liquid cheese on top!" << endl;
    }

    // notice that methods that are implemented in the base pizza class call this
    // This is new for me.
    virtual string getName() override{
        return pizza->getName();
    }
};

/*----------------Concrete PizzaStores ----------------*/
class BLRPizzaStore: public PizzaStore{
    Pizza* makePizza(string pizzaName, string topping){
        Pizza* pz = NULL;
        if(pizzaName == "Margerita"){
            pz = new BLRMargerita();
        }
        else if (pizzaName == "PeppyPaneer"){
            pz = new BLRPeppyPaneer();
        }
        else if (pizzaName == "FarmHouse"){
            pz = new BLRFarmHouse();
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
class DELPizzaStore: public PizzaStore{
    Pizza* makePizza(string pizzaName, string topping){
        Pizza* pz = NULL;
        if(pizzaName == "Margerita"){
            pz = new DELMargerita();
        }
        else if (pizzaName == "PeppyPaneer"){
            pz = new DELPeppyPaneer();
        }
        else if (pizzaName == "FarmHouse"){
            pz = new DELFarmHouse();
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
/*----------------Concrete PizzaStores END ------------*/

int main(void){
    PizzaStore* ps = new BLRPizzaStore();
    ps->orderPizza("PeppyPaneer", "ExtraCheese");
    cout << endl;
    ps = new DELPizzaStore();
    ps->orderPizza("PeppyPaneer");
}

/*
Making Peppy Paneer Pizza for the Bangalorians ...
Making the base. Adding Italian sauce. Adding lots of Panner and Mozerella Cheese. Adding baked red Peprika. Baking the pizza at 400 degrees.
[Topping!] Adding extra Liquid cheese on top!
Cutting the Banglore Peppy Paneer pizza
Boxing the Banglore Peppy Paneer pizza

Making Peppy Paneer Pizza Delhi Style! ...
Making the base. Adding Salsa sauce. Adding lots of Malai Panner and Regato Cheese. Baking the pizza at 400 degrees.
Cutting the Delhi Peppy Paneer pizza
Boxing the Delhi Peppy Paneer pizza
*/