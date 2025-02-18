## Example problem solved using factory pattern
### Level - 1
Our client has opened a pizza store that makes pizza, cuts and boxes it.
There are 3 kinds of pizzas: Margerita, Peppy Paneer, Farmhouse
#### Objectives:
Our Client should be able to add or remove pizza easily without modifying too much.
Our Customer should be able to do a little customization like adding topings, making cheeseburst, etc.
#### Solved in: Bad.cpp, Good.cpp

#### Class Diagram
```mermaid
classDiagram
    class Pizza{
        # pizzaName: string
        + virtual makePizza() void
    }
    <<Interface>> Pizza
    class Topping{
        # *basePizza: Pizza
        # toppingName: string
    }
    <<Interface>> Topping

    class SimplePizzaFactory{
        +makePizza()  void
    }

    class PizzaStore{
        +makePizza()  void
        +orderPizza() void
    }

    Pizza <|.. Margerita
    Pizza <|.. PeppyPaneer
    Pizza <|.. FarmHouse

    Topping <|.. ExtraCheese

    Pizza <|-- Topping

    SimplePizzaFactory ..> Pizza
    SimplePizzaFactory ..> Topping

    PizzaStore ..> SimplePizzaFactory
```

### Level - 2
PizzaStore has become very famous and has a franchise mode:
Now it has outlet in Banglore, Delhi, etc.
#### Objectives:
Same as level 1
Aditionaly, It should be easy to scale, and each franchise can have their own customizations keeping the overall procedure the same.
Ex, Banglore style pizza have a thin crust , while Delhi style have a thick crust
#### Solved in: Better.cpp

#### Class Diagram
```mermaid
classDiagram
    class Pizza{
        # pizzaName: string
        + virtual makePizza() void
    }
    <<Interface>> Pizza
    class Topping{
        # *basePizza: Pizza
        # toppingName: string
    }
    <<Interface>> Topping

    class PizzaStore{
        + virtual makePizza() void
    }
    <<Abstract>> PizzaStore

    class BLRPizzaStore{
        +makePizza() void
    }
    class DELPizzaStore{
        +makePizza() void
    }

    Pizza <|.. DELMargerita
    Pizza <|.. DELPeppyPaneer
    Pizza <|.. DELFarmHouse

    Pizza <|.. BLRMargerita
    Pizza <|.. BLRPeppyPaneer
    Pizza <|.. BLRFarmHouse

    PizzaStore <|.. BLRPizzaStore
    PizzaStore <|.. DELPizzaStore

    PizzaStore ..> Pizza
    Topping <|.. ExtraCheese

    Pizza <|-- Topping
```

### Level - 3
We want more quality control, We have seen while Franchises are trying to introduce new flavours they are cutting cost and not using quality ingredients. So, We will ship them whatever variations they want of their pizza ingredients but no third pary products!

#### Objectives
Same as level two.
#### Solved in Best.cpp
#### Class Diagram
```mermaid
classDiagram
    class Pizza{
        # pizzaName: string
        + virtual makePizza() void
    }
    <<Interface>> Pizza
    class Topping{
        # *basePizza: Pizza
        # toppingName: string
    }
    <<Interface>> Topping

    class PizzaStore{
        + PizzaStore(IngredientFactory* inf)
        + virtual makePizza() void
    }
    <<Abstract>> PizzaStore

    class Ingredient{
        + virtual getDescription(): string
    }
    <<Abstract>> Ingredient

    class IngredientFactory{
        +virtual getBase(): *Ingredient
        +virtual getSauce(): *Ingredient
        +virtual getCheese(): *Ingredient
    }
    <<Abstract>> IngredientFactory

    class BLRIngredientFactory{
        +getBase(): *Ingredient
        +getSauce(): *Ingredient
        +getCheese(): *Ingredient
    }
    class DELIngredientFactory{
        +getBase(): *Ingredient
        +getSauce(): *Ingredient
        +getCheese(): *Ingredient
    }
    class BLRPizzaStore{
        +makePizza() void
    }
    class DELPizzaStore{
        +makePizza() void
    }

    Ingredient <|.. BLRPizzaBase
    Ingredient <|.. BLRPizzaSauce
    Ingredient <|.. BLRPizzaCheese

    Ingredient <|.. DELPizzaBase
    Ingredient <|.. DELPizzaSauce
    Ingredient <|.. DELPizzaCheese

    IngredientFactory <|.. BLRIngredientFactory
    IngredientFactory <|.. DELIngredientFactory

    Pizza <|.. DELMargerita
    Pizza <|.. DELPeppyPaneer
    Pizza <|.. DELFarmHouse

    Pizza <|.. BLRMargerita
    Pizza <|.. BLRPeppyPaneer
    Pizza <|.. BLRFarmHouse

    PizzaStore <|.. BLRPizzaStore
    PizzaStore <|.. DELPizzaStore

    PizzaStore ..> Pizza
    PizzaStore ..> IngredientFactory
    Pizza ..> IngredientFactory
    IngredientFactory ..> Ingredient

    Topping <|.. ExtraCheese

    Pizza <|-- Topping
```