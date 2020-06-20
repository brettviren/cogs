/** A cogs configurable provides an abstract interface to receive cogs
 * objects. */

#ifndef COGS_CONFIGURABLE_HPP_SEEN
#define COGS_CONFIGURABLE_HPP_SEEN

#include "cogs/object.hpp"

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
            // fixme: here we will instrument some ESR forwarding of failures.
            configure(obj.get<CfgObj>());
        }

    };

}

#endif
