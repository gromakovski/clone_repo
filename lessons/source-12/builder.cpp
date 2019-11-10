// Строитель (Builder)

#include <string>

#pragma region (Pizza)
class Pizza {
public:
    Pizza(const std::string& dough,
        const std::string& sauce,
        const std::string& topping)
            : m_dough(dough)
            , m_sauce(sauce)
            , m_topping(topping) {
        
    }

    Pizza(const std::string& dough,
        const std::string& sauce,
        const std::string& topping,
        const std::string& additional)
            : m_dough(dough)
            , m_sauce(sauce)
            , m_topping(topping)
            , m_additional(additional) {
        
    }  

private:
    std::string m_dough;
    std::string m_sauce;
    std::string m_topping;
    std::string m_additional = "None";
};


void testPizza() {
    Pizza pizza1(
        "wheat",
        "mild",
        "pepperoni and salami"
    );
    Pizza pizza2(
        "wheat",
        "mild",
        "pepperoni and salami",
        "olives"
    );
}
#pragma endregion


#pragma region (PizzaWithSetters)
class PizzaWithSetters {
public:
    void setDough(const std::string& dough) {
        m_dough = dough;
    }

    void setSauce(const std::string& sauce) {
        m_sauce = sauce;
    }

    void setTopping(const std::string& topping) {
        m_topping = topping;
    }

    void setAdditional(const std::string& additional) {
        m_additional = additional;
    }

private:
    std::string m_dough;
    std::string m_sauce;
    std::string m_topping;
    std::string m_additional = "None";
};

void testPizzaWithSetters() {
    PizzaWithSetters pizza;
    pizza.setDough("wheat");
    pizza.setSauce("mild");
    pizza.setTopping("pepperoni and salami");
    pizza.setAdditional("olives");

    // Work with pizza.
}
#pragma endregion


#pragma region (Builder)
class PizzaBuilder {
public:
    PizzaBuilder() = default;
    ~PizzaBuilder() = default;

    PizzaBuilder& withDough(const std::string& dough) {
        m_dough = dough;
        return *this;
    }

    PizzaBuilder& withSauce(const std::string& sauce) {
        m_sauce = sauce;
        return *this;
    }

    PizzaBuilder& withTopping(const std::string& topping) {
        m_topping = topping;
        return *this;
    }

    PizzaBuilder& withAdditional(const std::string& additional) {
        m_additional = additional;
        return *this;
    }

    Pizza build() {
        return Pizza{
            m_dough,
            m_sauce,
            m_topping,
            m_additional
        };
    }

private:
    std::string m_dough = "wheat";
    std::string m_sauce = "mild";
    std::string m_topping = "pepperoni";
    std::string m_additional = "None";

};


void testBuilder() {
    PizzaBuilder builder;
    
    auto pizza = builder.withDough("rye")
        .withSauce("spicy")
        .build();
}

#pragma endregion



int main() {

    testBuilder();

    return 0;
}