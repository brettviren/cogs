#include "comp_nljs.hpp"

#include "factory.hpp"
#include "ports.hpp"

#include "cogs/configurable.hpp"
#include "cogs/issues.hpp"


namespace demo {

    // class Sink, etc

    class Source : public cogs::Configurable<democfg::Source>,
                   public demo::PortuserBase {
      public:
        Source() {
            ERS_INFO("Source:\tconstructing");
        }
        virtual ~Source() {
            ERS_INFO("Source:\tdestructing");
        }

        virtual void configure(democfg::Source&& cfg) {
            ERS_INFO("Source:\tconfigured to send " << cfg.ntosend << " things");
        }
        
        virtual void set_port(demo::Port p) {
            ERS_INFO("Source:\tgiven port " << p.ident);
        }
    };

}


DEMO_REGISTER_COMPONENT("demoSource", demo::Source);
