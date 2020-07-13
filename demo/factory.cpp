#include "factory.hpp"
#include "cogs/issues.hpp"

#include <map>

ERS_DECLARE_ISSUE(demo, unknown_implementation,
                  "unknown implementation: " << impname,
                  ((std::string)impname))

using factory_maker_t = std::map<std::string, demo::maker_f>;
factory_maker_t& maker_repo() {
    static factory_maker_t* m{nullptr};
    if (!m) { m = new factory_maker_t; }
    return *m;
}


std::string demo::factory_register_base(std::string imp_name, maker_f maker)
{
    auto& mr = maker_repo();
    mr[imp_name] = maker;
    return imp_name;
}

cogs::Configurable* demo::configurable(std::string imp_name, std::string inst_name)
{
    auto& mr = maker_repo();
    if (mr.find(imp_name) == mr.end()) {
        throw demo::unknown_implementation(ERS_HERE, imp_name);
    }

    static std::map<std::string, cogs::Configurable*> made;
    auto ret = made[inst_name];
    if (ret) { return ret; }

    made[inst_name] = mr[imp_name]();

    return made[inst_name];
}

demo::PortuserBase* demo::portuser(std::string imp_name, std::string inst_name)
{
    /// SHIELD THY EYES! this is NOT the way to do polymorphic factory
    auto c = demo::configurable(imp_name, inst_name);
    return dynamic_cast<demo::PortuserBase*>(c);
}
