/** A cogs configurable provides an abstract interface to receive cogs
 * objects. */

#ifndef COGS_CONFIGURABLE_HPP_SEEN
#define COGS_CONFIGURABLE_HPP_SEEN

#include "cogs/object.hpp"
#include "cogs/issues.hpp"

namespace cogs {

    // Retype a dynamic configuration object to a static CfgObj struct
    // or throw cogs::schema_error.
    template<typename CfgObj>
    auto cfgobj(object obj) {
        try {
            return obj.get<CfgObj>();
        }
        catch (const cogs::object::type_error& pe) {
            // fixme: how do I chain exceptins?
            ERS_INFO("bad object: " << obj);
            throw cogs::schema_error(ERS_HERE, pe.what());
        }
    }

    // Implement to be able to receive an generically typed object.
    // Most client code should inherit from Configurable<> below.
    struct Configurable {
        virtual void configure(object obj) = 0;
    };


}

#endif
