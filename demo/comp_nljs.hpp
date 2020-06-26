#ifndef DEMOCFG_COMP_NLJS_HPP
#define DEMOCFG_COMP_NLJS_HPP


#include "nlohmann/json.hpp"
#include "comp_avro.hpp"

namespace democfg {

    using json = nlohmann::json;


    // Converters for Source
    // A config for a source component
    inline void to_json(json& j, const Source& obj) {
        j = json{
            {"ntosend", obj.ntosend}
        };
    }
    inline void from_json(const json& j, Source& obj) {
        j.at("ntosend").get_to(obj.ntosend);    
    }


} // namespace democfg

#endif