// test nlohmann::json serialization with inheritance.

#include "nlohmann/json.hpp"
#include <iostream>

namespace ns {
    using json = nlohmann::json;

    struct Base {
        int b{1};
    };

    struct Sub : public Base {
        int s{2};
    };

    void to_json(json& j, const Base& b) {
        j = json{{"b", b.b}};
    }
    void from_json(const json& j, Base& b) {
        j.at("b").get_to(b.b);
    }

    void to_json(json& j, const Sub& s) {
        to_json(j, (const Base&) s);
        std::cout << "Sub::to_json: " << j << std::endl;
        j["s"] = s.s;           // don't like
        //j = json{{"s", s.s}};
    }
    void from_json(const json& j, Sub& s) {
        from_json(j, (Base&) s);
        j.at("s").get_to(s.s);
    }
} // namespace ns

void test_one()
{
    using json = nlohmann::json;
    auto j = json{{"b",42},{"s",24}};
    std::cout << "in: " << j << std::endl;

    // test round trip via subclass
    {
        auto s = j.get<ns::Sub>();
        assert (s.s == 24);
        assert (s.b == 42);
        json j2 = s;
        assert (j == j2);
    }

    // test slicing
    {
        auto b = j.get<ns::Base>();
        assert (b.b == 42);
        json j2 = b;
        assert (j != j2);
        assert (j["b"] == j2["b"]);
        assert (j2["a"].is_null());
    }

}

int main()
{
    test_one();
}
