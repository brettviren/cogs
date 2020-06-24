/**
 * Ports in this demo are bogs placeholders for something like ZIO
 * ports.  They are included here to provide an example of a
 * non-trivial exchange between nodes and abstract component
 * interfaces. 
 */
#ifndef COGS_DEMO_PORTS_HPP_SEEN
#define COGS_DEMO_PORTS_HPP_SEEN

#include <string>


namespace demo {

    struct Port {
        std::string ident;
        void recv() {};
        void send() {};
    };

    // A component that expects to use ports must inherit from this.
    // The configuration for the component that is given to the node
    // then drives which ports to give to the component.
    struct PortuserBase {
        virtual void set_port(Port p) = 0;
    };
    

}

#endif
