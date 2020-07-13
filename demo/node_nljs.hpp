#ifndef DEMOCFG_NODE_NLJS_HPP
#define DEMOCFG_NODE_NLJS_HPP


#include "nlohmann/json.hpp"
#include "node_structs.hpp"

namespace democfg {

    using json = nlohmann::json;

    NLOHMANN_JSON_SERIALIZE_ENUM( LinkType, {
            { democfg::LinkType::bind, "bind" },
            { democfg::LinkType::connect, "connect" },
        })

    // Converters for Link
    // Describes how a single link is to be made
    inline void to_json(json& j, const Link& obj) {
        j["linktype"] = obj.linktype;
        j["address"] = obj.address;
    }
    inline void from_json(const json& j, Link& obj) {
        j.at("linktype").get_to(obj.linktype);    
        j.at("address").get_to(obj.address);    
    }
    // Converters for Port
    // A port configuration object
    inline void to_json(json& j, const Port& obj) {
        j["ident"] = obj.ident;
        j["links"] = obj.links;
    }
    inline void from_json(const json& j, Port& obj) {
        j.at("ident").get_to(obj.ident);    
        j.at("links").get_to(obj.links);    
    }
    // Converters for Comp
    // An object used by the node to partly configure a component
    inline void to_json(json& j, const Comp& obj) {
        j["ident"] = obj.ident;
        j["type_name"] = obj.type_name;
        j["portlist"] = obj.portlist;
        j["config"] = obj.config;
    }
    inline void from_json(const json& j, Comp& obj) {
        j.at("ident").get_to(obj.ident);    
        j.at("type_name").get_to(obj.type_name);    
        j.at("portlist").get_to(obj.portlist);    
        j.at("config").get_to(obj.config);    
    }
    // Converters for Node
    // A node configures ports and components
    inline void to_json(json& j, const Node& obj) {
        j["ident"] = obj.ident;
        j["portdefs"] = obj.portdefs;
        j["compdefs"] = obj.compdefs;
    }
    inline void from_json(const json& j, Node& obj) {
        j.at("ident").get_to(obj.ident);    
        j.at("portdefs").get_to(obj.portdefs);    
        j.at("compdefs").get_to(obj.compdefs);    
    }


} // namespace democfg

#endif