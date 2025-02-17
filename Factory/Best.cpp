/*
Here we solve Level - III
We want to enforce quality control by creating our own set of ingredients

We will use Abstract Factory
*/
#include <iostream>
#include <string>
using namespace std;

/*--------------------- Interfaces ---------------------*/
/*------------------ NEW Additions  -------------------*/
class Ingredient{
    public:
    virtual string getIngredient() = 0;     // Factory Method
};
class IngredientFactory{                    // Abstract Factory
    public:
    virtual Ingredient* getBase() = 0;
    virtual Ingredient* getSauce() = 0;
    virtual Ingredient* getCheese() = 0;
};
/*------------------ NEW Additions END ----------------*/
/*----------- Salvaged from good.cpp START -------------*/
class Pizza{
    protected:
    string pizzaName = "Default Pizza Name";
    IngredientFactory* inf;
    public:
    virtual void makePizza() = 0;           // Factory Method
    virtual void cut(){
        cout << "Cutting the " << this->getName() << " pizza" << endl;
    }
    virtual void box(){
        cout << "Boxing the " << this->getName() << " pizza" << endl;
    }
    virtual void addBase(){
        cout << "Making the " << inf->getBase()->getIngredient() << endl;
    }
    virtual void addSauce(){
        cout << "Spreading the " << inf->getSauce()->getIngredient() << endl;
    }
        virtual void addCheese(){
        cout << "Adding lots of " << inf->getCheese()->getIngredient() << endl;
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
/*----------- Salvaged from good.cpp END --------------*/
/*------------------ Interfaces END -------------------*/
/*-------------------- New Classes  -------------------*/
class BLRBase: public Ingredient{
    public:
    virtual string getIngredient() override{
        return "Banglore style thin Pizza Base made from Sourdough";
    }
};
class BLRSauce: public Ingredient{
    public:
    virtual string getIngredient() override{
        return "Banglore style Pizza Sauce made from Natti Tomatos";
    }
};
class BLRCheese: public Ingredient{
    public:
    virtual string getIngredient() override{
        return "Banglore style Pizza Cheese made from Mozella and Chedder.";
    }
};
class DELBase: public Ingredient{
    public:
    virtual string getIngredient() override{
        return "Delhi style thick Pizza Base made from fresh dough";
    }
};
class DELSauce: public Ingredient{
    public:
    virtual string getIngredient() override{
        return "Delhi style Pizza Sauce made from Desi Tomatos and Tobasco";
    }
};
class DELCheese: public Ingredient{
    public:
    virtual string getIngredient() override{
        return "Delhi style Pizza Cheese made from Reggano and Chedder.";
    }
};

class BLRIngredientFactory: public IngredientFactory{
    public:
    Ingredient* getBase() override{
        return new BLRBase();
    }
    Ingredient* getSauce() override{
        return new BLRSauce();
    }
    Ingredient* getCheese() override{
        return new BLRCheese();
    }
};
class DELIngredientFactory: public IngredientFactory{
    public:
    Ingredient* getBase() override{
        return new DELBase();
    }
    Ingredient* getSauce() override{
        return new DELSauce();
    }
    Ingredient* getCheese() override{
        return new DELCheese();
    }
};
/*-------------------- New Classes END ----------------*/
class BLRMargerita: public Pizza{
    public:
    BLRMargerita(IngredientFactory* inf){
        this->pizzaName = "Banglore Margerita";
        this->inf = inf;
    }
    void makePizza() override {
        cout << "Making Margerita Pizza Banglore Style! ..." << endl;
        addBase(); addSauce(); addCheese();
        cout << "Baking the pizza at 350 degrees." << endl;
    }
};

class BLRPeppyPaneer: public Pizza{
    public:
    BLRPeppyPaneer(IngredientFactory* inf){
        this->pizzaName = "Banglore Peppy Paneer";
        this->inf = inf;
    }
    void makePizza() override {
        cout << "Making Peppy Paneer Pizza for the Bangalorians ..." << endl;
        addBase(); addSauce();
        cout << "Adding lots of Paneer " << endl;
        cout << "Adding baked red Peprika. " << endl;
        addCheese();
        cout << "Baking the pizza at 400 degrees." << endl;
    }
};

class BLRFarmHouse: public Pizza{
    public:
    BLRFarmHouse(IngredientFactory* inf){
        this->pizzaName = "Banglore Farm House";
        this->inf = inf;
    }
    void makePizza() override {
        cout << "Making the Famous BLR farmhouse pizza ..." << endl;
        addBase(); addSauce(); addCheese();
        cout << "Adding lots of Vegetables, Mushrooms & Olives"
             << "Baking the pizza at 300 degrees." << endl;
    }
};


/*------------------------ DEL Style ----------------------*/
class DELMargerita: public Pizza{
    public:
    DELMargerita(IngredientFactory* inf){
        this->pizzaName = "Delhi Margerita";
        this->inf = inf;
    }
    void makePizza() override {
        cout << "Making Delhi style Margerita Pizza ...\n";
        addBase(); addSauce(); addCheese();
        cout << "Baking the pizza at 350 degrees." << endl;
    }
};

class DELPeppyPaneer: public Pizza{
    public:
    DELPeppyPaneer(IngredientFactory* inf){
        this->pizzaName = "Delhi Peppy Paneer";
        this->inf = inf;
    }
    void makePizza() override {
        cout << "Making Peppy Paneer Pizza Delhi Style! ...\n";
        addBase(); addSauce(); addCheese();
        cout << "Adding lots of Malai Panner."
             << "Baking the pizza at 400 degrees." << endl;
    }
};

class DELFarmHouse: public Pizza{
    public:
    DELFarmHouse(IngredientFactory* inf){
        this->pizzaName = "Delhi Farm House";
        this->inf = inf;
    }
    void makePizza() override {
        cout << "Making the farmhouse pizza in a classic Delhi Style ...\n";
        addBase(); addSauce(); addCheese();
        cout << "Adding lots of Vegetables, Mushrooms & Olives. "
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
            pz = new BLRMargerita(new BLRIngredientFactory());
        }
        else if (pizzaName == "PeppyPaneer"){
            pz = new BLRPeppyPaneer(new BLRIngredientFactory());
        }
        else if (pizzaName == "FarmHouse"){
            pz = new BLRFarmHouse(new BLRIngredientFactory());
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
            pz = new DELMargerita(new DELIngredientFactory());
        }
        else if (pizzaName == "PeppyPaneer"){
            pz = new DELPeppyPaneer(new DELIngredientFactory());
        }
        else if (pizzaName == "FarmHouse"){
            pz = new DELFarmHouse(new DELIngredientFactory());
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
Making the Banglore style thin Pizza Base made from Sourdough
Spreading the Banglore style Pizza Sauce made from Natti Tomatos
Adding lots of Paneer 
Adding baked red Peprika. 
Adding lots of Banglore style Pizza Cheese made from Mozella and Chedder.
Baking the pizza at 400 degrees.
[Topping!] Adding extra Liquid cheese on top!
Cutting the Banglore Peppy Paneer pizza
Boxing the Banglore Peppy Paneer pizza

Making Peppy Paneer Pizza Delhi Style! ...
Making the Delhi style thick Pizza Base made from fresh dough
Spreading the Delhi style Pizza Sauce made from Desi Tomatos and Tobasco
Adding lots of Delhi style Pizza Cheese made from Reggano and Chedder.
Adding lots of Malai Panner.Baking the pizza at 400 degrees.
Cutting the Delhi Peppy Paneer pizza
Boxing the Delhi Peppy Paneer pizza
*/