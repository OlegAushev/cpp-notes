#include <ios>
#include <iostream>
#include <string>

class House {
public:
    void show() const {
        std::cout << "House details: \n"
                  << "1. Material:      " << material_
                  << "2. Room Count:    " << room_count_ << std::boolalpha
                  << "3. Garage:        " << has_garage_
                  << "4. Swimming Pool: " << has_swimpool_ << std::noboolalpha;
    }
private:
    std::string material_;
    int room_count_{0};
    bool has_garage_{false};
    bool has_swimpool_{false};
};

class HouseBuilder {
public:
    virtual ~HouseBuilder() = default;
};
// class HouseBuilder {
// public:
//     virtual ~HouseBuilder() = default;

//     virtual void buildFoundation() { house->setFoundation("Default Foundation"); }
//     virtual void buildStructure() { house->setStructure("Default Structure"); }
//     virtual void buildRoof() { house->setRoof("Default Roof"); }
//     virtual void buildInterior() { house->setInterior("Default Interior"); }

//     virtual House* getHouse() { return house; }

// protected:
//     House* house = new House();
// };
// Step 3: Implement the LuxuryHouseBuilder and StandardHouseBuilder Classes
// These classes will override the default methods of HouseBuilder to build specific types of houses.

// C++
// class LuxuryHouseBuilder : public HouseBuilder {
// public:
//     void buildFoundation() override { house->setFoundation("Luxury Foundation"); }
//     void buildStructure() override { house->setStructure("Luxury Structure"); }
//     void buildRoof() override { house->setRoof("Luxury Roof"); }
//     void buildInterior() override { house->setInterior("Luxury Interior"); }
// };

// class StandardHouseBuilder : public HouseBuilder {
// public:
//     void buildFoundation() override { house->setFoundation("Standard Foundation"); }
//     void buildStructure() override { house->setStructure("Standard Structure"); }
//     void buildRoof() override { house->setRoof("Standard Roof"); }
//     void buildInterior() override { house->setInterior("Standard Interior"); }
// };
// Step 4: Define the HouseDirector Class
// The HouseDirector class will construct the House using a HouseBuilder.

// C++
// class HouseDirector {
// public:
//     void setBuilder(HouseBuilder* builder) { this->builder = builder; }

//     House* buildHouse() {
//         builder->buildFoundation();
//         builder->buildStructure();
//         builder->buildRoof();
//         builder->buildInterior();
//         return builder->getHouse();
//     }

// private:
//     HouseBuilder* builder;
// };
// Step 5: Demonstrate the Builder Pattern
// Here's how you can use the HouseDirector class to build different types of houses.

// C++
// int main() {
//     HouseDirector director;

//     LuxuryHouseBuilder luxuryBuilder;
//     StandardHouseBuilder standardBuilder;

//     director.setBuilder(&luxuryBuilder);
//     House* luxuryHouse = director.buildHouse();
//     luxuryHouse->showHouse();

//     std::cout << "\n";

//     director.setBuilder(&standardBuilder);
//     House* standardHouse = director.buildHouse();
//     standardHouse->showHouse();

//     delete luxuryHouse;
//     delete standardHouse;

//     return 0;
// }
