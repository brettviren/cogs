#include "node_nljs.hpp"

#include "factory.hpp"

#include "cogs/configurable.hpp"
#include "cogs/issues.hpp"


namespace demo {

    class Node : public cogs::Configurable<democfg::Node> {
      public:
        Node() {
            ERS_INFO("Node:\t\tconstructing");
        }
        virtual ~Node() {
            ERS_INFO("Node:\t\tdestructing");
        }

        virtual void configure(democfg::Node&& cfg) {
            ERS_INFO("Node:\t\t" << cfg.ident);

            for (auto& p : cfg.portdefs) {
                ERS_INFO("Node:\t\t\tmaking port: " << p.ident);
                for (auto& l : p.links) {
                    std::string borc = "bind";
                    if (l.linktype == democfg::LinkType::connect) {
                        borc = "connect";
                    }
                    ERS_INFO("Node:\t\t\t\tlink: " << borc << "'ing to: " << l.address);
                }
            }

            // Interaction between a Node and components
            for (auto& c : cfg.compdefs) {
                ERS_INFO("Node:\t\tlookin up component: " << c.ident);
                auto pu = portuser(c.type_name, c.ident);
                if (!pu) {
                    ERS_DEBUG(1, "Node:\t\tignoring non-port using component");
                    continue;
                }
                // Ports here represent some kind of a shared resource
                // with potentally complex construction semantics or
                // otherwise to be constructed by one component and
                // used by others.  Only components that want ports,
                // indicated by having a PortuserBase inheritance are
                // considered.  And, we only set those ports
                // identified through configuration.
                for (auto pn: c.portlist) {
                    Port port{pn};
                    ERS_INFO("Node:\t\t\tset port: " << pn);
                    pu->set_port(port);
                }
            }
        }
        
    };

}

DEMO_REGISTER_COMPONENT("demoNode", demo::Node);
