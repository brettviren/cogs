/** A cogs configurable provides an abstract interface to receive cogs
 * objects. */

#ifndef COGS_CONFIGURABLE_HPP_SEEN
#define COGS_CONFIGURABLE_HPP_SEEN

#include "cogs/object.hpp"
#include "cogs/issues.hpp"

namespace cogs {

    // Implement to be able to receive an generically typed object.
    // Most client code should inherit from Configurable<> below.
    struct ConfigurableBase {
        virtual void configure(object obj) = 0;
    };

    // Implement to have any retyping errors handled automatically.
    // Most client code should inherit from this instad of the base.
    template<class CfgObj>
    struct Configurable : virtual public ConfigurableBase {

        virtual void configure(CfgObj&& cfgobj) = 0;

        void configure(object obj) {
            CfgObj co;
            try {
                co = obj.get<CfgObj>();
            }
            catch (const cogs::object::type_error& pe) {
                // fixme: how do I chain exceptins?
                ERS_INFO("bad object: " << obj);
                throw cogs::schema_error(ERS_HERE, pe.what());
            }

            configure(std::move(co));
        }

    };

}

#endif
