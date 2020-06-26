#ifndef DEMOCFG_HEAD_NLJS_HPP
#define DEMOCFG_HEAD_NLJS_HPP


#include "nlohmann/json.hpp"
#include "head_avro.hpp"

namespace democfg {

    using json = nlohmann::json;


    // Converters for ConfigHeader
    // 
    inline void to_json(json& j, const ConfigHeader& obj) {
        j = json{
            {"impname", obj.impname},
            {"instname", obj.instname}
        };
    }
    inline void from_json(const json& j, ConfigHeader& obj) {
        j.at("impname").get_to(obj.impname);    
        j.at("instname").get_to(obj.instname);    
    }


} // namespace democfg

#endif