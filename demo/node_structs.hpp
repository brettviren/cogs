#ifndef DEMOCFG_NODE_STRUCTS_HPP
#define DEMOCFG_NODE_STRUCTS_HPP

#include <string>
#include <vector>

namespace democfg {

    enum class LinkType: unsigned {
        bind,
        connect,
    };

    struct Link {
        LinkType linktype;
        std::string address;
    };

    struct Port {
        std::string ident;
        std::vector<Link> links;
    };

    struct Comp {
        std::string ident;
        std::string type_name;
        std::vector<std::string> portlist;
        std::string config;
    };

    struct Node {
        std::string ident;
        std::vector<Port> portdefs;
        std::vector<Comp> compdefs;
    };


} // namespace democfg

#endif