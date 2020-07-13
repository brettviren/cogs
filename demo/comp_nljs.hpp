#ifndef DEMOCFG_COMP_NLJS_HPP
#define DEMOCFG_COMP_NLJS_HPP


#include "nlohmann/json.hpp"
#include "comp_structs.hpp"

namespace democfg {

    using json = nlohmann::json;


    // Converters for Source
    // A config for a source component
    inline void to_json(json& j, const Source& obj) {
        j["ntosend"] = obj.ntosend;
    }
    inline void from_json(const json& j, Source& obj) {
        j.at("ntosend").get_to(obj.ntosend);    
    }
    // Converters for MySource
    // 
    inline void to_json(json& j, const MySource& obj) {
        to_json(j, (const Source&)obj);
        j["myparam"] = obj.myparam;
    }
    inline void from_json(const json& j, MySource& obj) {
        from_json(j, (Source&)obj);
        j.at("myparam").get_to(obj.myparam);    
    }


} // namespace democfg

#endif