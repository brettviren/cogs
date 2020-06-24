/** This is a really dumb factory.
 *
 * Any configurable class should register with:
 *
 * DEMO_REGISTER_COMPONENT("myname", myns::MyConfigurableType);
 */

#ifndef COGS_DEMO_FACTORY_HPP
#define COGS_DEMO_FACTORY_HPP

#include "ports.hpp"
#include "cogs/configurable.hpp"

#include <functional>

namespace demo {

    // The factory method: 
    cogs::ConfigurableBase* configurable(std::string imp_name, std::string inst_name);
    demo::PortuserBase* portuser(std::string imp_name, std::string inst_name);


    // Ignore the rest of this junk.
    using maker_f = std::function<cogs::ConfigurableBase*()>;
    std::string factory_register_base(std::string imp_name, maker_f maker);
    template<typename TYPE>
    std::string factory_register(std::string imp_name) {
        return factory_register_base(imp_name, []{ return new TYPE; });
    }

}

#define DEMO_REGISTER_COMPONENT(IMP_NAME, TYPE) \
    static std::string dummy = demo::factory_register<TYPE>(IMP_NAME)

#endif
